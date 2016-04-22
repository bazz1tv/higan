struct Satellaview : Memory {
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

private:
  struct {
    buint8 r2188, r2189, r218a, r218b;
    buint8 r218c, r218d, r218e, r218f;
    buint8 r2190, r2191, r2192, r2193;
    buint8 r2194, r2195, r2196, r2197;
    buint8 r2198, r2199, r219a, r219b;
    buint8 r219c, r219d, r219e, r219f;

    buint8 r2192_counter;
    buint8 r2192_hour, r2192_minute, r2192_second;
  } regs;
};

extern Satellaview satellaview;
