#if defined(SFC_SUPERGAMEBOY)

struct ICD2 : Emulator::Interface::Bind, GameBoy::Interface::Hook, Coprocessor {
  static auto Enter() -> void;
  auto main() -> void;

  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  auto serialize(serializer&) -> void;

  uint revision;

private:
  #include "interface/interface.hpp"
  #include "mmio/mmio.hpp"

  Emulator::Interface::Bind* bind = nullptr;
  GameBoy::Interface::Hook* hook = nullptr;
};

#else

struct ICD2 : Coprocessor {
  auto init() -> void {}
  auto load() -> void {}
  auto unload() -> void {}
  auto power() -> void {}
  auto reset() -> void {}

  auto read(uint24, buint8) -> buint8 { return 0; }
  auto write(uint24, buint8) -> void { return; }

  auto serialize(serializer&) -> void {}

  uint revision;
};

#endif

extern ICD2 icd2;
