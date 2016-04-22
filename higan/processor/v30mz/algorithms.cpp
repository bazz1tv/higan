//(0 = odd, 1 = even) number of bits set in value
auto V30MZ::parity(buint8 value) const -> bool {
  value ^= value >> 4;
  value ^= value >> 2;
  value ^= value >> 1;
  return !(value & 1);
}

#define bits (size == Byte ? 8 : 16)
#define mask (size == Byte ? 0xff : 0xffff)
#define sign (size == Byte ? 0x80 : 0x8000)

auto V30MZ::alAdc(Size size, buint16 x, buint16 y) -> buint16 {
  return alAdd(size, x, y + r.f.c);
}

auto V30MZ::alAdd(Size size, buint16 x, buint16 y) -> buint16 {
  buint16 result = (x + y) & mask;
  r.f.c = x + y > mask;
  r.f.p = parity(result);
  r.f.h = (uint4)x + (uint4)y >= 16;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = (result ^ x) & (result ^ y) & sign;
  return result;
}

auto V30MZ::alAnd(Size size, buint16 x, buint16 y) -> buint16 {
  buint16 result = (x & y) & mask;
  r.f.c = 0;
  r.f.p = parity(result);
  r.f.h = 0;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = 0;
  return result;
}

auto V30MZ::alDec(Size size, buint16 x) -> buint16 {
  buint16 result = (x - 1) & mask;
  r.f.p = parity(result);
  r.f.h = (x & 0x0f) == 0;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = result == sign - 1;
  return result;
}

auto V30MZ::alDiv(Size size, buint32 x, buint32 y) -> buint32 {
  if(y == 0) return interrupt(0), 0;
  buint32 quotient = x / y;
  buint32 remainder = x % y;
  return (remainder & mask) << bits | (quotient & mask);
}

auto V30MZ::alDivi(Size size, int32 x, int32 y) -> buint32 {
  if(y == 0) return interrupt(0), 0;
  x = size == Byte ? (int8_t)x : (int16_t)x;
  y = size == Byte ? (int8_t)y : (int16_t)y;
  buint32 quotient = x / y;
  buint32 remainder = x % y;
  return (remainder & mask) << bits | (quotient & mask);
}

auto V30MZ::alInc(Size size, buint16 x) -> buint16 {
  buint16 result = (x + 1) & mask;
  r.f.p = parity(result);
  r.f.h = (x & 0x0f) == 0x0f;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = result == sign;
  return result;
}

auto V30MZ::alMul(Size size, buint16 x, buint16 y) -> buint32 {
  buint32 result = x * y;
  r.f.c = result >> bits;
  r.f.v = result >> bits;
  return result;
}

auto V30MZ::alMuli(Size size, int16 x, int16 y) -> buint32 {
  x = size == Byte ? (int8_t)x : (int16_t)x;
  y = size == Byte ? (int8_t)y : (int16_t)y;
  buint32 result = x * y;
  r.f.c = result >> bits;
  r.f.v = result >> bits;
  return result;
}

auto V30MZ::alNeg(Size size, buint16 x) -> buint16 {
  buint16 result = (-x) & mask;
  r.f.c = x;
  r.f.p = parity(result);
  r.f.h = x & 0x0f;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = x == sign;
  return result;
}

auto V30MZ::alNot(Size size, buint16 x) -> buint16 {
  buint16 result = (~x) & mask;
  return result;
}

auto V30MZ::alOr(Size size, buint16 x, buint16 y) -> buint16 {
  buint16 result = (x | y) & mask;
  r.f.c = 0;
  r.f.p = parity(result);
  r.f.h = 0;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = 0;
  return result;
}

auto V30MZ::alRcl(Size size, buint16 x, uint5 y) -> buint16 {
  buint16 result = x;
  for(uint n = 0; n < y; n++) {
    bool carry = result & sign;
    result = (result << 1) | r.f.c;
    r.f.c = carry;
  }
  r.f.v = (x ^ result) & sign;
  return result & mask;
}

auto V30MZ::alRcr(Size size, buint16 x, uint5 y) -> buint16 {
  buint16 result = x;
  for(uint n = 0; n < y; n++) {
    bool carry = result & 1;
    result = (r.f.c ? sign : 0) | (result >> 1);
    r.f.c = carry;
  }
  r.f.v = (x ^ result) & sign;
  return result & mask;
}

auto V30MZ::alRol(Size size, buint16 x, uint4 y) -> buint16 {
  r.f.c = (x << y) & (1 << bits);
  buint16 result = ((x << y) | (x >> (bits - y))) & mask;
  r.f.v = (x ^ result) & sign;
  return result;
}

auto V30MZ::alRor(Size size, buint16 x, uint4 y) -> buint16 {
  r.f.c = (x >> (y - 1)) & 1;
  buint16 result = ((x >> y) | (x << (bits - y))) & mask;
  r.f.v = (x ^ result) & sign;
  return result;
}

auto V30MZ::alSal(Size size, buint16 x, uint5 y) -> buint16 {
  r.f.c = (x << y) & (1 << bits);
  buint16 result = (x << y) & mask;
  r.f.p = parity(result);
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = 0;
  return result;
}

auto V30MZ::alSar(Size size, buint16 x, uint5 y) -> buint16 {
  if(y & 16) {
    r.f.c = x & sign;
    return 0 - r.f.c;
  }
  r.f.c = (x >> (y - 1)) & 1;
  buint16 result = (x >> y) & mask;
  if(x & sign) result |= mask << (bits - y);
  r.f.p = parity(result);
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = 0;
  return result;
}

auto V30MZ::alSbb(Size size, buint16 x, buint16 y) -> buint16 {
  return alSub(size, x, y + r.f.c);
}

auto V30MZ::alShl(Size size, buint16 x, uint5 y) -> buint16 {
  r.f.c = (x << y) & (1 << bits);
  buint16 result = (x << y) & mask;
  r.f.p = parity(result);
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = (x ^ result) & sign;
  return result;
}

auto V30MZ::alShr(Size size, buint16 x, uint5 y) -> buint16 {
  r.f.c = (x >> (y - 1)) & 1;
  buint16 result = (x >> y) & mask;
  r.f.p = parity(result);
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = (x ^ result) & sign;
  return result;
}

auto V30MZ::alSub(Size size, buint16 x, buint16 y) -> buint16 {
  buint16 result = (x - y) & mask;
  r.f.c = y > x;
  r.f.p = parity(result);
  r.f.h = (uint4)y > (uint4)x;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = (x ^ y) & (x ^ result) & sign;
  return result;
}

auto V30MZ::alXor(Size size, buint16 x, buint16 y) -> buint16 {
  buint16 result = (x ^ y) & mask;
  r.f.c = 0;
  r.f.p = parity(result);
  r.f.h = 0;
  r.f.z = result == 0;
  r.f.s = result & sign;
  r.f.v = 0;
  return result;
}

#undef mask
#undef sign
