struct NSS {
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto set_dip(buint16 dip) -> void;
  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  buint8 dip = 0x00;
};

extern NSS nss;
