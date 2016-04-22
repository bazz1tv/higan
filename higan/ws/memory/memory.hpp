struct IO {
  virtual auto portRead(buint16 addr) -> buint8 = 0;
  virtual auto portWrite(buint16 addr, buint8 data) -> void = 0;
};

struct InternalRAM {
  auto power() -> void;
  auto serialize(serializer&) -> void;

  auto read(buint16 addr, uint size = Byte) -> buint32;
  auto write(buint16 addr, buint8 data) -> void;

private:
  buint8 memory[65536];
};

struct Bus {
  auto power() -> void;

  auto read(uint20 addr) -> buint8;
  auto write(uint20 addr, buint8 data) -> void;

  auto map(IO* io, uint16_t lo, maybe<uint16_t> hi = nothing) -> void;
  auto portRead(buint16 addr) -> buint8;
  auto portWrite(buint16 addr, buint8 data) -> void;

private:
  IO* port[64 * 1024] = {nullptr};
};

extern InternalRAM iram;
extern Bus bus;
