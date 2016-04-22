struct Flags {
  inline operator uint() {
    return (n << 7) | (v << 6) | (d << 3) | (i << 2) | (z << 1) | (c << 0);
  }

  inline auto operator=(buint8 data) -> Flags& {
    n = data & 0x80; v = data & 0x40;
    d = data & 0x08; i = data & 0x04; z = data & 0x02; c = data & 0x01;
    return *this;
  }

  bool n, v, d, i, z, c;
};

struct Registers {
  buint8  mdr;
  buint16 pc;
  buint8  a, x, y, s;
  Flags  p;
} regs;

struct Register16 {
  union {
    uint16_t w;
    struct { uint8_t order_lsb2(l, h); };
  };
} abs, iabs;

buint8 rd;
buint8 zp;
buint16 aa;
