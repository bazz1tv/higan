alwaysinline auto op_readpc() -> buint8 {
  return op_read(regs.pc++);
}

alwaysinline auto op_readsp() -> buint8 {
  return op_read(0x0100 | ++regs.s);
}

alwaysinline auto op_writesp(buint8 data) -> void {
  return op_write(0x0100 | regs.s--, data);
}

alwaysinline auto op_readdp(buint8 addr) -> buint8 {
  return op_read((regs.p.p << 8) + addr);
}

alwaysinline auto op_writedp(buint8 addr, buint8 data) -> void {
  return op_write((regs.p.p << 8) + addr, data);
}
