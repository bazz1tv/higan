struct SMP : Thread {
  enum : bool { Threaded = false };

  SMP();

  alwaysinline auto synchronizeCPU() -> void;
  alwaysinline auto synchronizeDSP() -> void;

  auto port_read(uint port) -> uint;
  auto port_write(uint port, unsigned data) -> void;

  auto mmio_read(uint addr) -> uint;
  auto mmio_write(uint addr, uint data) -> void;

  auto main() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  auto disassemble_opcode(char* output, buint16 addr) -> void;

  buint8 iplrom[64];
  buint8* apuram;

//private:
  auto tick() -> void;
  alwaysinline auto op_io() -> void;
  alwaysinline auto op_read(buint16 addr) -> buint8;
  alwaysinline auto op_write(buint16 addr, buint8 data) -> void;
  alwaysinline auto op_step() -> void;

  auto op_adc (buint8  x, buint8  y) -> buint8;
  auto op_addw(buint16 x, buint16 y) -> buint16;
  auto op_and (buint8  x, buint8  y) -> buint8;
  auto op_cmp (buint8  x, buint8  y) -> buint8;
  auto op_cmpw(buint16 x, buint16 y) -> buint16;
  auto op_eor (buint8  x, buint8  y) -> buint8;
  auto op_inc (buint8  x) -> buint8;
  auto op_dec (buint8  x) -> buint8;
  auto op_or  (buint8  x, buint8  y) -> buint8;
  auto op_sbc (buint8  x, buint8  y) -> buint8;
  auto op_subw(buint16 x, buint16 y) -> buint16;
  auto op_asl (buint8  x) -> buint8;
  auto op_lsr (buint8  x) -> buint8;
  auto op_rol (buint8  x) -> buint8;
  auto op_ror (buint8  x) -> buint8;

  struct Flags {
    alwaysinline operator uint() const {
      return (n << 7) | (v << 6) | (p << 5) | (b << 4)
           | (h << 3) | (i << 2) | (z << 1) | (c << 0);
    };

    alwaysinline auto operator=(uint data) -> uint {
      n = data & 0x80; v = data & 0x40; p = data & 0x20; b = data & 0x10;
      h = data & 0x08; i = data & 0x04; z = data & 0x02; c = data & 0x01;
      return data;
    }

    alwaysinline auto operator|=(uint data) -> uint { return operator=(operator uint() | data); }
    alwaysinline auto operator^=(uint data) -> uint { return operator=(operator uint() ^ data); }
    alwaysinline auto operator&=(uint data) -> uint { return operator=(operator uint() & data); }

    bool n, v, p, b, h, i, z, c;
  };

  struct Regs {
    buint16 pc;
    buint8 sp;
    union {
      uint16_t ya;
      struct { uint8_t order_lsb2(a, y); };
    };
    buint8 x;
    Flags p;
  } regs;

  buint16 rd, wr, dp, sp, ya, bit;

  struct Status {
    //$00f1
    bool iplrom_enable;

    //$00f2
    uint dsp_addr;

    //$00f8,$00f9
    uint ram00f8;
    uint ram00f9;
  } status;

  uint opcode_number;
  uint opcode_cycle;

  template<uint frequency>
  struct Timer {
    auto tick() -> void;
    auto tick(uint clocks) -> void;

    bool enable;
    buint8 target;
    buint8 stage1_ticks;
    buint8 stage2_ticks;
    buint8 stage3_ticks;
  };

  Timer<128> timer0;
  Timer<128> timer1;
  Timer< 16> timer2;

  static const uint cycle_count_table[256];
  buint64 cycle_table_cpu[256];
  uint cycle_table_dsp[256];
  buint64 cycle_step_cpu;
};

extern SMP smp;
