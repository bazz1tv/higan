//PPUcounter emulates the H/V latch counters of the S-PPU2.
//
//real hardware has the S-CPU maintain its own copy of these counters that are
//updated based on the state of the S-PPU Vblank and Hblank pins. emulating this
//would require full lock-step synchronization for every clock tick.
//to bypass this and allow the two to run out-of-order, both the CPU and PPU
//classes inherit PPUcounter and keep their own counters.
//the timers are kept in sync, as the only differences occur on V=240 and V=261,
//based on interlace. thus, we need only synchronize and fetch interlace at any
//point before this in the frame, which is handled internally by this class at
//V=128.

class PPUcounter {
public:
  alwaysinline void tick();
  alwaysinline void tick(unsigned clocks);

  alwaysinline bool   field   () const;
  alwaysinline buint16 vcounter() const;
  alwaysinline buint16 hcounter() const;
  inline buint16 hdot() const;
  inline buint16 lineclocks() const;

  alwaysinline bool   field   (unsigned offset) const;
  alwaysinline buint16 vcounter(unsigned offset) const;
  alwaysinline buint16 hcounter(unsigned offset) const;

  inline void reset();
  function<void ()> scanline;
  void serialize(serializer&);

private:
  inline void vcounter_tick();

  struct {
    bool interlace;
    bool field;
    buint16 vcounter;
    buint16 hcounter;
  } status;

  struct {
    bool field[2048];
    buint16 vcounter[2048];
    buint16 hcounter[2048];

    int32 index;
  } history;
};
