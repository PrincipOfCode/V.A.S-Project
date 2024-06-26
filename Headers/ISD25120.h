//==========================================================================
//                         "ISD25120.h"
//==========================================================================
#ifndef ISD25120_H		
#define ISD25120_H 

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"

//---------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------
#define CE_PULS_TIME	100 
#define PD_HI_TIME	    1000
#define ADD_LATCH_TIME	50
#define EOM_TIME		50 //25


xdata u8 ISD _at_ 0xc000 ;
sbit ISD_PD	=	P3^2; 
sbit ISD_CE	=	P3^3;
sbit EOM	=   P3^5; 

//--------------------------------------------------------------------------
// 	Functions PROTOTYPES
//--------------------------------------------------------------------------
void init_ISD();
void playback_ISD(u8 add); 

//--------------------------------------------------------------------------
// 	Functions
//-------------------------------------------------------------------------- 

//--------------------------------------------------------------------------
// init_ISD
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters	: None
// Discription	: SetUp the ISD for use! 
//
//-------------------------------------------------------------------------
void init_ISD() 
{
	ISD_PD = 1;
	delay_ms(PD_HI_TIME);

	ISD_PD = 0;
	delay_ms(PD_HI_TIME);

	ISD_CE = 1;

}

//--------------------------------------------------------------------------
// playback_ISD
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters	: unsigned byte (8 bits) - msg address
// Discription	: This function set the msg address
//                to the ISD, set it on playback mode (Latch it)
//                and waits until the end of msg (EOM). 
//
//-------------------------------------------------------------------------
void playback_ISD(u8 add)   
{   	
	ISD_PD = 0;
   	ISD = add;
	delay_us(ADD_LATCH_TIME);
	add = ISD;
    ISD_CE = 0;       
	delay_us(CE_PULS_TIME);		
	ISD_CE = 1; // Latch the ISD - start playback
	while(EOM); // wait for end of msg!
	delay_ms(EOM_TIME);
} 

#endif 
//===========================================================================
//                  End Of File "ISD25120.h"
//===========================================================================