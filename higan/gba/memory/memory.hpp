struct Memory {
  virtual auto read(uint mode, buint32 addr) -> buint32 = 0;
  virtual auto write(uint mode, buint32 addr, buint32 word) -> void = 0;
};

struct MMIO : Memory {
  virtual auto read(buint32 addr) -> buint8 = 0;
  virtual auto write(buint32 addr, buint8 data) -> void = 0;
  auto read(uint mode, buint32 addr) -> buint32 final;
  auto write(uint mode, buint32 addr, buint32 word) -> void final;
};

struct Bus {
  static auto mirror(buint32 addr, buint32 size) -> buint32;

  auto power() -> void;

  Memory* mmio[0x400] = {nullptr};
};

extern Bus bus;
