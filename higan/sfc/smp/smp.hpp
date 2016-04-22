//Sony CXP1100Q-1

struct SMP : Processor::SPC700, Thread {
  enum : bool { Threaded = true };

  alwaysinline auto step(uint clocks) -> void;
  alwaysinline auto synchronizeCPU() -> void;
  alwaysinline auto synchronizeDSP() -> void;

  auto portRead(uint2 port) const -> buint8;
  auto portWrite(uint2 port, buint8 data) -> void;

  auto main() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  buint8 iplrom[64];
  buint8 apuram[64 * 1024];

privileged:
  struct {
    //timing
    uint clockCounter;
    uint dspCounter;
    uint timerStep;

    //$00f0
    buint8 clockSpeed;
    buint8 timerSpeed;
    bool timersEnable;
    bool ramDisable;
    bool ramWritable;
    bool timersDisable;

    //$00f1
    bool iplromEnable;

    //$00f2
    buint8 dspAddr;

    //$00f8,$00f9
    buint8 ram00f8;
    buint8 ram00f9;
  } status;

  static auto Enter() -> void;

  struct Debugger {
    hook<void (buint16)> op_exec;
    hook<void (buint16, buint8)> op_read;
    hook<void (buint16, buint8)> op_write;
  } debugger;

  //memory.cpp
  auto ramRead(buint16 addr) -> buint8;
  auto ramWrite(buint16 addr, buint8 data) -> void;

  auto busRead(buint16 addr) -> buint8;
  auto busWrite(buint16 addr, buint8 data) -> void;

  auto op_io() -> void;
  auto op_read(buint16 addr) -> buint8;
  auto op_write(buint16 addr, buint8 data) -> void;

  auto disassembler_read(buint16 addr) -> buint8;

  //timing.cpp
  template<unsigned Frequency>
  struct Timer {
    buint8 stage0;
    buint8 stage1;
    buint8 stage2;
    uint4 stage3;
    bool line;
    bool enable;
    buint8 target;

    auto tick() -> void;
    auto synchronizeStage1() -> void;
  };

  Timer<192> timer0;
  Timer<192> timer1;
  Timer< 24> timer2;

  alwaysinline auto addClocks(uint clocks) -> void;
  alwaysinline auto cycleEdge() -> void;
};

extern SMP smp;
