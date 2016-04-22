struct CPU : Processor::R65816, Thread, public PPUcounter {
  enum : bool { Threaded = true };

  CPU();

  alwaysinline auto step(uint clocks) -> void;
  alwaysinline auto synchronizeSMP() -> void;
  auto synchronizePPU() -> void;
  auto synchronizeCoprocessors() -> void;
  auto synchronizeDevices() -> void;

  auto pio() -> buint8;
  auto joylatch() -> bool;
  auto interruptPending() const -> bool;
  auto port_read(buint8 port) -> buint8;
  auto port_write(buint8 port, buint8 data) -> void;
  auto dmaPortRead(uint24 addr, buint8 data) -> buint8;
  auto dmaPortWrite(uint24 addr, buint8 data) -> void;
  auto mmio_read(uint addr, buint8 data) -> buint8;
  auto mmio_write(uint addr, buint8 data) -> void;

  auto io() -> void;
  auto read(uint24 addr) -> buint8;
  auto write(uint24 addr, buint8 data) -> void;

  auto main() -> void;
  auto enable() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  buint8 wram[128 * 1024];
  vector<Thread*> coprocessors;

private:
  //cpu
  static auto Enter() -> void;

  //timing
  auto queue_event(uint id) -> void;
  auto lastCycle() -> void;
  auto add_clocks(uint clocks) -> void;
  auto scanline() -> void;
  auto run_auto_joypad_poll() -> void;

  struct QueueEvent {
    enum : uint {
      DramRefresh,
      HdmaRun,
    };
  };
  nall::priority_queue<uint> queue;

  //memory
  auto speed(uint addr) const -> uint;

  //dma
  auto dma_transfer_valid(buint8 bbus, uint abus) -> bool;
  auto dma_addr_valid(uint abus) -> bool;
  auto dma_read(uint abus) -> buint8;
  auto dma_write(bool valid, uint addr, buint8 data) -> void;
  auto dma_transfer(bool direction, buint8 bbus, uint abus) -> void;
  auto dma_bbus(uint i, uint index) -> buint8;
  auto dma_addr(uint i) -> uint;
  auto hdma_addr(uint i) -> uint;
  auto hdma_iaddr(uint i) -> uint;
  auto dma_run() -> void;
  auto hdma_active_after(uint i) -> bool;
  auto hdma_update(uint i) -> void;
  auto hdma_run() -> void;
  auto hdma_init() -> void;
  auto dma_reset() -> void;

  //registers
  buint8 port_data[4];

  struct Channel {
    bool dma_enabled;
    bool hdma_enabled;

    bool direction;
    bool indirect;
    bool unused;
    bool reverse_transfer;
    bool fixed_transfer;
    buint8 transfer_mode;

    buint8 dest_addr;
    buint16 source_addr;
    buint8 source_bank;

    union {
      uint16_t transfer_size;
      uint16_t indirect_addr;
    };

    buint8 indirect_bank;
    buint16 hdma_addr;
    buint8 line_counter;
    buint8 unknown;

    bool hdma_completed;
    bool hdma_do_transfer;
  } channel[8];

  struct Status {
    bool nmi_valid;
    bool nmi_line;
    bool nmi_transition;
    bool nmi_pending;

    bool irq_valid;
    bool irq_line;
    bool irq_transition;
    bool irq_pending;

    bool irq_lock;
    bool hdma_pending;

    uint wram_addr;

    bool joypad_strobe_latch;

    bool nmi_enabled;
    bool virq_enabled;
    bool hirq_enabled;
    bool auto_joypad_poll_enabled;

    buint8 pio;

    buint8 wrmpya;
    buint8 wrmpyb;
    buint16 wrdiva;
    buint8 wrdivb;

    buint16 htime;
    buint16 vtime;

    uint rom_speed;

    buint16 rddiv;
    buint16 rdmpy;

    buint8 joy1l, joy1h;
    buint8 joy2l, joy2h;
    buint8 joy3l, joy3h;
    buint8 joy4l, joy4h;
  } status;
};

extern CPU cpu;
