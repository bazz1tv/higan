struct MROM {
  buint8* data;
  uint size;
  uint mask;

  auto read(uint mode, buint32 addr) -> buint32;
  auto write(uint mode, buint32 addr, buint32 word) -> void;

  auto serialize(serializer&) -> void;
} mrom;

struct SRAM {
  buint8* data;
  uint size;
  uint mask;

  auto read(uint mode, buint32 addr) -> buint32;
  auto write(uint mode, buint32 addr, buint32 word) -> void;

  auto serialize(serializer&) -> void;
} sram;

struct EEPROM {
  buint8* data;
  uint size;
  uint mask;
  uint test;
  uint bits;

  enum class Mode : uint {
    Wait, Command, ReadAddress, ReadValidate, ReadData, WriteAddress, WriteData, WriteValidate
  } mode;
  uint offset;
  uint address;
  uint addressbits;

  auto read(uint addr) -> bool;
  auto write(uint addr, bool bit) -> void;

  auto read() -> bool;
  auto write(bool bit) -> void;
  auto power() -> void;
  auto serialize(serializer&) -> void;
} eeprom;

struct FLASH {
  buint8* data;
  uint size;
  buint16 id;

  bool unlockhi;
  bool unlocklo;
  bool idmode;
  bool erasemode;
  bool bankselect;
  bool writeselect;
  bool bank;

  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 byte) -> void;

  auto power() -> void;
  auto serialize(serializer&) -> void;
} flash;
