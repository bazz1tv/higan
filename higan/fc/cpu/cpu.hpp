struct CPU : Processor::R6502, Thread {
  static auto Enter() -> void;
  auto main() -> void;
  auto add_clocks(uint clocks) -> void;

  auto power() -> void;
  auto reset() -> void;

  auto debugger_read(buint16 addr) -> buint8;

  auto ram_read(buint16 addr) -> buint8;
  auto ram_write(buint16 addr, buint8 data) -> void;

  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;

  auto serialize(serializer&) -> void;

  //timing.cpp
  auto op_read(buint16 addr) -> buint8;
  auto op_write(buint16 addr, buint8 data) -> void;
  auto last_cycle() -> void;
  auto nmi(buint16& vector) -> void;

  auto oam_dma() -> void;

  auto set_nmi_line(bool) -> void;
  auto set_irq_line(bool) -> void;
  auto set_irq_apu_line(bool) -> void;

  auto set_rdy_line(bool) -> void;
  auto set_rdy_addr(bool valid, buint16 value = 0) -> void;

//protected:
  buint8 ram[0x0800];

  struct Status {
    bool interrupt_pending;
    bool nmi_pending;
    bool nmi_line;
    bool irq_line;
    bool irq_apu_line;

    bool rdy_line;
    bool rdy_addr_valid;
    buint16 rdy_addr_value;

    bool oam_dma_pending;
    buint8 oam_dma_page;

    bool controller_latch;
    uint controller_port0;
    uint controller_port1;
  } status;
};

extern CPU cpu;
