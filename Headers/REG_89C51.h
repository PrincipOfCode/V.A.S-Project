//===========================================================================
//                         "REG89C51.h"
//===========================================================================

#ifndef __REG_89C51_H__
#define __REG_89C51_H__

/*  PORT 0  */
sfr  P0   = 0x80;
sbit P0_7 = P0^7;
sbit P0_6 = P0^6;
sbit P0_5 = P0^5;
sbit P0_4 = P0^4;
sbit P0_3 = P0^3;
sbit P0_2 = P0^2;
sbit P0_1 = P0^1;
sbit P0_0 = P0^0;

/*  PORT 1  */
sfr  P1   = 0x90;
sbit P1_7 = P1^7;
sbit P1_6 = P1^6;
sbit P1_5 = P1^5;
sbit P1_4 = P1^4;
sbit P1_3 = P1^3;
sbit P1_2 = P1^2;
sbit P1_1 = P1^1;
sbit P1_0 = P1^0;

/*  PORT 2  */
sfr  P2   = 0xA0;
sbit P2_7 = P2^7;
sbit P2_6 = P2^6;
sbit P2_5 = P2^5;
sbit P2_4 = P2^4;
sbit P2_3 = P2^3;
sbit P2_2 = P2^2;
sbit P2_1 = P2^1;
sbit P2_0 = P2^0;

/*  PORT 3  */
sfr  P3   = 0xB0;
sbit P3_7 = P3^7;
sbit P3_6 = P3^6;
sbit P3_5 = P3^5;
sbit P3_4 = P3^4;
sbit P3_3 = P3^3;
sbit P3_2 = P3^2;
sbit P3_1 = P3^1;
sbit P3_0 = P3^0;

sbit RD   = P3^7;
sbit WR   = P3^6;
sbit T1   = P3^5;
sbit T0   = P3^4;
sbit INT1 = P3^3;
sbit INT0 = P3^2;
sbit TXD  = P3^1;
sbit RXD  = P3^0;

#endif
//===========================================================================
//                  End Of File "REG89C51.h"
//===========================================================================