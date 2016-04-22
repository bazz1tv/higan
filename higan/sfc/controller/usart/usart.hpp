struct USART : Controller, public library {
  USART(bool port);
  ~USART();

  auto main() -> void;

  auto quit() -> bool;
  auto usleep(uint microseconds) -> void;
  auto readable() -> bool;
  auto read() -> buint8;
  auto writable() -> bool;
  auto write(buint8 data) -> void;

  auto data() -> uint2;
  auto latch(bool data) -> void;

private:
  bool latched = 0;
  bool data1 = 0;
  bool data2 = 0;
  uint counter = 0;

  buint8 rxlength = 0;
  buint8 rxdata = 0;
  vector<buint8> rxbuffer;

  buint8 txlength = 0;
  buint8 txdata = 0;
  vector<buint8> txbuffer;

  function<void (
    function<bool ()>,      //quit
    function<void (uint)>,  //usleep
    function<bool ()>,      //readable
    function<buint8 ()>,     //read
    function<bool ()>,      //writable
    function<void (buint8)>  //write
  )> usart_init;
  function<void (lstring)> usart_main;
};
