bool r15_modified = false;

auto step(unsigned clocks) -> void;

auto rombuffer_sync() -> void;
auto rombuffer_update() -> void;
auto rombuffer_read() -> buint8;

auto rambuffer_sync() -> void;
auto rambuffer_read(buint16 addr) -> buint8;
auto rambuffer_write(buint16 addr, buint8 data) -> void;

auto r14_modify(buint16) -> void;
auto r15_modify(buint16) -> void;

auto timing_reset() -> void;
