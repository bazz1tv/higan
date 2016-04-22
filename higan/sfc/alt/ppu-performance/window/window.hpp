struct LayerWindow {
  auto render(bool screen) -> void;
  auto serialize(serializer&) -> void;

  bool one_enable;
  bool one_invert;
  bool two_enable;
  bool two_invert;

  uint mask;

  bool main_enable;
  bool sub_enable;

  buint8 main[256];
  buint8 sub[256];
};

struct ColorWindow {
  auto render(bool screen) -> void;
  auto serialize(serializer&) -> void;

  bool one_enable;
  bool one_invert;
  bool two_enable;
  bool two_invert;

  uint mask;

  uint main_mask;
  uint sub_mask;

  buint8 main[256];
  buint8 sub[256];
};
