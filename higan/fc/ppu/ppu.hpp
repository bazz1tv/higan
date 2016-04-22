#include "video.hpp"

struct PPU : Thread {
  static auto Enter() -> void;
  auto main() -> void;
  auto tick() -> void;

  auto scanline() -> void;
  auto frame() -> void;

  auto power() -> void;
  auto reset() -> void;

  auto read(buint16 addr) -> buint8;
  auto write(buint16 addr, buint8 data) -> void;

  auto ciram_read(buint16 addr) -> buint8;
  auto ciram_write(buint16 addr, buint8 data) -> void;

  auto cgram_read(buint16 addr) -> buint8;
  auto cgram_write(buint16 addr, buint8 data) -> void;

  auto raster_enable() const -> bool;
  auto nametable_addr() const -> uint;
  auto scrollx() const -> uint;
  auto scrolly() const -> uint;
  auto sprite_height() const -> uint;

  auto chr_load(buint16 addr) -> buint8;

  auto scrollx_increment() -> void;
  auto scrolly_increment() -> void;

  auto raster_pixel() -> void;
  auto raster_sprite() -> void;
  auto raster_scanline() -> void;

  auto serialize(serializer&) -> void;

  struct Status {
    buint8 mdr;

    bool field;
    uint lx;
    uint ly;

    buint8 bus_data;

    bool address_latch;

    uint15 vaddr;
    uint15 taddr;
    buint8 xaddr;

    bool nmi_hold;
    bool nmi_flag;

    //$2000
    bool nmi_enable;
    bool master_select;
    bool sprite_size;
    uint bg_addr;
    uint sprite_addr;
    uint vram_increment;

    //$2001
    uint3 emphasis;
    bool sprite_enable;
    bool bg_enable;
    bool sprite_edge_enable;
    bool bg_edge_enable;
    bool grayscale;

    //$2002
    bool sprite_zero_hit;
    bool sprite_overflow;

    //$2003
    buint8 oam_addr;
  } status;

  struct Raster {
    buint16 nametable;
    buint16 attribute;
    buint16 tiledatalo;
    buint16 tiledatahi;

    uint oam_iterator;
    uint oam_counter;

    struct OAM {
      buint8 id;
      buint8 y;
      buint8 tile;
      buint8 attr;
      buint8 x;

      buint8 tiledatalo;
      buint8 tiledatahi;
    } oam[8], soam[8];
  } raster;

  buint32 buffer[256 * 262];
  buint8 ciram[2048];
  buint8 cgram[32];
  buint8 oam[256];
};

extern PPU ppu;
