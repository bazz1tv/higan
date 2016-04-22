buint8 r6003;      //control port
buint8 r6004;      //joypad 1
buint8 r6005;      //joypad 2
buint8 r6006;      //joypad 3
buint8 r6007;      //joypad 4
buint8 r7000[16];  //JOYP packet data
buint8 mlt_req;    //number of active joypads

buint8 output[4 * 512];
uint read_bank;
uint read_addr;
uint write_bank;
uint write_addr;
