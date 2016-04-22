public:
  auto mmio_read(uint addr, buint8 data) -> buint8;
  auto mmio_write(uint addr, buint8 data) -> void;

privileged:
struct {
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

  uint10 oam_iaddr;
  uint9 cgram_iaddr;

  //$2100  INIDISP
  bool display_disable;
  uint4 display_brightness;

  //$2102  OAMADDL
  //$2103  OAMADDH
  uint10 oam_baseaddr;
  uint10 oam_addr;
  bool oam_priority;

  //$2105  BGMODE
  bool bg3_priority;
  buint8 bgmode;

  //$210d  BG1HOFS
  buint16 mode7_hoffset;

  //$210e  BG1VOFS
  buint16 mode7_voffset;

  //$2115  VMAIN
  bool vram_incmode;
  uint2 vram_mapping;
  buint8 vram_incsize;

  //$2116  VMADDL
  //$2117  VMADDH
  buint16 vram_addr;

  //$211a  M7SEL
  uint2 mode7_repeat;
  bool mode7_vflip;
  bool mode7_hflip;

  //$211b  M7A
  buint16 m7a;

  //$211c  M7B
  buint16 m7b;

  //$211d  M7C
  buint16 m7c;

  //$211e  M7D
  buint16 m7d;

  //$211f  M7X
  buint16 m7x;

  //$2120  M7Y
  buint16 m7y;

  //$2121  CGADD
  uint9 cgram_addr;

  //$2133  SETINI
  bool mode7_extbg;
  bool pseudo_hires;
  bool overscan;
  bool interlace;

  //$213c  OPHCT
  buint16 hcounter;

  //$213d  OPVCT
  buint16 vcounter;
} regs;

alwaysinline auto get_vram_address() -> buint16;
alwaysinline auto vram_read(uint addr) -> buint8;
alwaysinline auto vram_write(uint addr, buint8 data) -> void;
alwaysinline auto oam_read(uint addr) -> buint8;
alwaysinline auto oam_write(uint addr, buint8 data) -> void;
alwaysinline auto cgram_read(uint addr) -> buint8;
alwaysinline auto cgram_write(uint addr, buint8 data) -> void;

auto mmio_update_video_mode() -> void;

auto mmio_w2100(buint8) -> void;  //INIDISP
auto mmio_w2101(buint8) -> void;  //OBSEL
auto mmio_w2102(buint8) -> void;  //OAMADDL
auto mmio_w2103(buint8) -> void;  //OAMADDH
auto mmio_w2104(buint8) -> void;  //OAMDATA
auto mmio_w2105(buint8) -> void;  //BGMODE
auto mmio_w2106(buint8) -> void;  //MOSAIC
auto mmio_w2107(buint8) -> void;  //BG1SC
auto mmio_w2108(buint8) -> void;  //BG2SC
auto mmio_w2109(buint8) -> void;  //BG3SC
auto mmio_w210a(buint8) -> void;  //BG4SC
auto mmio_w210b(buint8) -> void;  //BG12NBA
auto mmio_w210c(buint8) -> void;  //BG34NBA
auto mmio_w210d(buint8) -> void;  //BG1HOFS
auto mmio_w210e(buint8) -> void;  //BG1VOFS
auto mmio_w210f(buint8) -> void;  //BG2HOFS
auto mmio_w2110(buint8) -> void;  //BG2VOFS
auto mmio_w2111(buint8) -> void;  //BG3HOFS
auto mmio_w2112(buint8) -> void;  //BG3VOFS
auto mmio_w2113(buint8) -> void;  //BG4HOFS
auto mmio_w2114(buint8) -> void;  //BG4VOFS
auto mmio_w2115(buint8) -> void;  //VMAIN
auto mmio_w2116(buint8) -> void;  //VMADDL
auto mmio_w2117(buint8) -> void;  //VMADDH
auto mmio_w2118(buint8) -> void;  //VMDATAL
auto mmio_w2119(buint8) -> void;  //VMDATAH
auto mmio_w211a(buint8) -> void;  //M7SEL
auto mmio_w211b(buint8) -> void;  //M7A
auto mmio_w211c(buint8) -> void;  //M7B
auto mmio_w211d(buint8) -> void;  //M7C
auto mmio_w211e(buint8) -> void;  //M7D
auto mmio_w211f(buint8) -> void;  //M7X
auto mmio_w2120(buint8) -> void;  //M7Y
auto mmio_w2121(buint8) -> void;  //CGADD
auto mmio_w2122(buint8) -> void;  //CGDATA
auto mmio_w2123(buint8) -> void;  //W12SEL
auto mmio_w2124(buint8) -> void;  //W34SEL
auto mmio_w2125(buint8) -> void;  //WOBJSEL
auto mmio_w2126(buint8) -> void;  //WH0
auto mmio_w2127(buint8) -> void;  //WH1
auto mmio_w2128(buint8) -> void;  //WH2
auto mmio_w2129(buint8) -> void;  //WH3
auto mmio_w212a(buint8) -> void;  //WBGLOG
auto mmio_w212b(buint8) -> void;  //WOBJLOG
auto mmio_w212c(buint8) -> void;  //TM
auto mmio_w212d(buint8) -> void;  //TS
auto mmio_w212e(buint8) -> void;  //TMW
auto mmio_w212f(buint8) -> void;  //TSW
auto mmio_w2130(buint8) -> void;  //CGWSEL
auto mmio_w2131(buint8) -> void;  //CGADDSUB
auto mmio_w2132(buint8) -> void;  //COLDATA
auto mmio_w2133(buint8) -> void;  //SETINI
auto mmio_r2134() -> buint8;  //MPYL
auto mmio_r2135() -> buint8;  //MPYM
auto mmio_r2136() -> buint8;  //MPYH
auto mmio_r2137() -> buint8;  //SLHV
auto mmio_r2138() -> buint8;  //OAMDATAREAD
auto mmio_r2139() -> buint8;  //VMDATALREAD
auto mmio_r213a() -> buint8;  //VMDATAHREAD
auto mmio_r213b() -> buint8;  //CGDATAREAD
auto mmio_r213c() -> buint8;  //OPHCT
auto mmio_r213d() -> buint8;  //OPVCT
auto mmio_r213e() -> buint8;  //STAT77
auto mmio_r213f() -> buint8;  //STAT78

auto mmio_reset() -> void;
