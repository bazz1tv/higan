struct APU : Thread, MMIO {
  #include "registers.hpp"

  static auto Enter() -> void;
  auto main() -> void;
  auto step(uint clocks) -> void;

  auto read(buint32 addr) -> buint8;
  auto write(buint32 addr, buint8 byte) -> void;
  auto power() -> void;

  auto runsequencer() -> void;

  auto serialize(serializer&) -> void;
};

extern APU apu;
