//render.cpp
inline auto render_line_mode0() -> void;
inline auto render_line_mode1() -> void;
inline auto render_line_mode2() -> void;
inline auto render_line_mode3() -> void;
inline auto render_line_mode4() -> void;
inline auto render_line_mode5() -> void;
inline auto render_line_mode6() -> void;
inline auto render_line_mode7() -> void;

//cache.cpp
enum : uint { COLORDEPTH_4 = 0, COLORDEPTH_16 = 1, COLORDEPTH_256 = 2 };
enum : uint { TILE_2BIT = 0, TILE_4BIT = 1, TILE_8BIT = 2 };

struct pixel_t {
  //bgr555 color data for main/subscreen pixels: 0x0000 = transparent / use palette color # 0
  //needs to be bgr555 instead of palette index for direct color mode ($2130 bit 0) to work
  buint16 src_main, src_sub;
  //indicates source of palette # for main/subscreen (BG1-4, OAM, or back)
  buint8  bg_main,  bg_sub;
  //color_exemption -- true when bg == OAM && palette index >= 192, disables color add/sub effects
  buint8  ce_main,  ce_sub;
  //priority level of src_n. to set src_n,
  //the priority of the pixel must be >pri_n
  buint8  pri_main, pri_sub;
} pixel_cache[256];

buint8* bg_tiledata[3];
buint8* bg_tiledata_state[3];  //0 = valid, 1 = dirty

template<uint color_depth> auto render_bg_tile(buint16 tile_num) -> void;
inline auto flush_pixel_cache() -> void;
auto alloc_tiledata_cache() -> void;
auto flush_tiledata_cache() -> void;
auto free_tiledata_cache() -> void;

//windows.cpp
struct window_t {
  buint8 main[256], sub[256];
} window[6];

auto build_window_table(buint8 bg, bool mainscreen) -> void;
auto build_window_tables(buint8 bg) -> void;

//bg.cpp
struct {
  buint16 tw,  th;  //tile width, height
  buint16 mx,  my;  //screen mask x, y
  buint16 scx, scy; //sc index offsets
} bg_info[4];
auto update_bg_info() -> void;

template<uint bg> auto bg_get_tile(buint16 x, buint16 y) -> buint16;
template<uint mode, uint bg, uint color_depth> auto render_line_bg(buint8 pri0_pos, buint8 pri1_pos) -> void;

//oam.cpp
struct sprite_item {
  buint8  width, height;
  buint16 x, y;
  buint8  character;
  bool   use_nameselect;
  bool   vflip, hflip;
  buint8  palette;
  buint8  priority;
  bool   size;
} sprite_list[128];
bool sprite_list_valid;
uint active_sprite;

buint8 oam_itemlist[32];
struct oam_tileitem {
  buint16 x, y, pri, pal, tile;
  bool   hflip;
} oam_tilelist[34];

enum : uint { OAM_PRI_NONE = 4 };
buint8 oam_line_pal[256], oam_line_pri[256];

auto update_sprite_list(unsigned addr, buint8 data) -> void;
auto build_sprite_list() -> void;
auto is_sprite_on_scanline() -> bool;
auto load_oam_tiles() -> void;
auto render_oam_tile(int tile_num) -> void;
auto render_line_oam_rto() -> void;
auto render_line_oam(buint8 pri0_pos, buint8 pri1_pos, buint8 pri2_pos, buint8 pri3_pos) -> void;

//mode7.cpp
template<uint bg> auto render_line_mode7(buint8 pri0_pos, buint8 pri1_pos) -> void;

//addsub.cpp
inline auto addsub(buint32 x, buint32 y, bool halve) -> buint16;

//line.cpp
inline auto get_palette(buint8 index) -> buint16;
inline auto get_direct_color(buint8 p, buint8 t) -> buint16;
inline auto get_pixel_normal(buint32 x) -> buint16;
inline auto get_pixel_swap(buint32 x) -> buint16;
auto render_line_output() -> void;
auto render_line_clear() -> void;
