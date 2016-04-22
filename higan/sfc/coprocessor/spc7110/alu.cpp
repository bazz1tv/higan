auto SPC7110::alu_multiply() -> void {
  add_clocks(30);

  if(r482e & 1) {
    //signed 16-bit x 16-bit multiplication
    int16 r0 = (int16)(r4824 | r4825 << 8);
    int16 r1 = (int16)(r4820 | r4821 << 8);

    int result = r0 * r1;
    r4828 = result;
    r4829 = result >> 8;
    r482a = result >> 16;
    r482b = result >> 24;
  } else {
    //unsigned 16-bit x 16-bit multiplication
    buint16 r0 = (buint16)(r4824 | r4825 << 8);
    buint16 r1 = (buint16)(r4820 | r4821 << 8);

    uint result = r0 * r1;
    r4828 = result;
    r4829 = result >> 8;
    r482a = result >> 16;
    r482b = result >> 24;
  }

  r482f &= 0x7f;
}

auto SPC7110::alu_divide() -> void {
  add_clocks(40);

  if(r482e & 1) {
    //signed 32-bit x 16-bit division
    int32 dividend = (int32)(r4820 | r4821 << 8 | r4822 << 16 | r4823 << 24);
    int16 divisor  = (int16)(r4826 | r4827 << 8);

    int32 quotient;
    int16 remainder;

    if(divisor) {
      quotient  = (int32)(dividend / divisor);
      remainder = (int32)(dividend % divisor);
    } else {
      //illegal division by zero
      quotient  = 0;
      remainder = dividend;
    }

    r4828 = quotient;
    r4829 = quotient >> 8;
    r482a = quotient >> 16;
    r482b = quotient >> 24;

    r482c = remainder;
    r482d = remainder >> 8;
  } else {
    //unsigned 32-bit x 16-bit division
    buint32 dividend = (buint32)(r4820 | r4821 << 8 | r4822 << 16 | r4823 << 24);
    buint16 divisor  = (buint16)(r4826 | r4827 << 8);

    buint32 quotient;
    buint16 remainder;

    if(divisor) {
      quotient  = (buint32)(dividend / divisor);
      remainder = (buint16)(dividend % divisor);
    } else {
      //illegal division by zero
      quotient  = 0;
      remainder = dividend;
    }

    r4828 = quotient;
    r4829 = quotient >> 8;
    r482a = quotient >> 16;
    r482b = quotient >> 24;

    r482c = remainder;
    r482d = remainder >> 8;
  }

  r482f &= 0x7f;
}
