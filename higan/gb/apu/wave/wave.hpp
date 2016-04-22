struct Wave {
  auto getPattern(uint5 offset) const -> uint4;

  auto run() -> void;
  auto clockLength() -> void;
  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;
  auto power(bool initializeLength = true) -> void;

  auto serialize(serializer&) -> void;

  bool enable;

  bool dacEnable;
  uint2 volume;
  uint11 frequency;
  bool counter;
  buint8 pattern[16];

  int16 output;
  uint length;
  uint period;
  uint5 patternOffset;
  uint4 patternSample;
  uint patternHold;
};
