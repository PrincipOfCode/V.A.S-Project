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
#include "OUTPUTS.h"

void Envoke(void);

void Envoke(void)
{	
		init_ISD();
		inIt_Settings(); 
		init_lcd();	 
		
		print_lcd(0,0,"OutPuts Testing:");
		delay_ms(300);
		inItOutPuts();
		
	    
		while(1)
		{
			playMsg();
		}

}