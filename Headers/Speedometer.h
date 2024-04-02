//===========================================================================
//             				"Speedometer.h"
//===========================================================================
#ifndef Speedometer_h
#define Speedometer_h

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"
#include "Delays_H.h"

// 24000 Samples * 2 Alfa => maximum speed +-120 for (9v * 300mA):
#define SAMPLES				24000  
#define ALFA				2	   


#define EXCEPRION 			5
#define FATAL_EXCEPTION		10

//---------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------
sbit SM_PULS = P3^4;   // Speedometer	 (Input)
bit state = 1;
bit pr_state = 0;

//---------------------------------------------------------------------------
// Function PROTOTYPE:
//---------------------------------------------------------------------------
void getSpeed(bit);

//---------------------------------------------------------------------------
// The Function:
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
// getSpeed
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters	: bit [0- regular scan, 1- force msg after scan ] 
// Discription	: this function calculate the speed value 
//                by counter the pulses in defined sampling time.
//
//-------------------------------------------------------------------------
void getSpeed(bit force)
{	
	u8  counter = 0x00; 
	u16 i;

	for(i=0;i<SAMPLES;i++){
		state	= SM_PULS;	
		if(state != pr_state) 
		{
		   pr_state	= state;
		   if(state) counter++;

		}
	}
	// calcuate the results and save it:
	settings.speed.speed = counter * ALFA;
	
	// check for speed settings:		
	switch(settings.speed.a_speed)
	{
		case 1:
			if((settings.speed.speed >= 50 + EXCEPRION)&&(settings.speed.speed < 50 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 50 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		case 2:
			if((settings.speed.speed >= 60 + EXCEPRION)&&(settings.speed.speed < 60 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 60 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		case 3:
			if((settings.speed.speed >= 70 + EXCEPRION)&&(settings.speed.speed < 70 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 70 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		case 4:
			if((settings.speed.speed >= 80 + EXCEPRION)&&(settings.speed.speed < 80 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 80 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		case 5:
			if((settings.speed.speed >= 90 + EXCEPRION)&&(settings.speed.speed < 90 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 90 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		case 6:
			if((settings.speed.speed >= 100 + EXCEPRION)&&(settings.speed.speed < 100 + FATAL_EXCEPTION))
			{				
				appendMsgList(&FMsg3);	
				return;
			} else if (settings.speed.speed >= 100 + FATAL_EXCEPTION)
			{
				appendMsgList(&FMsg2);	
				return;
			}
			break;
		default:
			break;

	}
	// if no other msgs and force set then add this msg:
	if(force) appendMsgList(&FMsg4);
	return;
}


#endif
//===========================================================================
//                  End Of File "Speedometer.h"        
//===========================================================================