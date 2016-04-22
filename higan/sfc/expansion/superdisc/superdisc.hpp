struct SuperDisc : Coprocessor, Memory {
  static auto Enter() -> void;
  auto main() -> void;

  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  //nec.cpp
  auto necPollIRQ() -> buint8;
  auto necReadData() -> buint8;
  auto necWriteCommand(uint4 data) -> void;

  //sony.cpp
  auto sonyPollIRQ() -> buint8;
  auto sonyReadData() -> buint8;
  auto sonyWriteCommand(buint8 data) -> void;
  auto sonyWriteData(buint8 data) -> void;

private:
  struct Registers {
    buint8 irqEnable;
  } r;

  //NEC
  struct NEC {
    vector<uint4> command;
    buint8 data;
  } nec;

  //Sony
  struct Sony {
    buint8 command;
    buint8 data;
  } sony;
};

extern SuperDisc superdisc;
