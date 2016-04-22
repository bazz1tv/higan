struct Decomp {
  struct IM {  //input manager
    IM(SDD1::Decomp& self) : self(self) {}
    auto init(uint offset) -> void;
    auto get_codeword(buint8 code_length) -> buint8;

  private:
    Decomp& self;
    uint offset;
    uint bit_count;
  };

  struct GCD {  //golomb-code decoder
    GCD(SDD1::Decomp& self) : self(self) {}
    auto get_run_count(buint8 code_number, buint8& mps_count, bool& lps_index) -> void;

  private:
    Decomp& self;
    static const buint8 run_count[256];
  };

  struct BG {  //bits generator
    BG(SDD1::Decomp& self, buint8 code_number) : self(self), code_number(code_number) {}
    auto init() -> void;
    auto get_bit(bool& end_of_run) -> buint8;

  private:
    Decomp& self;
    const buint8 code_number;
    buint8 mps_count;
    bool lps_index;
  };

  struct PEM {  //probability estimation module
    PEM(SDD1::Decomp& self) : self(self) {}
    auto init() -> void;
    auto get_bit(buint8 context) -> buint8;

  private:
    Decomp& self;
    struct State {
      buint8 code_number;
      buint8 next_if_mps;
      buint8 next_if_lps;
    };
    static const State evolution_table[33];
    struct ContextInfo {
      buint8 status;
      buint8 mps;
    } context_info[32];
  };

  struct CM {  //context model
    CM(SDD1::Decomp& self) : self(self) {}
    auto init(uint offset) -> void;
    buint8 get_bit();

  private:
    Decomp& self;
    buint8 bitplanes_info;
    buint8 context_bits_info;
    buint8 bit_number;
    buint8 current_bitplane;
    buint16 previous_bitplane_bits[8];
  };

  struct OL {  //output logic
    OL(SDD1::Decomp& self) : self(self) {}
    auto init(uint offset) -> void;
    auto decompress() -> buint8;

  private:
    Decomp& self;
    buint8 bitplanes_info;
    buint8 r0, r1, r2;
  };

  Decomp();
  auto init(uint offset) -> void;
  auto read() -> buint8;

  IM  im;
  GCD gcd;
  BG  bg0, bg1, bg2, bg3, bg4, bg5, bg6, bg7;
  PEM pem;
  CM  cm;
  OL  ol;
};
