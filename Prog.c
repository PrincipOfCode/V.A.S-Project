//===========================================================================
//                          "Prog.c"
//===========================================================================

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"	   // MicroControler Header
#include "type_var_H.h"	   // Types Definition Header
#include "Delays_H.h"	   // Delay Functions Header
#include "DStructure.h"	   // Data Structs Header
#include "OUTPUTS.h"	   // Complex OutPuts Header
#include "Key_Pad_3x4.h"   // Kay Pad Functions Header
#include "lcd_TC1602B.h"   // LCD Functions Header
#include "ADC0808_H.h"	   // ADC0808 Functions Header
#include "ISD25120.h"	   // ISD25120 Functions Header
#include "Doors_H.h"	   // Doors Functions Header
#include "Speedometer.h"   // Speedometer Functions Header


////---------------------------------------------------------------------------
//// MAIN Routine
////---------------------------------------------------------------------------


void main( void )
{
	
	init_ISD();		
	delay_ms(1000);
	init_lcd();	  
	print_lcd(0,0,"  Welcome to    ");
	print_lcd(1,0," V.A.S Project  ");
	delay_ms(2300);
	print_lcd(0,0,"   Made By:     ");
	print_lcd(1,0," Dvir and Eli   ");
	
	while(1)
	{	
		settings.keys.key = 0x00;
		while (settings.keys.key != '#') {scanPad();}	//	turn on
		
		inIt_Settings();	// reset System Settings	
		inItOutPuts();		// reset System OutPuts	
								
		scanVolt(1);		// force msg voice after Voltage scan		
		scanTemp(1);		// force msg voice after Temperatur scan		
		scanFull(1);		// force msg voice after Feul scan		
 		scanDoors(1);		// force msg voice after Doors scan						
		while(settings.keys.key != '#')					//  turn off
		{	
			
			if(msgExist())	// check if there is msg to play
			{
				playMsg();	// execute msg
				settings.fInterval = 0;	 // reset msg interval
			}
			else
			{				     
				if(settings.fInterval == 0) // print once until next msg 
				{
					// print the system stats template
					print_lcd(0,0,"[T:   C][V:   V]");
					print_lcd(1,0,"[F:   L][S:   K]");					
				} 				
				// print the values of : Temperatur, Voltage
				//                       Feul, Speed
				print_dec_lcd(0,3,settings.temp.tmpr);
				print_dec_lcd(0,11,settings.acc.voltage);
				print_dec_lcd(1,3,settings.tank.fuel);					
				print_dec_lcd(1,11,settings.speed.speed);					
				settings.fInterval++;  // increment interval
			}

			scanPad();				   // check for input
			upDateSettings();		   // update system settings

			// is it time for system state msg?
			if(settings.fInterval == FORCE_MESSAGE_INTERVAL) 
			{
				// scan and force msg
				getSpeed(1);			
				scanVolt(1);				
				scanTemp(1);
				scanFull(1);
		 		scanDoors(1);			
			} 
			else  // no
			{		
				// regular scan
				getSpeed(0);			
				scanVolt(0);				
				scanTemp(0);
				scanFull(0);
		 		scanDoors(0);
			}
		}
		
		// clear the screen [dump solution!]:
		print_lcd(0,0,"                ");
		print_lcd(1,0,"                ");
	}



}


//===========================================================================
//                  End Of File "Prog.c"
//===========================================================================
