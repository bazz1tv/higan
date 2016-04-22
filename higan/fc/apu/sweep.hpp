struct Sweep {
  auto check_period() -> bool;
  auto clock(uint channel) -> void;

  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  buint8 shift;
  bool decrement;
  uint3 period;
  buint8 counter;
  bool enable;
  bool reload;
  uint11 pulse_period;
};
