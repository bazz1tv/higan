//ARMv3 (ARM60)

struct ArmDSP : Processor::ARM, Coprocessor {
  #include "registers.hpp"

  ArmDSP();
  ~ArmDSP();

  static auto Enter() -> void;
  auto boot() -> void;
  auto main() -> void;

  auto step(uint clocks) -> void override;
  auto bus_idle() -> void override;
  auto bus_read(uint mode, buint32 addr) -> buint32 override;
  auto bus_write(uint mode, buint32 addr, buint32 word) -> void override;

  auto mmio_read(uint24 addr, buint8 data) -> buint8;
  auto mmio_write(uint24 addr, buint8 data) -> void;

  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;
  auto resetARM() -> void;

  auto firmware() const -> nall::vector<buint8>;
  auto serialize(serializer&) -> void;

  buint8* programROM;
  buint8* dataROM;
  buint8* programRAM;
};

extern ArmDSP armdsp;
