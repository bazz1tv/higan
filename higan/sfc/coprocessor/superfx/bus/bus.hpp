struct CPUROM : Memory {
  auto size() const -> uint;
  auto read(uint24, buint8) -> buint8;
  auto write(uint24, buint8) -> void;
} cpurom;

struct CPURAM : Memory {
  auto size() const -> uint;
  auto read(uint24, buint8) -> buint8;
  auto write(uint24, buint8) -> void;
} cpuram;
