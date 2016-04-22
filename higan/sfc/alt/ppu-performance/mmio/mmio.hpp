public:
  auto mmio_read(uint addr, buint8 data) -> buint8;
  auto mmio_write(uint addr, buint8 data) -> void;

private:

struct Regs {
  //internal
  buint8 ppu1_mdr;
  buint8 ppu2_mdr;

  buint16 vram_readbuffer;
  buint8 oam_latchdata;
  buint8 cgram_latchdata;
  buint8 bgofs_latchdata;
  buint8 mode7_latchdata;

  bool counters_latched;
  bool latch_hcounter;
  bool latch_vcounter;

  //$2100
  bool display_disable;
  uint display_brightness;

  //$2102-$2103
  buint16 oam_baseaddr;
  buint16 oam_addr;
  bool oam_priority;

  //$2105
  bool bg3_priority;
  uint bgmode;

  //$210d
  buint16 mode7_hoffset;

  //$210e
  buint16 mode7_voffset;

  //$2115
  bool vram_incmode;
  uint vram_mapping;
  uint vram_incsize;

  //$2116-$2117
  buint16 vram_addr;

  //$211a
  uint mode7_repeat;
  bool mode7_vflip;
  bool mode7_hflip;

  //$211b-$2120
  buint16 m7a;
  buint16 m7b;
  buint16 m7c;
  buint16 m7d;
  buint16 m7x;
  buint16 m7y;

  //$2121
  buint16 cgram_addr;

  //$2126-$212a
  uint window_one_left;
  uint window_one_right;
  uint window_two_left;
  uint window_two_right;

  //$2133
  bool mode7_extbg;
  bool pseudo_hires;
  bool overscan;
  bool interlace;

  //$213c
  buint16 hcounter;

  //$213d
  buint16 vcounter;
} regs;

auto get_vram_addr() -> buint16;
auto vram_read(uint addr) -> buint8;
auto vram_write(uint addr, buint8 data) -> void;

auto oam_read(uint addr) -> buint8;
auto oam_write(uint addr, buint8 data) -> void;

auto cgram_read(uint addr) -> buint8;
auto cgram_write(uint addr, buint8 data) -> void;

auto mmio_update_video_mode() -> void;
auto mmio_reset() -> void;
