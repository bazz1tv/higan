//93LC46 (  64x16-bit) [ 128 bytes]
//93LC56 ( 128x16-bit) [ 256 bytes]
//93LC66 ( 256x16-bit) [ 512 bytes]
//93LC76 ( 512x16-bit) [1024 bytes]
//93LC86 (1024x16-bit) [2048 bytes]

struct EEPROM {
  enum : uint {
    DataLo,
    DataHi,
    AddressLo,
    AddressHi,
    Status,
    Command = Status,
  };

  auto name() const -> string;
  auto data() -> buint16*;
  auto size() const -> uint;

  auto setName(string name) -> void;
  auto setSize(uint size) -> void;

  auto erase() -> void;
  auto power() -> void;
  auto read(uint) -> buint8;
  auto write(uint, buint8) -> void;

  auto operator[](uint10 addr) -> buint16&;

  //serialization.cpp
  auto serialize(serializer&) -> void;

private:
  auto execute() -> void;

  string _name;
  buint16 _data[1024];
  uint _size = 0;  //in words

  struct Registers {
    buint16 latch;
    buint16 address;

    bool unknown;
    bool writeRequested;
    bool readRequested;

    bool writeCompleted;
    bool readCompleted;

    bool writeProtect;
  } r;
};
