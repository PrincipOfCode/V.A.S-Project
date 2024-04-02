//	for P89V51RD2  
#ifndef __general_h__
#define __general_h__

typedef unsigned char  byte;
typedef unsigned int   uint;

#define ACK 0
#define NACK 1
#define TRUE 0
#define FALSE 0

void delay_us(uint us);
void delay_ms(uint ms);
void nop(void);


void nop(void){ } // delay 5usec


void delay_ms(uint ms)
{
	uint n;
	uint i;

	for (n=0; n<ms; n++)
	{
		for (i=0; i<100; i++); 
	} 
}

void delay_us(uint us)		  //	usec(10)=200usec ;  usec(1)=20usec ;
{ 
  while(us--) nop();
}
#endif