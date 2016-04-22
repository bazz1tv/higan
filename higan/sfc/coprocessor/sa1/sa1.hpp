struct SA1 : Processor::R65816, public Coprocessor {
  #include "bus/bus.hpp"
  #include "dma/dma.hpp"
  #include "memory/memory.hpp"
  #include "mmio/mmio.hpp"

  struct Status {
    buint8 tick_counter;

    bool interrupt_pending;

    buint16 scanlines;
    buint16 vcounter;
    buint16 hcounter;
  } status;

  static auto Enter() -> void;
  auto main() -> void;
  auto tick() -> void;
  auto interrupt() -> void override;

  alwaysinline auto trigger_irq() -> void;
  alwaysinline auto lastCycle() -> void override;
  alwaysinline auto interruptPending() const -> bool override;

  auto init() -> void;
  auto load() -> void;
  auto unload() -> void;
  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  MappedRAM rom;
  MappedRAM iram;
  MappedRAM bwram;
};

extern SA1 sa1;
