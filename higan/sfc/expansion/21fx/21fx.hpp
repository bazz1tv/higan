struct S21FX : Thread, Memory {
  static auto Enter() -> void;
  auto main() -> void;
  auto step(uint clocks) -> void;
  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto read(uint24 addr, buint8 data) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

private:
  auto quit() -> bool;
  auto usleep(uint) -> void;
  auto readable() -> bool;
  auto writable() -> bool;
  auto read() -> buint8;
  auto write(buint8) -> void;

  bool booted = false;
  buint16 resetVector;
  buint8 ram[122];

  nall::library link;
  function<void (
    function<bool ()>,      //quit
    function<void (uint)>,  //usleep
    function<bool ()>,      //readable
    function<bool ()>,      //writable
    function<buint8 ()>,     //read
    function<void (buint8)>  //write
  )> linkInit;
  function<void (lstring)> linkMain;

  vector<buint8> snesBuffer;  //SNES -> Link
  vector<buint8> linkBuffer;  //Link -> SNES
};

extern S21FX s21fx;
