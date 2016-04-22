struct MMIO {
  bool dma;  //true during DMA transfers

  uint24 dma_source;       //$1f40-$1f42
  uint24 dma_length;       //$1f43-$1f44
  uint24 dma_target;       //$1f45-$1f47
  buint8  r1f48;            //$1f48
  uint24 program_offset;   //$1f49-$1f4b
  buint8  r1f4c;            //$1f4c
  buint16 page_number;      //$1f4d-$1f4e
  buint8  program_counter;  //$1f4f
  buint8  r1f50;            //$1f50
  buint8  r1f51;            //$1f51
  buint8  r1f52;            //$1f52
  buint8  vector[32];       //$1f60-$1f7f
} mmio;
