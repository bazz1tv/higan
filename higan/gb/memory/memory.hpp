struct Memory {
  ~Memory();

  auto operator[](uint addr) -> buint8&;
  auto allocate(uint size) -> void;
  auto copy(const buint8* data, uint size) -> void;
  auto free() -> void;

  buint8* data = nullptr;
  uint size = 0;
};

struct MMIO {
  virtual auto mmio_read(buint16 addr) -> buint8 = 0;
  virtual auto mmio_write(buint16 addr, buint8 data) -> void = 0;
};

struct Unmapped : MMIO {
  auto mmio_read(buint16) -> buint8 { return 0xff; }
  auto mmio_write(buint16, buint8) -> void {}
};

struct Bus {
  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  MMIO* mmio[65536];
};

extern Unmapped unmapped;
extern Bus bus;
