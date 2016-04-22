struct OBC1 {
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  auto serialize(serializer&) -> void;

  MappedRAM ram;

private:
  auto ramRead(uint addr) -> buint8;
  auto ramWrite(uint addr, buint8 data) -> void;

  struct {
    buint16 address;
    buint16 baseptr;
    buint16 shift;
  } status;
};

extern OBC1 obc1;
