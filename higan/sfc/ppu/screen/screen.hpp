struct Screen {
  buint32* line;

  struct Regs {
    bool addsub_mode;
    bool direct_color;

    bool color_mode;
    bool color_halve;
    bool bg1_color_enable;
    bool bg2_color_enable;
    bool bg3_color_enable;
    bool bg4_color_enable;
    bool oam_color_enable;
    bool back_color_enable;

    uint5 color_b;
    uint5 color_g;
    uint5 color_r;
  } regs;

  struct Math {
    struct Layer {
      buint16 color;
      bool color_enable;
    } main, sub;
    bool transparent;
    bool addsub_mode;
    bool color_halve;
  } math;

  Screen(PPU& self);

  auto scanline() -> void;
  alwaysinline auto run() -> void;
  auto reset() -> void;

  auto get_pixel_sub(bool hires) -> buint16;
  auto get_pixel_main() -> buint16;
  auto addsub(uint x, uint y) -> buint16;
  alwaysinline auto get_color(uint palette) -> buint16;
  alwaysinline auto get_direct_color(uint palette, uint tile) -> buint16;
  alwaysinline auto fixed_color() const -> buint16;

  auto serialize(serializer&) -> void;

  PPU& self;
  friend class PPU;
};
