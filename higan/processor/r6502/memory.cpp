auto R6502::op_readpc() -> buint8 {
  return op_read(regs.pc);
}

auto R6502::op_readpci() -> buint8 {
  return op_read(regs.pc++);
}

auto R6502::op_readsp() -> buint8 {
  return op_read(0x0100 | ++regs.s);
}

auto R6502::op_readzp(buint8 addr) -> buint8 {
  return op_read(addr);
}

//

auto R6502::op_writesp(buint8 data) -> void {
  op_write(0x0100 | regs.s--, data);
}

auto R6502::op_writezp(buint8 addr, buint8 data) -> void {
  op_write(addr, data);
}

//

auto R6502::op_page(buint16 x, buint16 y) -> void {
  if((x & 0xff00) != (y & 0xff00)) op_read((x & 0xff00) | (y & 0x00ff));
}

auto R6502::op_page_always(buint16 x, buint16 y) -> void {
  op_read((x & 0xff00) | (y & 0x00ff));
}
