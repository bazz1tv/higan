//NEC uPD7720 (not supported)
//NEC uPD7725
//NEC uPD96050

#pragma once

namespace Processor {

struct uPD96050 {
  auto power() -> void;
  auto exec() -> void;
  auto serialize(serializer&) -> void;

  auto execOP(uint24 opcode) -> void;
  auto execRT(uint24 opcode) -> void;
  auto execJP(uint24 opcode) -> void;
  auto execLD(uint24 opcode) -> void;

  auto readSR() -> buint8;
  auto writeSR(buint8 data) -> void;

  auto readDR() -> buint8;
  auto writeDR(buint8 data) -> void;

  auto readDP(uint12 addr) -> buint8;
  auto writeDP(uint12 addr, buint8 data) -> void;

  auto disassemble(uint14 ip) -> string;

  enum class Revision : uint { uPD7725, uPD96050 } revision;
  uint24 programROM[16384];
  buint16 dataROM[2048];
  buint16 dataRAM[2048];

  //registers.cpp
  struct Flag {
    inline operator uint() const;
    inline auto operator=(uint d) -> uint;

    bool s1, s0, c, z, ov1, ov0;
  };

  struct Status {
    inline operator uint() const;
    inline auto operator=(uint d) -> uint;

    bool rqm, usf1, usf0, drs, dma, drc, soc, sic, ei, p1, p0;
  };

  struct Regs {
    buint16 stack[16];    //LIFO
    VariadicNatural pc;  //program counter
    VariadicNatural rp;  //ROM pointer
    VariadicNatural dp;  //data pointer
    uint4 sp;            //stack pointer
    int16 k;
    int16 l;
    int16 m;
    int16 n;
    int16 a;             //accumulator
    int16 b;             //accumulator
    Flag flaga;
    Flag flagb;
    buint16 tr;           //temporary register
    buint16 trb;          //temporary register
    Status sr;           //status register
    buint16 dr;           //data register
    buint16 si;
    buint16 so;
  } regs;
};

}
