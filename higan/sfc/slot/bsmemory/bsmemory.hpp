struct BSMemory : Memory {
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto size() const -> uint;
  auto read(uint24 addr, buint8) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  MappedRAM memory;
  bool readonly;

private:
  struct {
    uint command;
    buint8 write_old;
    buint8 write_new;

    bool flash_enable;
    bool read_enable;
    bool write_enable;
  } regs;
};

extern BSMemory bsmemory;
