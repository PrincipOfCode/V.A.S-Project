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
		u8 i, conv[3] = {0x00,0x00,0x00};
		init_lcd();	  
		print_lcd(0,0,"T:   F:   V:  ");
		//print_lcd(1,0,"c2:   ");		

		while(1)
		{
			scanTemp();
			scanTemp();
			scanFull();
			//for(i=0;i<3;i++) conv[i] = ADC_conversion(i);

			print_dec_lcd(0,1,settings.temp.tmpr);
			print_dec_lcd(0,6,settings.tank.fuel);
			print_dec_lcd(0,11,settings.acc.voltage);
			


		}

}