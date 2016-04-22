#include <gba/gba.hpp>

namespace GameBoyAdvance {

#include "mmio.cpp"
Bus bus;

struct UnmappedMemory : Memory {
  auto read(uint mode, buint32 addr) -> buint32 override { return 0; }
  auto write(uint mode, buint32 addr, buint32 word) -> void override {}
};

static UnmappedMemory unmappedMemory;

auto Bus::mirror(buint32 addr, buint32 size) -> buint32 {
  buint32 base = 0;
  if(size) {
    buint32 mask = 1 << 27;  //28-bit bus
    while(addr >= size) {
      while(!(addr & mask)) mask >>= 1;
      addr -= mask;
      if(size > mask) {
        size -= mask;
        base += mask;
      }
      mask >>= 1;
    }
    base += addr;
  }
  return base;
}

auto Bus::power() -> void {
  for(auto n : range(0x400)) mmio[n] = &unmappedMemory;
}

}
