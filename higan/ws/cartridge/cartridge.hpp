struct Cartridge : Thread, IO {
  static auto Enter() -> void;
  auto main() -> void;
  auto step(uint clocks) -> void;
  auto power() -> void;

  auto load() -> void;
  auto unload() -> void;

  //memory.cpp
  auto romRead(uint20 addr) -> buint8;
  auto romWrite(uint20 addr, buint8 data) -> void;

  auto ramRead(uint20 addr) -> buint8;
  auto ramWrite(uint20 addr, buint8 data) -> void;

  //rtc.cpp
  auto rtcLoad() -> void;
  auto rtcSave() -> void;
  auto rtcTickSecond() -> void;
  auto rtcCheckAlarm() -> void;
  auto rtcStatus() -> buint8;
  auto rtcCommand(buint8 data) -> void;
  auto rtcRead() -> buint8;
  auto rtcWrite(buint8 data) -> void;

  //io.cpp
  auto portRead(buint16 addr) -> buint8 override;
  auto portWrite(buint16 addr, buint8 data) -> void override;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  struct Information {
    string manifest;
    string title;
    bool orientation;  //0 = horizontal; 1 = vertical
    string sha256;
  } information;

  struct Registers {
    //$00c0  BANK_ROM2
    buint8 romBank2;

    //$00c1  BANK_SRAM
    buint8 sramBank;

    //$00c2  BANK_ROM0
    buint8 romBank0;

    //$00c3  BANK_ROM1
    buint8 romBank1;

    //$00cc  GPO_EN
    buint8 gpoEnable;

    //$00cd  GPO_DATA
    buint8 gpoData;
  } r;

  struct Memory {
    buint8* data = nullptr;
    uint size = 0;
    uint mask = 0;
    string name;
  };

  struct RTC : Memory {
    buint8 command;
    uint4 index;

    buint8 alarm;
    buint8 alarmHour;
    buint8 alarmMinute;

    auto year()    -> buint8& { return data[0]; }
    auto month()   -> buint8& { return data[1]; }
    auto day()     -> buint8& { return data[2]; }
    auto weekday() -> buint8& { return data[3]; }
    auto hour()    -> buint8& { return data[4]; }
    auto minute()  -> buint8& { return data[5]; }
    auto second()  -> buint8& { return data[6]; }
  };

  Memory rom;
  Memory ram;
  EEPROM eeprom;
  RTC rtc;
};

extern Cartridge cartridge;
