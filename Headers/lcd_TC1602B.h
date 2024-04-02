//==========================================================================
//                         "lcd_TC1602B.h"
//==========================================================================

#ifndef lcd_TC1602B
#define lcd_TC1602B

//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"
#include "Delays_H.h"

//--------------------------------------------------------------------------
// Global CONSTANTS
//--------------------------------------------------------------------------

#define 	DISP_2LINE_8BIT		0x38	// 0x38 2 rows,8 bits data, 5x10 pixels
#define 	DISP_ON_CURS_OFF	0x0c	// Display on, Cursor off
#define 	INC_ENTRY			0x06	// Inc. by 1 DDRAM address
#define 	DISP_CLR			0x01	// Clear the Display

#define 	LCD_DATA			P0		// PORT0[0:7] as LCD DB[0:7]
sbit 		LCD_RS	= 	P2^1;      	    // The definition of control pin
sbit 		LCD_E  	= 	P2^0;			// The definition of control pin

//--------------------------------------------------------------------------
// 	Function PROTOTYPES
//--------------------------------------------------------------------------

void	init_lcd(void);							// Install the LCD
void 	com_to_lcd(u8 c);						// Write commands
void 	data_to_lcd(u8 d);						// Write data  
void	print_lcd(u8 row, u8 col, const u8 * );	// Write char array to LCD
//void 	print_hex_lcd(u8 row, u8 col, u8 hex);	// Write Hex to LCD
void 	print_dec_lcd(u8 row, u8 col, u8 hex);	// Write Decimal to LCD

//--------------------------------------------------------------------------
// 	Functions
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// 	init_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : None
//	
//	Prepare the LCD for the next operations ..
//--------------------------------------------------------------------------
void init_lcd(void)
{
	// LCD command array:
	u8 init[4] = {	DISP_2LINE_8BIT,
					DISP_ON_CURS_OFF,
					INC_ENTRY,
					DISP_CLR		};
	int i;
	// Set the LCD command from the array:
	for (i=0;i<4;i++) com_to_lcd(init[i]);
}

//--------------------------------------------------------------------------
// 	com_to_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : unsigned char - command
//			
//	Write command to LCD!
//--------------------------------------------------------------------------
void com_to_lcd(u8 c) 
{
	LCD_DATA	=	c;					// Set Command in The PORT!!!
	LCD_RS 		= 	0;					// Set for Command Input
	LCD_E 		= 	1;					// Set for Command Input
	delay_ms(4);						// Delay 4 mikrosec
	LCD_E 		= 	0;					// Disable LCD for input
	delay_ms(4);						// Delay 4 milisec for execution
}

//--------------------------------------------------------------------------
// 	data_to_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : unsigned char - data
//			
//	Write data [char symbol] to LCD!
//--------------------------------------------------------------------------

void data_to_lcd(u8 d) 
{
	LCD_DATA	=	d;				// Set Data in The PORT!!!
	LCD_RS 		= 	1;				// Set for Data Input
	LCD_E 		= 	1;				// Set for Data Input
	delay_ms(4);					// Delay 4 mikrosec	
	LCD_E 		= 	0;				// Disable LCD for input
	delay_ms(4);					// Delay 4 milisec for execution
}

//--------------------------------------------------------------------------
// 	print_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : 
//		1.	unsigned char - row [0/1]
//		2.	unsigned char - col [0x00(0) - 0x0f(15)]
//		3.	ROM unsigned char array - pointer to the STRING!!!
//--------------------------------------------------------------------------
void print_lcd(u8 row, u8 col, const u8 *ptrStr) 
{	 	
	com_to_lcd(((row)? 0xc0 : 0x80)|(col & 0x0f));	// the address calculated in this way: we calculate like[row --> 0x80 or 0xc0] and then we add (4 low-order bits of col [this to limit it 16 positions in the row])
	while (*ptrStr!='\0') data_to_lcd(*ptrStr++);	// push all the string to lcd [until the line break char]!
}

//--------------------------------------------------------------------------
// 	print_hex_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : 
//		1.	unsigned char - row [0/1]
//		2.	unsigned char - col [0x00(0) - 0x0f(15)]
//		3.	unsigned char - hex VALUE 
// 	
//--------------------------------------------------------------------------
//void print_hex_lcd(u8 row, u8 col, u8 hex)
//{
//	u8 HDig	=	((hex & 0xf0) >> 4)& 0x0f;	
//	u8 LDig	=	((hex & 0x0f) < 0x0a) ? (hex & 0x0f)+ 0x30 : ((hex & 0x0f) - 0x0a) + 0x61 ;
//	HDig = (HDig < 0x0a) ? (HDig & 0x0f)+ 0x30 : ((HDig & 0x0f) - 0x0a )+ 0x61 ;
//	com_to_lcd(((row)? 0xc0 : 0x80)|(col & 0x0f));	// the address calculated in this way: we calculate like[row --> 0x80 or 0xc0] and then we add (4 low-order bits of col [this to limit it 16 positions in the row]) 	
//	data_to_lcd(HDig);
//	data_to_lcd(LDig);
//}

//--------------------------------------------------------------------------
// 	print_dec_lcd
//--------------------------------------------------------------------------
//
// 	Return Value : None
// 	Parameters : 
//		1.	unsigned char - row [0/1]
//		2.	unsigned char - col [0x00(0) - 0x0f(15)]
//		3.	unsigned char - dec VALUE 
// 	
//--------------------------------------------------------------------------
void print_dec_lcd(u8 row, u8 col, u8 dec)
{
	u8 H = 0x20, D = 0x20, U = 0x20;	// 0x20 - ascii space char	
	// set Unit digit:
	U = (dec % 10) + 0x30; 
	if (dec >= 0x0a)  // if number have more that one digit
	{
		// set Decimal digit:
		D = ((dec / 10) % 10) + 0x30;
	 	if (dec >= 0x64) // if number have more that two digits
			// set Hundreds digit:
			H = ((dec / 100) % 10) + 0x30;			
	}
	com_to_lcd(((row)? 0xc0 : 0x80)|(col & 0x0f));	// the address calculated in this way: we calculate like[row --> 0x80 or 0xc0] and then we add (4 low-order bits of col [this to limit it 16 positions in the row]) 		
	data_to_lcd(H); 
	data_to_lcd(D);
	data_to_lcd(U);
}
#endif
//==========================================================================
//                  End Of File "lcd_TC1602B.h"
//==========================================================================
