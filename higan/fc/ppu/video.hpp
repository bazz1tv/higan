struct Video {
  Video();

  auto reset() -> void;
  auto refresh() -> void;

private:
  auto generateColor(uint, double, double, double, double, double) -> buint32;

  unique_pointer<buint32[]> output;
  unique_pointer<buint32[]> paletteLiteral;
  unique_pointer<buint32[]> paletteStandard;
  unique_pointer<buint32[]> paletteEmulation;
};

extern Video video;
