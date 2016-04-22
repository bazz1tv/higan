auto ARM::condition(uint4 condition) -> bool {
  switch(condition) {
  case  0: return cpsr().z == 1;                          //EQ (equal)
  case  1: return cpsr().z == 0;                          //NE (not equal)
  case  2: return cpsr().c == 1;                          //CS (carry set)
  case  3: return cpsr().c == 0;                          //CC (carry clear)
  case  4: return cpsr().n == 1;                          //MI (negative)
  case  5: return cpsr().n == 0;                          //PL (positive)
  case  6: return cpsr().v == 1;                          //VS (overflow)
  case  7: return cpsr().v == 0;                          //VC (no overflow)
  case  8: return cpsr().c == 1 && cpsr().z == 0;         //HI (unsigned higher)
  case  9: return cpsr().c == 0 || cpsr().z == 1;         //LS (unsigned lower or same)
  case 10: return cpsr().n == cpsr().v;                   //GE (signed greater than or equal)
  case 11: return cpsr().n != cpsr().v;                   //LT (signed less than)
  case 12: return cpsr().z == 0 && cpsr().n == cpsr().v;  //GT (signed greater than)
  case 13: return cpsr().z == 1 || cpsr().n != cpsr().v;  //LE (signed less than or equal)
  case 14: return true;                                   //AL (always)
  case 15: return false;                                  //NV (never)
  }
}

auto ARM::bit(buint32 result) -> buint32 {
  if(cpsr().t || instruction() & (1 << 20)) {
    cpsr().n = result >> 31;
    cpsr().z = result == 0;
    cpsr().c = carryout();
  }
  return result;
}

auto ARM::add(buint32 source, buint32 modify, bool carry) -> buint32 {
  buint32 result = source + modify + carry;
  if(cpsr().t || instruction() & (1 << 20)) {
    buint32 overflow = ~(source ^ modify) & (source ^ result);
    cpsr().n = result >> 31;
    cpsr().z = result == 0;
    cpsr().c = (1u << 31) & (overflow ^ source ^ modify ^ result);
    cpsr().v = (1u << 31) & (overflow);
  }
  return result;
}

auto ARM::sub(buint32 source, buint32 modify, bool carry) -> buint32 {
  return add(source, ~modify, carry);
}

auto ARM::mul(buint32 product, buint32 multiplicand, buint32 multiplier) -> buint32 {
  idle();
  if((multiplier & 0xffffff00) != 0x00000000 && (multiplier & 0xffffff00) != 0xffffff00) idle();
  if((multiplier & 0xffff0000) != 0x00000000 && (multiplier & 0xffff0000) != 0xffff0000) idle();
  if((multiplier & 0xff000000) != 0x00000000 && (multiplier & 0xff000000) != 0xff000000) idle();

  product += multiplicand * multiplier;

  if(cpsr().t || instruction() & (1 << 20)) {
    cpsr().n = product >> 31;
    cpsr().z = product == 0;
  }

  return product;
}

auto ARM::lsl(buint32 source, buint8 shift) -> buint32 {
  carryout() = cpsr().c;
  if(shift == 0) return source;

  carryout() = shift > 32 ? 0 : source & (1 << 32 - shift);
  source     = shift > 31 ? 0 : source << shift;
  return source;
}

auto ARM::lsr(buint32 source, buint8 shift) -> buint32 {
  carryout() = cpsr().c;
  if(shift == 0) return source;

  carryout() = shift > 32 ? 0 : source & (1 << shift - 1);
  source     = shift > 31 ? 0 : source >> shift;
  return source;
}

auto ARM::asr(buint32 source, buint8 shift) -> buint32 {
  carryout() = cpsr().c;
  if(shift == 0) return source;

  carryout() = shift > 32 ? source & (1 << 31) : source & (1 << shift - 1);
  source     = shift > 31 ? (int32)source >> 31 : (int32)source >> shift;
  return source;
}

auto ARM::ror(buint32 source, buint8 shift) -> buint32 {
  carryout() = cpsr().c;
  if(shift == 0) return source;

  if(shift &= 31)
  source     = source << 32 - shift | source >> shift;
  carryout() = source & (1 << 31);
  return source;
}

auto ARM::rrx(buint32 source) -> buint32 {
  carryout() = source & 1;
  return (cpsr().c << 31) | (source >> 1);
}
