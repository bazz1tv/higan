struct Bridge {
  struct Buffer {
    bool ready;
    buint8 data;
  };
  Buffer cputoarm;
  Buffer armtocpu;
  buint32 timer;
  buint32 timerlatch;
  bool reset;
  bool ready;
  bool signal;

  auto status() const -> buint8 {
    return (ready << 7) | (cputoarm.ready << 3) | (signal << 2) | (armtocpu.ready << 0);
  }
} bridge;
