//===========================================================================
//             				"Key_Pad_3x4.h"
//===========================================================================
#ifndef Key_Pad_3x4_H
#define Key_Pad_3x4_H

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "type_var_H.h"
#include "Delays_H.h"
#include "DStructure.h"
#include "OUTPUTS.h"

//---------------------------------------------------------------------------
// Function PROTOTYPE:
//---------------------------------------------------------------------------
void scanPad();
void bufferIt();
void clearBuffer();
s8 bufferValue();	 // Returen 8 bit signed (can be negative!) ..
void upDateSettings();

//---------------------------------------------------------------------------
// The Function:
//---------------------------------------------------------------------------
void scanPad()
{
	const u8 key_char[]		= {'1','2','3','4','5','6','7','8','9','*','0','#'};
	const u8 scan_code[]	= {0xfe, 0xfd, 0xfb, 0xf7};
	u8 	key = 0x00;
	int row = 0;
	for (row = 0; row<4; row++)
	{
		P1 = scan_code[row];	//set the scan code in the port. 
		if(!P1_4)				//check if on col0 the key is pressed
		{
			delay_ms(40);			   					//debounce delay
			key = key_char[row*3 + 0]; 					//get key
			while (!P1_4); 								//wait for release
			delay_ms(40);			   					//debounce delay
			settings.keys.key = key;					//Save Key
			bufferIt();									//Buffer the presed key
			return; 									//finish
		}
		
		if (!P1_5) 				//check if on col1 the key is pressed
		{
			delay_ms(40);			   					//debounce delay
			key = key_char[row*3 + 1]; 					//get key
			while (!P1_5); 								//wait for release
			delay_ms(40);			   					//debounce delay
			settings.keys.key = key;					//Save Key
			bufferIt();									//Buffer the presed key
			return; 									//finish 
		}

		if (!P1_6) 				//check if on col2 the key is pressed
		{
			delay_ms(40);			   					//debounce delay
			key = key_char[row*3 + 2];		 			//get key number
			while (!P1_6); 								//wait for release
			delay_ms(40);			   					//debounce delay
			settings.keys.key = key;					//Save Key
			bufferIt();									//Buffer the presed key
			return; 									//finish		
		}
	}

	settings.keys.key = key;
	return;	 					//return no presed key -> 0x00
}

void bufferIt()
{	
	if (settings.keys.bIndex > 2) clearBuffer(); // if buffer full clear it!
	settings.keys.buffer[settings.keys.bIndex] = settings.keys.key;	 // put in the bufer the key value!
	settings.keys.bIndex++; // increment the buffer index .. for next operations ..!	
}

void clearBuffer()
{
	// put end of string char! '\0'  
	settings.keys.buffer[0]	=	'\0';
	settings.keys.buffer[1]	=	'\0';
	settings.keys.buffer[2]	=	'\0';
	settings.keys.buffer[3]	=	'\0';
	// set buffer index to zero!
	settings.keys.bIndex 	= 	0;
}


s8 bufferValue()
{
	s8 val = 0, i = 1; // set val to zero! and index to 1 (after posibbel * from the keypad) it is location of the first possible number input!
	while(settings.keys.buffer[i] != '\0') // do this loop until end of string char (on the buffer array)
	{
		val = (val * 10) + settings.keys.buffer[i]-48;	// calculation: Value = (Value*10) 	to present mor hier rang digit! and + (ascii char from buffer - 48), 48 is it ascii 0 char .. this is to calculate the offset from asci to decimal! (encoding!)
		i++;  // increment the inner index for this loop!
	}
	if(i>1) return val;	 // if loop abowe done one or more times then i>1 then return the calculation value! else return -1 as control value!
	return -1;	 // Empty
}


void upDateSettings()
{
	s8 val;
	if(settings.keys.buffer[0] == '*') // if '*' key was preset first
	{
		val = bufferValue();  // get the nummeric value of the buffer
		switch(val)
		{
			case (-1):	//	Empty
				break;
			case 0:		//  Force system output!
				// reset system ouput interval
				settings.fInterval = FORCE_MESSAGE_INTERVAL;
				clearBuffer();				
				break;
			case 1:	  	//	reserved!
				break;
			case 11:	//  Set speed to 50 Kph
				settings.speed.a_speed 	= 	1;
				clearBuffer();
				break;
			case 12:	//  Set speed to 60 Kph
				settings.speed.a_speed 	= 	2;
				clearBuffer();
				break;
			case 13:	//  Set speed to 70 Kph
				settings.speed.a_speed 	= 	3;
				clearBuffer();
				break;
			case 14:	//  Set speed to 80 Kph
				settings.speed.a_speed 	= 	4;
				clearBuffer();
				break;
			case 15:	//  Set speed to 90 Kph
				settings.speed.a_speed 	= 	5;
				clearBuffer();
				break;
			case 16:	//  Set speed to 100 Kph
				settings.speed.a_speed 	= 	6;
				clearBuffer();
				break;
			case 2:	  	//	reserved!
				break;
			case 21:	//  Set full alert to 5 Litter
				settings.tank.a_fule 	= 	1;
				clearBuffer();
				break;
			case 22:	//  Set full alert to 10 Litter
				settings.tank.a_fule 	= 	2;
				clearBuffer();
				break;
			case 23:	//  Set full alert to 15 Litter
				settings.tank.a_fule 	= 	3;
				clearBuffer();
				break;
			case 24:	//  Set full alert to 20 Litter
				settings.tank.a_fule 	= 	4;
				clearBuffer();
				break;
			case 25:	//  Set full alert to 25 Litter
				settings.tank.a_fule 	= 	5;
				clearBuffer();
				break;
			case 26:	//  Set full alert to 30 Litter
				settings.tank.a_fule 	= 	6;
				clearBuffer();
				break;
			case 3:	  	//	Turn on/off temperatur alert
				settings.temp.alert = !settings.temp.alert ;
				clearBuffer();
				break;
			case 4:	  	//	reserved!
				break;
			case 40:	//	Turn off voltage alert
				settings.acc.a_time = 0;
				clearBuffer();
				break;
			case 41:	//	Set voltage alert any 1 min
				settings.acc.a_time = 1;
				clearBuffer();
				break;
			case 42:	//	Set voltage alert any 5 min
				settings.acc.a_time = 2;
				clearBuffer();
				break;
			case 43:	//	Set voltage alert any 10 min
				settings.acc.a_time = 3;
				clearBuffer();
				break;
			case 5:	  	//	Turn on/off doors alert
				if(settings.doors.alert) // if alert set
				{
					// save present doors stage:
					settings.doors.ls = settings.doors.ps;
				}
				// change door alert [0 -> 1, 1 -> 0]:
				settings.doors.alert = !settings.doors.alert;
				clearBuffer();
				break;
			default:	//  Wrong input!
				clearBuffer();
				// add msg to the system msg list:
				appendMsgList(&FMsg1); 
				break;
		}
	}
}

#endif
//===========================================================================
//                  End Of File "Key_Pad_3x4.h"
//===========================================================================
