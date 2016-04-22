struct MMM01 : MMIO {
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  bool rom_mode;
  buint8 rom_base;

  bool ram_enable;
  buint8 rom_select;
  buint8 ram_select;
} mmm01;
