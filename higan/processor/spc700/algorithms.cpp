auto SPC700::op_adc(buint8 x, buint8 y) -> buint8 {
  int r = x + y + regs.p.c;
  regs.p.n = r & 0x80;
  regs.p.v = ~(x ^ y) & (x ^ r) & 0x80;
  regs.p.h = (x ^ y ^ r) & 0x10;
  regs.p.z = (buint8)r == 0;
  regs.p.c = r > 0xff;
  return r;
}

auto SPC700::op_and(buint8 x, buint8 y) -> buint8 {
  x &= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_asl(buint8 x) -> buint8 {
  regs.p.c = x & 0x80;
  x <<= 1;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_cmp(buint8 x, buint8 y) -> buint8 {
  int r = x - y;
  regs.p.n = r & 0x80;
  regs.p.z = (buint8)r == 0;
  regs.p.c = r >= 0;
  return x;
}

auto SPC700::op_dec(buint8 x) -> buint8 {
  x--;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_eor(buint8 x, buint8 y) -> buint8 {
  x ^= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_inc(buint8 x) -> buint8 {
  x++;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_ld(buint8 x, buint8 y) -> buint8 {
  regs.p.n = y & 0x80;
  regs.p.z = y == 0;
  return y;
}

auto SPC700::op_lsr(buint8 x) -> buint8 {
  regs.p.c = x & 0x01;
  x >>= 1;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_or(buint8 x, buint8 y) -> buint8 {
  x |= y;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_rol(buint8 x) -> buint8 {
  uint carry = regs.p.c << 0;
  regs.p.c = x & 0x80;
  x = (x << 1) | carry;
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_ror(buint8 x) -> buint8 {
  uint carry = regs.p.c << 7;
  regs.p.c = x & 0x01;
  x = carry | (x >> 1);
  regs.p.n = x & 0x80;
  regs.p.z = x == 0;
  return x;
}

auto SPC700::op_sbc(buint8 x, buint8 y) -> buint8 {
  return op_adc(x, ~y);
}

auto SPC700::op_st(buint8 x, buint8 y) -> buint8 {
  return y;
}

//

auto SPC700::op_adw(buint16 x, buint16 y) -> buint16 {
  buint16 r;
  regs.p.c = 0;
  r  = op_adc(x, y);
  r |= op_adc(x >> 8, y >> 8) << 8;
  regs.p.z = r == 0;
  return r;
}

auto SPC700::op_cpw(buint16 x, buint16 y) -> buint16 {
  int r = x - y;
  regs.p.n = r & 0x8000;
  regs.p.z = (buint16)r == 0;
  regs.p.c = r >= 0;
  return x;
}

auto SPC700::op_ldw(buint16 x, buint16 y) -> buint16 {
  regs.p.n = y & 0x8000;
  regs.p.z = y == 0;
  return y;
}

auto SPC700::op_sbw(buint16 x, buint16 y) -> buint16 {
  buint16 r;
  regs.p.c = 1;
  r  = op_sbc(x, y);
  r |= op_sbc(x >> 8, y >> 8) << 8;
  regs.p.z = r == 0;
  return r;
}
