auto SMP::op_adc(buint8 x, buint8 y) -> buint8 {
  int r = x + y + regs.p.c;
  regs.p.n = r & 0x80;
  regs.p.v = ~(x ^ y) & (x ^ r) & 0x80;
  regs.p.h = (x ^ y ^ r) & 0x10;
  regs.p.z = (buint8)r == 0;
  regs.p.c = r > 0xff;
  return r;
}

auto SMP::op_addw(buint16 x, buint16 y) -> buint16 {
  buint16 r;
  regs.p.c = 0;
  r  = op_adc(x, y);
  r |= op_adc(x >> 8, y >> 8) << 8;
  regs.p.z = r == 0;
  return r;
}

auto SMP::op_and(buint8 x, buint8 y) -> buint8 {
  x &= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_cmp(buint8 x, buint8 y) -> buint8 {
  int r = x - y;
  regs.p.n = r & 0x80;
  regs.p.z = (buint8)r == 0;
  regs.p.c = r >= 0;
  return x;
}

auto SMP::op_cmpw(buint16 x, buint16 y) -> buint16 {
  int r = x - y;
  regs.p.n = r & 0x8000;
  regs.p.z = (buint16)r == 0;
  regs.p.c = r >= 0;
  return x;
}

auto SMP::op_eor(buint8 x, buint8 y) -> buint8 {
  x ^= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_or(buint8 x, buint8 y) -> buint8 {
  x |= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_sbc(buint8 x, buint8 y) -> buint8 {
  int r = x - y - !regs.p.c;
  regs.p.n = r & 0x80;
  regs.p.v = (x ^ y) & (x ^ r) & 0x80;
  regs.p.h = !((x ^ y ^ r) & 0x10);
  regs.p.z = (buint8)r == 0;
  regs.p.c = r >= 0;
  return r;
}

auto SMP::op_subw(buint16 x, buint16 y) -> buint16 {
  buint16 r;
  regs.p.c = 1;
  r  = op_sbc(x, y);
  r |= op_sbc(x >> 8, y >> 8) << 8;
  regs.p.z = r == 0;
  return r;
}

auto SMP::op_inc(buint8 x) -> buint8 {
  x++;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_dec(buint8 x) -> buint8 {
  x--;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_asl(buint8 x) -> buint8 {
  regs.p.c = x & 0x80;
  x <<= 1;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_lsr(buint8 x) -> buint8 {
  regs.p.c = x & 0x01;
  x >>= 1;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_rol(buint8 x) -> buint8 {
  auto carry = (uint)regs.p.c;
  regs.p.c = x & 0x80;
  x = (x << 1) | carry;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SMP::op_ror(buint8 x) -> buint8 {
  auto carry = (uint)regs.p.c << 7;
  regs.p.c = x & 0x01;
  x = carry | (x >> 1);
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}
