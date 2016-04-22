#include <gb/gb.hpp>

namespace GameBoy {

Unmapped unmapped;
Bus bus;

Memory::~Memory() {
  free();
}

auto Memory::operator[](uint addr) -> buint8& {
  return data[addr];
}

auto Memory::allocate(uint size_) -> void {
  free();
  size = size_;
  data = new buint8[size];
}

auto Memory::copy(const buint8* data_, unsigned size_) -> void {
  free();
  size = size_;
  data = new buint8[size];
  memcpy(data, data_, size);
}

auto Memory::free() -> void {
  if(data) {
    delete[] data;
    data = nullptr;
  }
}

//

auto Bus::read(buint16 addr) -> buint8 {
  buint8 data = mmio[addr]->mmio_read(addr);

  if(cheat.enable()) {
    if(auto result = cheat.find(addr, data)) return result();
  }

  return data;
}

auto Bus::write(buint16 addr, buint8 data) -> void {
  mmio[addr]->mmio_write(addr, data);
}

auto Bus::power() -> void {
  for(auto n : range(65536)) mmio[n] = &unmapped;
}

}
