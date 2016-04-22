struct Memory {
  virtual inline auto size() const -> uint;
  virtual auto read(uint24 addr, buint8 data = 0) -> buint8 = 0;
  virtual auto write(uint24 addr, buint8 data) -> void = 0;
};

struct StaticRAM : Memory {
  inline StaticRAM(uint size);
  inline ~StaticRAM();

  inline auto data() -> buint8*;
  inline auto size() const -> uint;

  inline auto read(uint24 addr, buint8 data = 0) -> buint8;
  inline auto write(uint24 addr, buint8 data) -> void;
  inline auto operator[](uint24 addr) -> buint8&;
  inline auto operator[](uint24 addr) const -> const buint8&;

private:
  buint8* data_ = nullptr;
  uint size_ = 0;
};

struct MappedRAM : Memory {
  inline auto reset() -> void;
  inline auto map(buint8*, uint) -> void;
  inline auto copy(const stream& memory) -> void;
  inline auto read(const stream& memory) -> void;

  inline auto write_protect(bool status) -> void;
  inline auto data() -> buint8*;
  inline auto size() const -> uint;

  inline auto read(uint24 addr, buint8 data = 0) -> buint8;
  inline auto write(uint24 addr, buint8 data) -> void;
  inline auto operator[](uint24 addr) const -> const buint8&;

private:
  buint8* data_ = nullptr;
  uint size_ = 0;
  bool write_protect_ = false;
};

struct Bus {
  alwaysinline static auto mirror(uint addr, uint size) -> uint;
  alwaysinline static auto reduce(uint addr, uint mask) -> uint;

  Bus();
  ~Bus();

  alwaysinline auto read(uint24 addr, buint8 data) -> buint8;
  alwaysinline auto write(uint24 addr, buint8 data) -> void;

  auto reset() -> void;
  auto map() -> void;
  auto map(
    const function<buint8 (uint24, buint8)>& reader,
    const function<void (uint24, buint8)>& writer,
    buint8 banklo, buint8 bankhi, buint16 addrlo, buint16 addrhi,
    uint size = 0, uint base = 0, uint mask = 0
  ) -> void;

  buint8* lookup = nullptr;
  buint32* target = nullptr;

  uint idcount = 0;
  function<auto (uint24, buint8) -> buint8> reader[256];
  function<auto (uint24, buint8) -> void> writer[256];
};

extern Bus bus;
