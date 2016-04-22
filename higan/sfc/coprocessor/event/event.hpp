//SNES-EVENT board emulation:
//* Campus Challenge '92
//* Powerfest '94

struct Event : Coprocessor {
  static auto Enter() -> void;
  auto main() -> void;
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto mcuRead(uint24 addr, buint8) -> buint8;
  auto mcuWrite(uint24 addr, buint8) -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  auto serialize(serializer&) -> void;

  MappedRAM rom[4];
  MappedRAM ram;

  enum class Board : uint { CampusChallenge92, Powerfest94 } board;
  uint timer;

privileged:
  buint8 status;
  buint8 select;

  bool timerActive;
  bool scoreActive;

  uint timerSecondsRemaining;
  uint scoreSecondsRemaining;
};

extern Event event;
