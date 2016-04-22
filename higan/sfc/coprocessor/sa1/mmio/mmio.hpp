auto mmio_read(uint24 addr, buint8 data) -> buint8;
auto mmio_write(uint24 addr, buint8 data) -> void;

struct MMIO {
  //$2200 CCNT
  bool sa1_irq;
  bool sa1_rdyb;
  bool sa1_resb;
  bool sa1_nmi;
  buint8 smeg;

  //$2201 SIE
  bool cpu_irqen;
  bool chdma_irqen;

  //$2202 SIC
  bool cpu_irqcl;
  bool chdma_irqcl;

  //$2203,$2204 CRV
  buint16 crv;

  //$2205,$2206 CNV
  buint16 cnv;

  //$2207,$2208 CIV
  buint16 civ;

  //$2209 SCNT
  bool cpu_irq;
  bool cpu_ivsw;
  bool cpu_nvsw;
  buint8 cmeg;

  //$220a CIE
  bool sa1_irqen;
  bool timer_irqen;
  bool dma_irqen;
  bool sa1_nmien;

  //$220b CIC
  bool sa1_irqcl;
  bool timer_irqcl;
  bool dma_irqcl;
  bool sa1_nmicl;

  //$220c,$220d SNV
  buint16 snv;

  //$220e,$220f SIV
  buint16 siv;

  //$2210 TMC
  bool hvselb;
  bool ven;
  bool hen;

  //$2212,$2213
  buint16 hcnt;

  //$2214,$2215
  buint16 vcnt;

  //$2220 CXB
  bool cbmode;
  uint cb;

  //$2221 DXB
  bool dbmode;
  uint db;

  //$2222 EXB
  bool ebmode;
  uint eb;

  //$2223 FXB
  bool fbmode;
  uint fb;

  //$2224 BMAPS
  buint8 sbm;

  //$2225 BMAP
  bool sw46;
  buint8 cbm;

  //$2226 SBWE
  bool swen;

  //$2227 CBWE
  bool cwen;

  //$2228 BWPA
  buint8 bwp;

  //$2229 SIWP
  buint8 siwp;

  //$222a CIWP
  buint8 ciwp;

  //$2230 DCNT
  bool dmaen;
  bool dprio;
  bool cden;
  bool cdsel;
  bool dd;
  buint8 sd;

  //$2231 CDMA
  bool chdend;
  buint8 dmasize;
  buint8 dmacb;

  //$2232-$2234 SDA
  buint32 dsa;

  //$2235-$2237 DDA
  buint32 dda;

  //$2238,$2239 DTC
  buint16 dtc;

  //$223f BBF
  bool bbf;

  //$2240-224f BRF
  buint8 brf[16];

  //$2250 MCNT
  bool acm;
  bool md;

  //$2251,$2252 MA
  buint16 ma;

  //$2253,$2254 MB
  buint16 mb;

  //$2258 VBD
  bool hl;
  buint8 vb;

  //$2259-$225b VDA
  buint32 va;
  buint8 vbit;

  //$2300 SFR
  bool cpu_irqfl;
  bool chdma_irqfl;

  //$2301 CFR
  bool sa1_irqfl;
  bool timer_irqfl;
  bool dma_irqfl;
  bool sa1_nmifl;

  //$2302,$2303 HCR
  buint16 hcr;

  //$2304,$2305 VCR
  buint16 vcr;

  //$2306-230a MR
  buint64 mr;

  //$230b OF
  bool overflow;
} mmio;

auto mmio_w2200(buint8) -> void;  //CCNT
auto mmio_w2201(buint8) -> void;  //SIE
auto mmio_w2202(buint8) -> void;  //SIC
auto mmio_w2203(buint8) -> void;  //CRVL
auto mmio_w2204(buint8) -> void;  //CRVH
auto mmio_w2205(buint8) -> void;  //CNVL
auto mmio_w2206(buint8) -> void;  //CNVH
auto mmio_w2207(buint8) -> void;  //CIVL
auto mmio_w2208(buint8) -> void;  //CIVH
auto mmio_w2209(buint8) -> void;  //SCNT
auto mmio_w220a(buint8) -> void;  //CIE
auto mmio_w220b(buint8) -> void;  //CIC
auto mmio_w220c(buint8) -> void;  //SNVL
auto mmio_w220d(buint8) -> void;  //SNVH
auto mmio_w220e(buint8) -> void;  //SIVL
auto mmio_w220f(buint8) -> void;  //SIVH
auto mmio_w2210(buint8) -> void;  //TMC
auto mmio_w2211(buint8) -> void;  //CTR
auto mmio_w2212(buint8) -> void;  //HCNTL
auto mmio_w2213(buint8) -> void;  //HCNTH
auto mmio_w2214(buint8) -> void;  //VCNTL
auto mmio_w2215(buint8) -> void;  //VCNTH
auto mmio_w2220(buint8) -> void;  //CXB
auto mmio_w2221(buint8) -> void;  //DXB
auto mmio_w2222(buint8) -> void;  //EXB
auto mmio_w2223(buint8) -> void;  //FXB
auto mmio_w2224(buint8) -> void;  //BMAPS
auto mmio_w2225(buint8) -> void;  //BMAP
auto mmio_w2226(buint8) -> void;  //SBWE
auto mmio_w2227(buint8) -> void;  //CBWE
auto mmio_w2228(buint8) -> void;  //BWPA
auto mmio_w2229(buint8) -> void;  //SIWP
auto mmio_w222a(buint8) -> void;  //CIWP
auto mmio_w2230(buint8) -> void;  //DCNT
auto mmio_w2231(buint8) -> void;  //CDMA
auto mmio_w2232(buint8) -> void;  //SDAL
auto mmio_w2233(buint8) -> void;  //SDAH
auto mmio_w2234(buint8) -> void;  //SDAB
auto mmio_w2235(buint8) -> void;  //DDAL
auto mmio_w2236(buint8) -> void;  //DDAH
auto mmio_w2237(buint8) -> void;  //DDAB
auto mmio_w2238(buint8) -> void;  //DTCL
auto mmio_w2239(buint8) -> void;  //DTCH
auto mmio_w223f(buint8) -> void;  //BBF
auto mmio_w2240(buint8) -> void;  //BRF0
auto mmio_w2241(buint8) -> void;  //BRF1
auto mmio_w2242(buint8) -> void;  //BRF2
auto mmio_w2243(buint8) -> void;  //BRF3
auto mmio_w2244(buint8) -> void;  //BRF4
auto mmio_w2245(buint8) -> void;  //BRF5
auto mmio_w2246(buint8) -> void;  //BRF6
auto mmio_w2247(buint8) -> void;  //BRF7
auto mmio_w2248(buint8) -> void;  //BRF8
auto mmio_w2249(buint8) -> void;  //BRF9
auto mmio_w224a(buint8) -> void;  //BRFA
auto mmio_w224b(buint8) -> void;  //BRFB
auto mmio_w224c(buint8) -> void;  //BRFC
auto mmio_w224d(buint8) -> void;  //BRFD
auto mmio_w224e(buint8) -> void;  //BRFE
auto mmio_w224f(buint8) -> void;  //BRFF
auto mmio_w2250(buint8) -> void;  //MCNT
auto mmio_w2251(buint8) -> void;  //MAL
auto mmio_w2252(buint8) -> void;  //MAH
auto mmio_w2253(buint8) -> void;  //MBL
auto mmio_w2254(buint8) -> void;  //MBH
auto mmio_w2258(buint8) -> void;  //VBD
auto mmio_w2259(buint8) -> void;  //VDAL
auto mmio_w225a(buint8) -> void;  //VDAH
auto mmio_w225b(buint8) -> void;  //VDAB

auto mmio_r2300() -> buint8;  //SFR
auto mmio_r2301() -> buint8;  //CFR
auto mmio_r2302() -> buint8;  //HCRL
auto mmio_r2303() -> buint8;  //HCRH
auto mmio_r2304() -> buint8;  //VCRL
auto mmio_r2305() -> buint8;  //VCRH
auto mmio_r2306() -> buint8;  //MR [00-07]
auto mmio_r2307() -> buint8;  //MR [08-15]
auto mmio_r2308() -> buint8;  //MR [16-23]
auto mmio_r2309() -> buint8;  //MR [24-31]
auto mmio_r230a() -> buint8;  //MR [32-40]
auto mmio_r230b() -> buint8;  //OF
auto mmio_r230c() -> buint8;  //VDPL
auto mmio_r230d() -> buint8;  //VDPH
auto mmio_r230e() -> buint8;  //VC
