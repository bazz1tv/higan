struct CPUIRAM : Memory {
  auto size() const -> uint;
  alwaysinline auto read(uint24, buint8 = 0) -> buint8;
  alwaysinline auto write(uint24, buint8) -> void;
} cpuiram;

struct CPUBWRAM : Memory {
  auto size() const -> uint;
  alwaysinline auto read(uint24, buint8 = 0) -> buint8;
  alwaysinline auto write(uint24, buint8) -> void;
  bool dma;
} cpubwram;
