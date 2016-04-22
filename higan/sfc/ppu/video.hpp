struct Video {
  Video();

  auto reset() -> void;
  auto refresh() -> void;

private:
  auto drawCursor(buint32 color, int x, int y) -> void;
  auto drawCursors() -> void;

  unique_pointer<buint32[]> output;
  unique_pointer<buint32[]> paletteLiteral;
  unique_pointer<buint32[]> paletteStandard;
  unique_pointer<buint32[]> paletteEmulation;
};

extern Video video;
