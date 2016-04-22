struct MBC0 : MMIO {
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;
  auto power() -> void;
} mbc0;
