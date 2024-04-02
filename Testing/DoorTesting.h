//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"
#include "Delays_H.h"
#include "DStructure.h"
#include "Key_Pad_3x4.h"
#include "lcd_TC1602B.h"
#include "ADC0808_H.h"
#include "ISD25120.h"
#include "Doors_H.h"
#include "Speedometer.h"


void Envoke(void);

void Envoke(void)
{	
		init_lcd();	  
		print_lcd(0,0,"lf:0x    rf:0x  ");
		print_lcd(1,0,"lb:0x    rb:0x  ");		

		while(1)
		{
			scanDoors();
			print_hex_lcd(0,5,settings.doors.lfd);
			print_hex_lcd(0,14,settings.doors.rfd);
			print_hex_lcd(1,5,settings.doors.lbd);
			print_hex_lcd(1,14,settings.doors.rbd);
		}

}