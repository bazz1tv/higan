struct Cache {
  Cache(PPU& self);

  auto tile_2bpp(uint tile) -> buint8*;
  auto tile_4bpp(uint tile) -> buint8*;
  auto tile_8bpp(uint tile) -> buint8*;
  auto tile(uint bpp, uint tile) -> buint8*;

  auto serialize(serializer&) -> void;

  PPU& self;
  buint8* tiledata[3];
  buint8* tilevalid[3];

  friend class PPU;
};
