struct DMC {
  auto start() -> void;
  auto stop() -> void;
  auto clock() -> buint8;

  auto power() -> void;
  auto reset() -> void;

  auto serialize(serializer&) -> void;

  uint length_counter;
  bool irq_pending;

  uint4 period;
  uint period_counter;

  bool irq_enable;
  bool loop_mode;

  buint8 dac_latch;
  buint8 addr_latch;
  buint8 length_latch;

  uint15 read_addr;
  uint dma_delay_counter;

  uint3 bit_counter;
  bool have_dma_buffer;
  buint8 dma_buffer;

  bool have_sample;
  buint8 sample;
} dmc;
