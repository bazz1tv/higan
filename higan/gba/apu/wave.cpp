auto APU::Wave::run() -> void {
  if(period && --period == 0) {
    period = 1 * (2048 - frequency);
    patternsample = pattern[patternbank * 16 + patternaddr++];
    if(patternaddr == 0) patternbank ^= mode;
  }

  output = patternsample;
  static uint multiplier[] = {0, 4, 2, 1, 3, 3, 3, 3};
  output = (output * multiplier[volume]) / 4;
  if(enable == false) output = 0;
}

auto APU::Wave::clocklength() -> void {
  if(enable && counter) {
    if(++length == 0) enable = false;
  }
}

auto APU::Wave::read(uint addr) const -> buint8 {
  switch(addr) {
  case 0: return (mode << 5) | (bank << 6) | (dacenable << 7);
  case 1: return 0;
  case 2: return (volume << 5);
  case 3: return 0;
  case 4: return (counter << 6);
  }
}

auto APU::Wave::write(uint addr, buint8 byte) -> void {
  switch(addr) {
  case 0:  //NR30
    mode      = byte >> 5;
    bank      = byte >> 6;
    dacenable = byte >> 7;
    if(dacenable == false) enable = false;
    break;

  case 1:  //NR31
    length = byte >> 0;
    break;

  case 2:  //NR32
    volume = byte >> 5;
    break;

  case 3:  //NR33
    frequency = (frequency & 0xff00) | (byte << 0);
    break;

  case 4:  //NR34
    frequency = (frequency & 0x00ff) | (byte << 8);
    counter    = byte >> 6;
    initialize = byte >> 7;

    if(initialize) {
      enable = dacenable;
      period = 1 * (2048 - frequency);
      patternaddr = 0;
      patternbank = mode ? (uint1)0 : bank;
    }

    break;
  }
}

auto APU::Wave::readram(uint addr) const -> buint8 {
  buint8 byte = 0;
  byte |= pattern[addr * 2 + 0] << 0;
  byte |= pattern[addr * 2 + 1] << 4;
  return byte;
}

auto APU::Wave::writeram(uint addr, buint8 byte) -> void {
  pattern[addr * 2 + 0] = byte >> 0;
  pattern[addr * 2 + 1] = byte >> 4;
}

auto APU::Wave::power() -> void {
  mode = 0;
  bank = 0;
  dacenable = 0;
  length = 0;
  volume = 0;
  frequency = 0;
  counter = 0;
  initialize = 0;
  for(auto& sample : pattern) sample = 0;
  enable = 0;
  output = 0;
  patternaddr = 0;
  patternbank = 0;
  patternsample = 0;
  period = 0;
}
