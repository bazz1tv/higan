struct MBC2 : MMIO {
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  bool  ram_enable;  //$0000-1fff
  buint8 rom_select;  //$2000-3fff
} mbc2;
