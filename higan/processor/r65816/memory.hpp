alwaysinline auto readpc() -> buint8 {
  return read((regs.pc.b << 16) + regs.pc.w++);
}

alwaysinline auto readstack() -> buint8 {
  regs.e ? regs.s.l++ : regs.s.w++;
  return read(regs.s.w);
}

alwaysinline auto readstackn() -> buint8 {
  return read(++regs.s.w);
}

alwaysinline auto readaddr(buint32 addr) -> buint8 {
  return read(addr & 0xffff);
}

alwaysinline auto readlong(buint32 addr) -> buint8 {
  return read(addr & 0xffffff);
}

alwaysinline auto readdbr(buint32 addr) -> buint8 {
  return read(((regs.db << 16) + addr) & 0xffffff);
}

alwaysinline auto readpbr(buint32 addr) -> buint8 {
  return read((regs.pc.b << 16) + (addr & 0xffff));
}

alwaysinline auto readdp(buint32 addr) -> buint8 {
  if(regs.e && regs.d.l == 0x00) {
    return read((regs.d & 0xff00) + ((regs.d + (addr & 0xffff)) & 0xff));
  } else {
    return read((regs.d + (addr & 0xffff)) & 0xffff);
  }
}

alwaysinline auto readsp(buint32 addr) -> buint8 {
  return read((regs.s + (addr & 0xffff)) & 0xffff);
}

alwaysinline auto writestack(buint8 data) -> void {
  write(regs.s.w, data);
  regs.e ? regs.s.l-- : regs.s.w--;
}

alwaysinline auto writestackn(buint8 data) -> void {
  write(regs.s.w--, data);
}

alwaysinline auto writeaddr(buint32 addr, buint8 data) -> void {
  write(addr & 0xffff, data);
}

alwaysinline auto writelong(buint32 addr, buint8 data) -> void {
  write(addr & 0xffffff, data);
}

alwaysinline auto writedbr(buint32 addr, buint8 data) -> void {
  write(((regs.db << 16) + addr) & 0xffffff, data);
}

alwaysinline auto writepbr(buint32 addr, buint8 data) -> void {
  write((regs.pc.b << 16) + (addr & 0xffff), data);
}

alwaysinline auto writedp(buint32 addr, buint8 data) -> void {
  if(regs.e && regs.d.l == 0x00) {
    write((regs.d & 0xff00) + ((regs.d + (addr & 0xffff)) & 0xff), data);
  } else {
    write((regs.d + (addr & 0xffff)) & 0xffff, data);
  }
}

alwaysinline auto writesp(buint32 addr, buint8 data) -> void {
  write((regs.s + (addr & 0xffff)) & 0xffff, data);
}
