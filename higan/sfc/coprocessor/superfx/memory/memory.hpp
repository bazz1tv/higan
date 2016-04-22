uint rom_mask;  //rom_size - 1
uint ram_mask;  //ram_size - 1

auto bus_read(uint24 addr, buint8 data = 0x00) -> buint8 override;
auto bus_write(uint24 addr, buint8 data) -> void override;

auto op_read(buint16 addr) -> buint8;
alwaysinline auto peekpipe() -> buint8;
alwaysinline auto pipe() -> buint8;

auto cache_flush() -> void;
auto cache_mmio_read(buint16 addr) -> buint8;
auto cache_mmio_write(buint16 addr, buint8 data) -> void;

auto memory_reset() -> void;
