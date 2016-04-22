auto SuperFX::stop() -> void {
  cpu.regs.irq = 1;
}

auto SuperFX::color(buint8 source) -> buint8 {
  if(regs.por.highnibble) return (regs.colr & 0xf0) | (source >> 4);
  if(regs.por.freezehigh) return (regs.colr & 0xf0) | (source & 0x0f);
  return source;
}

auto SuperFX::plot(buint8 x, buint8 y) -> void {
  buint8 color = regs.colr;

  if(regs.por.dither && regs.scmr.md != 3) {
    if((x ^ y) & 1) color >>= 4;
    color &= 0x0f;
  }

  if(!regs.por.transparent) {
    if(regs.scmr.md == 3) {
      if(regs.por.freezehigh) {
        if((color & 0x0f) == 0) return;
      } else {
        if(color == 0) return;
      }
    } else {
      if((color & 0x0f) == 0) return;
    }
  }

  buint16 offset = (y << 5) + (x >> 3);
  if(offset != pixelcache[0].offset) {
    pixelcache_flush(pixelcache[1]);
    pixelcache[1] = pixelcache[0];
    pixelcache[0].bitpend = 0x00;
    pixelcache[0].offset = offset;
  }

  x = (x & 7) ^ 7;
  pixelcache[0].data[x] = color;
  pixelcache[0].bitpend |= 1 << x;
  if(pixelcache[0].bitpend == 0xff) {
    pixelcache_flush(pixelcache[1]);
    pixelcache[1] = pixelcache[0];
    pixelcache[0].bitpend = 0x00;
  }
}

auto SuperFX::rpix(buint8 x, buint8 y) -> buint8 {
  pixelcache_flush(pixelcache[1]);
  pixelcache_flush(pixelcache[0]);

  unsigned cn;  //character number
  switch(regs.por.obj ? 3 : regs.scmr.ht) {
  case 0: cn = ((x & 0xf8) << 1) + ((y & 0xf8) >> 3); break;
  case 1: cn = ((x & 0xf8) << 1) + ((x & 0xf8) >> 1) + ((y & 0xf8) >> 3); break;
  case 2: cn = ((x & 0xf8) << 1) + ((x & 0xf8) << 0) + ((y & 0xf8) >> 3); break;
  case 3: cn = ((y & 0x80) << 2) + ((x & 0x80) << 1) + ((y & 0x78) << 1) + ((x & 0x78) >> 3); break;
  }
  unsigned bpp = 2 << (regs.scmr.md - (regs.scmr.md >> 1));  // = [regs.scmr.md]{ 2, 4, 4, 8 };
  unsigned addr = 0x700000 + (cn * (bpp << 3)) + (regs.scbr << 10) + ((y & 0x07) * 2);
  buint8 data = 0x00;
  x = (x & 7) ^ 7;

  for(unsigned n = 0; n < bpp; n++) {
    unsigned byte = ((n >> 1) << 4) + (n & 1);  // = [n]{ 0, 1, 16, 17, 32, 33, 48, 49 };
    step(regs.clsr ? 5 : 6);
    data |= ((bus_read(addr + byte) >> x) & 1) << n;
  }

  return data;
}

auto SuperFX::pixelcache_flush(pixelcache_t& cache) -> void {
  if(cache.bitpend == 0x00) return;

  buint8 x = cache.offset << 3;
  buint8 y = cache.offset >> 5;

  unsigned cn;  //character number
  switch(regs.por.obj ? 3 : regs.scmr.ht) {
  case 0: cn = ((x & 0xf8) << 1) + ((y & 0xf8) >> 3); break;
  case 1: cn = ((x & 0xf8) << 1) + ((x & 0xf8) >> 1) + ((y & 0xf8) >> 3); break;
  case 2: cn = ((x & 0xf8) << 1) + ((x & 0xf8) << 0) + ((y & 0xf8) >> 3); break;
  case 3: cn = ((y & 0x80) << 2) + ((x & 0x80) << 1) + ((y & 0x78) << 1) + ((x & 0x78) >> 3); break;
  }
  unsigned bpp = 2 << (regs.scmr.md - (regs.scmr.md >> 1));  // = [regs.scmr.md]{ 2, 4, 4, 8 };
  unsigned addr = 0x700000 + (cn * (bpp << 3)) + (regs.scbr << 10) + ((y & 0x07) * 2);

  for(unsigned n = 0; n < bpp; n++) {
    unsigned byte = ((n >> 1) << 4) + (n & 1);  // = [n]{ 0, 1, 16, 17, 32, 33, 48, 49 };
    buint8 data = 0x00;
    for(unsigned x = 0; x < 8; x++) data |= ((cache.data[x] >> n) & 1) << x;
    if(cache.bitpend != 0xff) {
      step(regs.clsr ? 5 : 6);
      data &= cache.bitpend;
      data |= bus_read(addr + byte) & ~cache.bitpend;
    }
    step(regs.clsr ? 5 : 6);
    bus_write(addr + byte, data);
  }

  cache.bitpend = 0x00;
}
