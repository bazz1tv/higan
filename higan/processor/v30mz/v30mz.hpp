//NEC V30MZ

#pragma once

namespace Processor {

struct V30MZ {
  using Size = uint;
  enum : uint { Byte = 1, Word = 2, Long = 4 };
  enum : uint {
    SegmentOverrideES  = 0x26,
    SegmentOverrideCS  = 0x2e,
    SegmentOverrideSS  = 0x36,
    SegmentOverrideDS  = 0x3e,
    Lock               = 0xf0,
    RepeatWhileNotZero = 0xf2,
    RepeatWhileZero    = 0xf3,
  };

  virtual auto wait(uint clocks = 1) -> void = 0;
  virtual auto read(uint20 addr) -> buint8 = 0;
  virtual auto write(uint20 addr, buint8 data) -> void = 0;
  virtual auto in(buint16 port) -> buint8 = 0;
  virtual auto out(buint16 port, buint8 data) -> void = 0;

  auto debug(string text) -> void;
  auto power() -> void;
  auto exec() -> void;
  auto interrupt(buint8 vector) -> void;
  auto instruction() -> void;

  //registers.cpp
  auto repeat() -> buint8;
  auto segment(buint16) -> buint16;

  auto getAcc(Size) -> buint32;
  auto setAcc(Size, buint32) -> void;

  //modrm.cpp
  auto modRM() -> void;

  auto getMem(Size, uint offset = 0) -> buint16;
  auto setMem(Size, buint16) -> void;

  auto getReg(Size) -> buint16;
  auto setReg(Size, buint16) -> void;

  auto getSeg() -> buint16;
  auto setSeg(buint16) -> void;

  //memory.cpp
  auto read(Size, buint16, buint16) -> buint32;
  auto write(Size, buint16, buint16, buint16) -> void;

  auto in(Size, buint16) -> buint16;
  auto out(Size, buint16, buint16) -> void;

  auto fetch(Size = Byte) -> buint16;
  auto pop() -> buint16;
  auto push(buint16) -> void;

  //algorithms.cpp
  auto parity(buint8) const -> bool;
  auto alAdc(Size, buint16, buint16) -> buint16;
  auto alAdd(Size, buint16, buint16) -> buint16;
  auto alAnd(Size, buint16, buint16) -> buint16;
  auto alDec(Size, buint16        ) -> buint16;
  auto alDiv(Size, buint32, buint32) -> buint32;
  auto alDivi(Size, int32,  int32) -> buint32;
  auto alInc(Size, buint16        ) -> buint16;
  auto alMul(Size, buint16, buint16) -> buint32;
  auto alMuli(Size, int16,  int16) -> buint32;
  auto alNeg(Size, buint16        ) -> buint16;
  auto alNot(Size, buint16        ) -> buint16;
  auto alOr (Size, buint16, buint16) -> buint16;
  auto alRcl(Size, buint16, uint5 ) -> buint16;
  auto alRcr(Size, buint16, uint5 ) -> buint16;
  auto alRol(Size, buint16, uint4 ) -> buint16;
  auto alRor(Size, buint16, uint4 ) -> buint16;
  auto alSal(Size, buint16, uint5 ) -> buint16;
  auto alSar(Size, buint16, uint5 ) -> buint16;
  auto alSbb(Size, buint16, buint16) -> buint16;
  auto alSub(Size, buint16, buint16) -> buint16;
  auto alShl(Size, buint16, uint5 ) -> buint16;
  auto alShr(Size, buint16, uint5 ) -> buint16;
  auto alXor(Size, buint16, buint16) -> buint16;

  //instructions-adjust.cpp
  auto opDecimalAdjust(bool);
  auto opAsciiAdjust(bool);
  auto opAdjustAfterMultiply();
  auto opAdjustAfterDivide();

  //instructions-alu.cpp
  auto opAddMemReg(Size);
  auto opAddRegMem(Size);
  auto opAddAccImm(Size);
  auto opOrMemReg(Size);
  auto opOrRegMem(Size);
  auto opOrAccImm(Size);
  auto opAdcMemReg(Size);
  auto opAdcRegMem(Size);
  auto opAdcAccImm(Size);
  auto opSbbMemReg(Size);
  auto opSbbRegMem(Size);
  auto opSbbAccImm(Size);
  auto opAndMemReg(Size);
  auto opAndRegMem(Size);
  auto opAndAccImm(Size);
  auto opSubMemReg(Size);
  auto opSubRegMem(Size);
  auto opSubAccImm(Size);
  auto opXorMemReg(Size);
  auto opXorRegMem(Size);
  auto opXorAccImm(Size);
  auto opCmpMemReg(Size);
  auto opCmpRegMem(Size);
  auto opCmpAccImm(Size);
  auto opTestMemReg(Size);
  auto opTestAcc(Size);
  auto opMultiplySignedRegMemImm(Size);
  auto opIncReg(uint16_t&);
  auto opDecReg(uint16_t&);
  auto opSignExtendByte();
  auto opSignExtendWord();

  //instructions-exec.cpp
  auto opLoop();
  auto opLoopWhile(bool);
  auto opJumpShort();
  auto opJumpIf(bool);
  auto opJumpNear();
  auto opJumpFar();
  auto opCallNear();
  auto opCallFar();
  auto opReturn();
  auto opReturnImm();
  auto opReturnFar();
  auto opReturnFarImm();
  auto opReturnInt();
  auto opInt3();
  auto opIntImm();
  auto opInto();
  auto opEnter();
  auto opLeave();
  auto opPushReg(uint16_t&);
  auto opPopReg(uint16_t&);
  auto opPushFlags();
  auto opPopFlags();
  auto opPushAll();
  auto opPopAll();
  auto opPushImm(Size);
  auto opPopMem();

  //instructions-flag.cpp
  auto opStoreFlagsAcc();
  auto opLoadAccFlags();
  auto opComplementCarry();
  auto opClearFlag(bool&);
  auto opSetFlag(bool&);

  //instructions-group.cpp
  auto opGroup1MemImm(Size, bool);
  auto opGroup2MemImm(Size, maybe<buint8> = {});
  auto opGroup3MemImm(Size);
  auto opGroup4MemImm(Size);

  //instructions-misc.cpp
  auto opSegment(buint16);
  auto opRepeat(bool);
  auto opLock();
  auto opWait();
  auto opHalt();
  auto opNop();
  auto opIn(Size);
  auto opOut(Size);
  auto opInDX(Size);
  auto opOutDX(Size);
  auto opTranslate();
  auto opBound();

  //instructions-move.cpp
  auto opMoveMemReg(Size);
  auto opMoveRegMem(Size);
  auto opMoveMemSeg();
  auto opMoveSegMem();
  auto opMoveAccMem(Size);
  auto opMoveMemAcc(Size);
  auto opMoveRegImm(uint8_t&);
  auto opMoveRegImm(uint16_t&);
  auto opMoveMemImm(Size);
  auto opExchange(uint16_t&, uint16_t&);
  auto opExchangeMemReg(Size);
  auto opLoadEffectiveAddressRegMem();
  auto opLoadSegmentMem(uint16_t&);

  //instructions-string.cpp
  auto opInString(Size);
  auto opOutString(Size);
  auto opMoveString(Size);
  auto opCompareString(Size);
  auto opStoreString(Size);
  auto opLoadString(Size);
  auto opScanString(Size);

  //serialization.cpp
  auto serialize(serializer&) -> void;

  //disassembler.cpp
  auto disassemble(buint16 cs, buint16 ip, bool registers = true, bool bytes = true) -> string;

  struct State {
    bool halt;    //set to true for hlt instruction; blocks execution until next interrupt
    bool poll;    //set to false to suppress interrupt polling between CPU instructions
    bool prefix;  //set to true for prefix instructions; prevents flushing of Prefix struct
  } state;

  buint8 opcode;
  vector<buint8> prefixes;

  struct ModRM {
    uint2 mod;
    uint3 reg;
    uint3 mem;

    buint16 segment;
    buint16 address;
  } modrm;

  struct Registers {
    union { uint16_t ax; struct { uint8_t order_lsb2(al, ah); }; };
    union { uint16_t cx; struct { uint8_t order_lsb2(cl, ch); }; };
    union { uint16_t dx; struct { uint8_t order_lsb2(dl, dh); }; };
    union { uint16_t bx; struct { uint8_t order_lsb2(bl, bh); }; };
    uint16_t sp;
    uint16_t bp;
    uint16_t si;
    uint16_t di;
    uint16_t es;
    uint16_t cs;
    uint16_t ss;
    uint16_t ds;
    uint16_t ip;

    uint8_t*  b[8]{&al, &cl, &dl, &bl, &ah, &ch, &dh, &bh};
    uint16_t* w[8]{&ax, &cx, &dx, &bx, &sp, &bp, &si, &di};
    uint16_t* s[8]{&es, &cs, &ss, &ds, &es, &cs, &ss, &ds};

    struct Flags {
      //registers.cpp
      operator uint16_t() const;
      auto operator=(uint16_t data);

      bool m;  //mode
      bool v;  //overflow
      bool d;  //direction
      bool i;  //interrupt
      bool b;  //break
      bool s;  //sign
      bool z;  //zero
      bool h;  //half-carry
      bool p;  //parity
      bool c;  //carry
    } f;
  } r;
};

}
