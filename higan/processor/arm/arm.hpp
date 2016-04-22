#pragma once

namespace Processor {

//Supported Models:
//* ARMv3  (ARM60)
//* ARMv4T (ARM7TDMI)

struct ARM {
  enum : unsigned {       //mode flags for bus_read, bus_write:
    Nonsequential =   1,  //N cycle
    Sequential    =   2,  //S cycle
    Prefetch      =   4,  //instruction fetch (eligible for prefetch)
    Byte          =   8,  //8-bit access
    Half          =  16,  //16-bit access
    Word          =  32,  //32-bit access
    Load          =  64,  //load operation
    Store         = 128,  //store operation
    Signed        = 256,  //sign extend
  };

  #include "registers.hpp"
  #include "instructions-arm.hpp"
  #include "instructions-thumb.hpp"
  #include "disassembler.hpp"

  virtual auto step(unsigned clocks) -> void = 0;
  virtual auto bus_idle() -> void = 0;
  virtual auto bus_read(unsigned mode, buint32 addr) -> buint32 = 0;
  virtual auto bus_write(unsigned mode, buint32 addr, buint32 word) -> void = 0;

  //arm.cpp
  auto power() -> void;
  auto exec() -> void;
  auto idle() -> void;
  auto read(unsigned mode, buint32 addr) -> buint32;
  auto load(unsigned mode, buint32 addr) -> buint32;
  auto write(unsigned mode, buint32 addr, buint32 word) -> void;
  auto store(unsigned mode, buint32 addr, buint32 word) -> void;
  auto vector(buint32 addr, Processor::Mode mode) -> void;

  //algorithms.cpp
  auto condition(uint4 condition) -> bool;
  auto bit(buint32 result) -> buint32;
  auto add(buint32 source, buint32 modify, bool carry) -> buint32;
  auto sub(buint32 source, buint32 modify, bool carry) -> buint32;
  auto mul(buint32 product, buint32 multiplicand, buint32 multiplier) -> buint32;
  auto lsl(buint32 source, buint8 shift) -> buint32;
  auto lsr(buint32 source, buint8 shift) -> buint32;
  auto asr(buint32 source, buint8 shift) -> buint32;
  auto ror(buint32 source, buint8 shift) -> buint32;
  auto rrx(buint32 source) -> buint32;

  //step.cpp
  auto pipeline_step() -> void;
  auto arm_step() -> void;
  auto thumb_step() -> void;

  //serialization.cpp
  auto serialize(serializer&) -> void;

  bool trace = false;
  uintmax_t instructions = 0;
};

}
