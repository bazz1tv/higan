auto bus_read(uint24 addr, buint8 data) -> buint8;
auto bus_write(uint24 addr, buint8 data) -> void;
auto vbr_read(uint24 addr, buint8 data = 0) -> buint8;

alwaysinline auto io() -> void override;
alwaysinline auto read(uint24 addr) -> buint8 override;
alwaysinline auto write(uint24 addr, buint8 data) -> void override;

auto mmcrom_read(uint24 addr, buint8 data) -> buint8;
auto mmcrom_write(uint24 addr, buint8 data) -> void;

auto mmcbwram_read(uint24 addr, buint8 data) -> buint8;
auto mmcbwram_write(uint24 addr, buint8 data) -> void;

auto mmc_sa1_read(uint addr, buint8 data) -> buint8;
auto mmc_sa1_write(uint addr, buint8 data) -> void;

auto bitmap_read(uint addr, buint8 data) -> buint8;
auto bitmap_write(uint addr, buint8 data) -> void;
