//===========================================================================
//             				"Doors_H.h"
//===========================================================================
#ifndef Doors_H
#define Doors_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "type_var_H.h"
#include "Delays_H.h"
#include "DStructure.h"
#include "OUTPUTS.h"


xdata unsigned char DOORS _at_ 0x8000 ;

//---------------------------------------------------------------------------
// Function PROTOTYPE:
//---------------------------------------------------------------------------
void scanDoors(bit force);
//---------------------------------------------------------------------------
// The Function:
//---------------------------------------------------------------------------

//--------------------------------------------------------------------------
// scanDoors
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters	: bit [0- regular scan, 1- force msg after scan ] 
// Discription	: delay during several miliseconds
//
//-------------------------------------------------------------------------
void scanDoors(bit force)
{
	// get Doors status byte and clear it by 
	// the mask, we need only first 4 bits,
	// and save it in the present doors state:
	settings.doors.ps 	=	DOORS & 0x0f;
	// get and save the left front door 
	// value from present doors state:
	settings.doors.lfd 	=	(u8)((settings.doors.ps & (1 << 0))>>0);
	// get and save the right front door 
	// value from present doors state:
	settings.doors.rfd	=	(u8)((settings.doors.ps & (1 << 1))>>1);
	// get and save the left back door 
	// value from present doors state:
	settings.doors.lbd	=	(u8)((settings.doors.ps & (1 << 2))>>2);
	// get and save the right back door 
	// value from present doors state:
	settings.doors.rbd	=	(u8)((settings.doors.ps & (1 << 3))>>3);
	
	if(settings.doors.ps != 0x00) // did all the doors close?
	{
		if(!settings.doors.alert) // doors alert off	
		{
			// last doors state not equal to present doors state:
			if(settings.doors.ls != settings.doors.ps)	
			{
				// turn doors alert on:
				settings.doors.alert	=	1; 
				// if left front door open add msg:
				if(settings.doors.lfd) appendMsgList(&FMsg12);				
				// if right front door open add msg:
				if(settings.doors.rfd) appendMsgList(&FMsg13);
				// if left back door open add msg:
				if(settings.doors.lbd) appendMsgList(&FMsg14);
				// if right back door open add msg:
				if(settings.doors.rbd) appendMsgList(&FMsg15);
				return;
			}
		}
		else // doors alert on	
		{
				// if left front door open add msg:
				if(settings.doors.lfd) appendMsgList(&FMsg12);				
				// if right front door open add msg:
				if(settings.doors.rfd) appendMsgList(&FMsg13);
				// if left back door open add msg:
				if(settings.doors.lbd) appendMsgList(&FMsg14);
				// if right back door open add msg:
				if(settings.doors.rbd) appendMsgList(&FMsg15);
				return;
		}
	}
	// no other msgs and force set add this msg:
	if(force) appendMsgList(&FMsg16);
	return;		
}

#endif
//===========================================================================
//                  End Of File "Doors_H.h"
//===========================================================================
