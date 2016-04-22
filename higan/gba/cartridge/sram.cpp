auto Cartridge::SRAM::read(uint mode, buint32 addr) -> buint32 {
  buint32 word = data[addr & mask];
  word |= word <<  8;
  word |= word << 16;
  return word;
}

auto Cartridge::SRAM::write(uint mode, buint32 addr, buint32 word) -> void {
  data[addr & mask] = word;
}

auto Cartridge::SRAM::serialize(serializer& s) -> void {
  s.array(data, size);
}
