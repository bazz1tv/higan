struct Cartridge {
  #include "memory.hpp"

  auto sha256() const -> string;
  auto manifest() const -> string;
  auto title() const -> string;

  struct Information {
    string markup;
    string sha256;
    string title;
  } information;

  struct Media {
    uint id;
    string name;
  };
  vector<Media> memory;

  Cartridge();
  ~Cartridge();

  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;

  auto read(uint mode, buint32 addr) -> buint32;
  auto write(uint mode, buint32 addr, buint32 word) -> void;

  auto serialize(serializer&) -> void;

private:
  bool hasSRAM = false;
  bool hasEEPROM = false;
  bool hasFLASH = false;
};

extern Cartridge cartridge;
