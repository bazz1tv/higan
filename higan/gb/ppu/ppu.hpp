#include "video.hpp"

struct PPU : Thread, MMIO {
  static auto Enter() -> void;
  auto main() -> void;
  auto add_clocks(uint clocks) -> void;

  auto hflip(uint data) const -> uint;

  //mmio.cpp
  auto vram_addr(buint16 addr) const -> uint;
  auto mmio_read(buint16 addr) -> buint8;
  auto mmio_write(buint16 addr, buint8 data) -> void;

  //dmg.cpp
  auto dmg_read_tile(bool select, uint x, uint y, uint& data) -> void;
  auto dmg_scanline() -> void;
  auto dmg_run() -> void;
  auto dmg_run_bg() -> void;
  auto dmg_run_window() -> void;
  auto dmg_run_ob() -> void;

  //cgb.cpp
  auto cgb_read_tile(bool select, uint x, uint y, uint& attr, uint& data) -> void;
  auto cgb_scanline() -> void;
  auto cgb_run() -> void;
  auto cgb_run_bg() -> void;
  auto cgb_run_window() -> void;
  auto cgb_run_ob() -> void;

  auto power() -> void;

  auto serialize(serializer&) -> void;

  buint8 vram[16384];  //GB = 8192, GBC = 16384
  buint8 oam[160];
  buint8 bgp[4];
  buint8 obp[2][4];
  buint8 bgpd[64];
  buint8 obpd[64];

  function<auto () -> void> scanline;
  function<auto () -> void> run;

  struct Status {
    uint lx;

    //$ff40  LCDC
    bool display_enable;
    bool window_tilemap_select;
    bool window_display_enable;
    bool bg_tiledata_select;
    bool bg_tilemap_select;
    bool ob_size;
    bool ob_enable;
    bool bg_enable;

    //$ff41  STAT
    bool interrupt_lyc;
    bool interrupt_oam;
    bool interrupt_vblank;
    bool interrupt_hblank;

    //$ff42  SCY
    buint8 scy;

    //$ff43  SCX
    buint8 scx;

    //$ff44  LY
    buint8 ly;

    //$ff45  LYC
    buint8 lyc;

    //$ff46  DMA
    bool dma_active;
    uint dma_clock;
    buint8 dma_bank;

    //$ff4a  WY
    buint8 wy;

    //$ff4b  WX
    buint8 wx;

    //$ff4f  VBK
    bool vram_bank;

    //$ff68  BGPI
    bool bgpi_increment;
    uint6 bgpi;

    //$ff6a  OBPI
    bool obpi_increment;
    buint8 obpi;
  } status;

  buint32 screen[160 * 144];

  struct Pixel {
    buint16 color;
    buint8 palette;
    bool priority;
  };
  Pixel bg;
  Pixel ob;

  struct Sprite {
    uint x;
    uint y;
    uint tile;
    uint attr;
    uint data;
  };
  Sprite sprite[10];
  uint sprites;

  uint px;

  struct Background {
    uint attr;
    uint data;
  };
  Background background;
  Background window;
};

extern PPU ppu;
