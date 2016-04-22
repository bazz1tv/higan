auto get_vram_address() -> buint16;

auto vram_mmio_read(buint16 addr) -> buint8;
auto vram_mmio_write(buint16 addr, buint8 data) -> void;

auto oam_mmio_read(buint16 addr) -> buint8;
auto oam_mmio_write(buint16 addr, buint8 data) -> void;

auto cgram_mmio_read(buint16 addr) -> buint8;
auto cgram_mmio_write(buint16 addr, buint8 data) -> void;
