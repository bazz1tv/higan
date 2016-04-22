struct CPU : Processor::R65816, Thread, public PPUcounter {
  enum : bool { Threaded = true };

  auto interruptPending() const -> bool override;
  auto pio() const -> buint8;
  auto joylatch() const -> bool;

  CPU();

  alwaysinline auto step(uint clocks) -> void;
  alwaysinline auto synchronizeSMP() -> void;
  auto synchronizePPU() -> void;
  auto synchronizeCoprocessors() -> void;
  auto synchronizeDevices() -> void;

  auto portRead(uint2 port) const -> buint8;
  auto portWrite(uint2 port, buint8 data) -> void;

  static auto Enter() -> void;
  auto main() -> void;
  auto enable() -> void;
  auto power() -> void;
  auto reset() -> void;

  //dma.cpp
  auto dmaAddClocks(uint clocks) -> void;
  auto dmaTransferValid(buint8 bbus, uint24 abus) -> bool;
  auto dmaAddressValid(uint24 abus) -> bool;
  auto dmaRead(uint24 abus) -> buint8;
  auto dmaWrite(bool valid, uint addr = 0, buint8 data = 0) -> void;
  auto dmaTransfer(bool direction, buint8 bbus, uint24 abus) -> void;

  auto dmaAddressB(uint n, uint channel) -> buint8;
  auto dmaAddress(uint n) -> uint24;
  auto hdmaAddress(uint n) -> uint24;
  auto hdmaIndirectAddress(uint n) -> uint24;

  auto dmaEnabledChannels() -> uint;
  auto hdmaActive(uint n) -> bool;
  auto hdmaActiveAfter(uint s) -> bool;
  auto hdmaEnabledChannels() -> uint;
  auto hdmaActiveChannels() -> uint;

  auto dmaRun() -> void;
  auto hdmaUpdate(uint n) -> void;
  auto hdmaRun() -> void;
  auto hdmaInitReset() -> void;
  auto hdmaInit() -> void;

  //memory.cpp
  auto io() -> void override;
  auto read(uint24 addr) -> buint8 override;
  auto write(uint24 addr, buint8 data) -> void override;
  alwaysinline auto speed(uint24 addr) const -> uint;
  auto disassemblerRead(uint24 addr) -> buint8 override;

  //mmio.cpp
  auto apuPortRead(uint24 addr, buint8 data) -> buint8;
  auto cpuPortRead(uint24 addr, buint8 data) -> buint8;
  auto dmaPortRead(uint24 addr, buint8 data) -> buint8;
  auto apuPortWrite(uint24 addr, buint8 data) -> void;
  auto cpuPortWrite(uint24 addr, buint8 data) -> void;
  auto dmaPortWrite(uint24 addr, buint8 data) -> void;

  //timing.cpp
  auto dmaCounter() const -> uint;

  auto addClocks(uint clocks) -> void;
  auto scanline() -> void;

  alwaysinline auto aluEdge() -> void;
  alwaysinline auto dmaEdge() -> void;
  alwaysinline auto lastCycle() -> void;

  //irq.cpp
  alwaysinline auto pollInterrupts() -> void;
  auto nmitimenUpdate(buint8 data) -> void;
  auto rdnmi() -> bool;
  auto timeup() -> bool;

  alwaysinline auto nmiTest() -> bool;
  alwaysinline auto irqTest() -> bool;

  //joypad.cpp
  auto stepAutoJoypadPoll() -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  buint8 wram[128 * 1024];
  vector<Thread*> coprocessors;

privileged:
  uint cpu_version = 2;  //allowed: 1, 2

  struct Status {
    bool interrupt_pending;

    uint clock_count;
    uint line_clocks;

    //timing
    bool irq_lock;

    uint dram_refresh_position;
    bool dram_refreshed;

    uint hdma_init_position;
    bool hdma_init_triggered;

    uint hdma_position;
    bool hdma_triggered;

    bool nmi_valid;
    bool nmi_line;
    bool nmi_transition;
    bool nmi_pending;
    bool nmi_hold;

    bool irq_valid;
    bool irq_line;
    bool irq_transition;
    bool irq_pending;
    bool irq_hold;

    bool power_pending;
    bool reset_pending;

    //DMA
    bool dma_active;
    uint dma_counter;
    uint dma_clocks;
    bool dma_pending;
    bool hdma_pending;
    bool hdma_mode;  //0 = init, 1 = run

    //auto joypad polling
    bool auto_joypad_active;
    bool auto_joypad_latch;
    uint auto_joypad_counter;
    uint auto_joypad_clock;

    //MMIO
    //$2140-217f
    buint8 port[4];

    //$2181-$2183
    uint17 wram_addr;

    //$4016-$4017
    bool joypad_strobe_latch;
    buint32 joypad1_bits;
    buint32 joypad2_bits;

    //$4200
    bool nmi_enabled;
    bool hirq_enabled, virq_enabled;
    bool auto_joypad_poll;

    //$4201
    buint8 pio;

    //$4202-$4203
    buint8 wrmpya;
    buint8 wrmpyb;

    //$4204-$4206
    buint16 wrdiva;
    buint8 wrdivb;

    //$4207-$420a
    uint9 hirq_pos;
    uint9 virq_pos;

    //$420d
    uint rom_speed;

    //$4214-$4217
    buint16 rddiv;
    buint16 rdmpy;

    //$4218-$421f
    buint16 joy1;
    buint16 joy2;
    buint16 joy3;
    buint16 joy4;
  } status;

  struct ALU {
    uint mpyctr;
    uint divctr;
    uint shift;
  } alu;

  struct Channel {
    //$420b
    bool dma_enabled;

    //$420c
    bool hdma_enabled;

    //$43x0
    bool direction;
    bool indirect;
    bool unused;
    bool reverse_transfer;
    bool fixed_transfer;
    uint3 transfer_mode;

    //$43x1
    buint8 dest_addr;

    //$43x2-$43x3
    buint16 source_addr;

    //$43x4
    buint8 source_bank;

    //$43x5-$43x6
    union {
      uint16_t transfer_size;
      uint16_t indirect_addr;
    };

    //$43x7
    buint8 indirect_bank;

    //$43x8-$43x9
    buint16 hdma_addr;

    //$43xa
    buint8 line_counter;

    //$43xb/$43xf
    buint8 unknown;

    //internal state
    bool hdma_completed;
    bool hdma_do_transfer;
  } channel[8];

  struct Pipe {
    bool valid;
    uint addr;
    buint8 data;
  } pipe;

  struct Debugger {
    hook<auto (uint24) -> void> op_exec;
    hook<auto (uint24, buint8) -> void> op_read;
    hook<auto (uint24, buint8) -> void> op_write;
    hook<auto () -> void> op_nmi;
    hook<auto () -> void> op_irq;
  } debugger;
};

extern CPU cpu;
