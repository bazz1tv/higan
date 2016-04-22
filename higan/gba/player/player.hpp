struct Player {
  struct Status {
    bool enable;
    bool rumble;

    bool logoDetected;
    uint logoCounter;

    uint packet;
    buint32 send;
    buint32 recv;
  } status;

  auto power() -> void;
  auto frame() -> void;

  auto keyinput() -> maybe<buint16>;
  auto read() -> maybe<buint32>;
  auto write(uint2 addr, buint8 byte) -> void;

  auto serialize(serializer& s) -> void;
};

extern Player player;
