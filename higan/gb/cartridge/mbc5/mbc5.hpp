struct MBC5 : MMIO {
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;
  auto power() -> void;

  bool ram_enable;    //$0000-1fff
  buint16 rom_select;  //$2000-2fff + $3000-3fff
  buint8 ram_select;   //$4000-5fff
} mbc5;
