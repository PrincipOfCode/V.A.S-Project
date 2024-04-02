//===========================================================================
//                          "addDecSys.h"
//===========================================================================
#ifndef addDecSys_H
#define addDecSys_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"
#include "Delays_H.h"

//---------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------
#define LATCHES_UPDATE_TIME		50		//	delay time of 50 ns

#define LCD_BY_DEFAULT		0x00	// 	SET Disable all, use LCD on this BUS
#define ISD_LE_SET_0		0x01   	//  SET 0 to Input Enable Pin of 74LS373 [for ISD]
#define ISD_LE_SET_1		0x0d	//  SET 1 to Input Enable Pin of 74LS373 [for ISD]
#define DOORS_OE_SET_0		0x07	//  SET 0 to Output Enable Pin of 74LS373 [for dors]
#define DOORS_OE_SET_1		0x03	//  SET 1 to Output Enable Pin of 74LS373 [for dors]
#define ADC_START_SET_0		0x05
#define ADC_START_SET_1		0x09								 
#define ADC_OE_SET_0		0x06	//	SET 0 to Output Enable Pin of ADC0808
#define ADC_OE_SET_1		0x0a	//	SET 1 to Output Enable Pin of ADC0808


sbit TO_A	=	P2^6;
sbit TO_B	=	P2^7;
sbit RD_T  	= 	P3^7;
sbit WR_T  	= 	P3^6;

//---------------------------------------------------------------------------
// Global STATIC
//---------------------------------------------------------------------------
static u8 bitState = 0x00;
//---------------------------------------------------------------------------
// 	Function PROTOTYPE
//---------------------------------------------------------------------------
void bus_Controle(u8);


//--------------------------------------------------------------------------
// 	Functions
//--------------------------------------------------------------------------
void bus_Controle(u8 s4bits) // {LSB--> 1:WR, 2:RD, 3:TO_B, 4:TO_A <--MSB}
{	
	if((s4bits & 0x0c) == 0x08 ) 
		s4bits ^= (bitState & 0x03);		//	It is a TRIK!
	
 	WR_T	= (s4bits & (1 << 0) )!= 0x00;
	RD_T 	= (s4bits & (1 << 1) )!= 0x00;
	TO_B 	= (s4bits & (1 << 2) )!= 0x00;
	TO_A 	= (s4bits & (1 << 3) )!= 0x00;
				   	

	bitState = s4bits;						// Save The State!
	delay_us(LATCHES_UPDATE_TIME);		    // wait to update
}




#endif
//===========================================================================
//                  End Of File "addDecSys.h"
//===========================================================================
