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

typedef struct  {
	u8	vMsgAddr;			//	Voice MESSAGE ADDRESS
	u16	vMsgTime;			//  Voice MESSAGE DELAY TIME
	void *ptrNext;		    //	Pointer to next MESSAGE 	
}	MESSAGE;

typedef	struct  {
	MESSAGE *ptrVoice;
	const u8 *ptrStr0;	    //  Line 0 String MESSAGE
	const u8 *ptrStr1;	    //  Line 1 String MESSAGE
}	PIP_MESSAGE;	

//PIP_MESSAGE	msg_wrong = {0x01,100,"Incorrect ","instructions"}
//PIP_MESSAGE	msg_hariga = {0x0a,100,"Speed deviation","severe"}



#define MSG_WRONG			0x01
#define MSG_HARIGA			0x0a
#define MSG_HAMURA			0x10
#define MSG_MIN_HAMEHIRUT	0x15
#define MSG_M_HAMEHIRUT		0x1b
#define MSG_HAMUTERET		0x22
#define MSG_MEHIRUT			0x27
#define MSG_KAMUT_DELEK		0x2c
#define MSG_TKINA			0x32
#define MSG_KTANA_ME		0x37
#define MSG_LITER			0x3d
#define MSG_1				0x43
#define MSG_2				0x48
#define MSG_3				0x4e
#define MSG_4				0x53
#define MSG_5				0x59
#define MSG_10				0x60
#define MSG_15				0x65
#define MSG_20				0x6d
#define MSG_25				0x72
#define MSG_30				0x7a
#define MSG_TEMPERATURA		0x80
#define MSG_MESUKENET_STOP	0x87
#define MSG_SIM_LEV			0x90
#define MSG_METAH_MAZBER	0x95
#define MSG_TAKIN			0x9c
#define MSG_LO_TAKIN		0xa1
#define MSG_MAZAV_HADLATOT	0xa6
#define MSG_DELET			0xad
#define MSG_SMALE			0xb2
#define MSG_YAMIN			0xb7
#define MSG_KEDMIT			0xbb
#define MSG_AHORIT			0xbf
#define MSG_PTUHA			0xc7



void inIt_MSG(void);
void Envoke(void);

void inIt_MSG(void)
{


}

void Envoke(void)
{	
		
		u8 matix[10][2] = {	MSG_1,
							MSG_PTUH,
							MSG_20,
							MSG_MAZAV_HADLATOT,
							MSG_2,
							MSG_2,
							MSG_DELET,
							MSG_2,
							MSG_2,
							MSG_PTUHA};
		u8 i = 0x00;
		inIt_MSG();
		init_ISD();
		init_lcd();	  
		print_lcd(0,0,"msg: 0x  ");
	    
		while(1)
		{
			print_hex_lcd(0,7,i);
			playback_ISD(matix[i]);
			if(i < 9) i++;
			else i =0;
			


		}

}