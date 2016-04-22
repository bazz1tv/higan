struct Bus {
  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;
};

extern Bus bus;
