//===========================================================================
//             				"ADC0808_H.h"
//===========================================================================
#ifndef ADC0808_h
#define ADC0808_h

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "type_var_H.h"
#include "Delays_H.h"
#include "DStructure.h"


//---------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------
#define ADC_CONV_TIME       300		// 	convertion time for ADC0808 - 200usec
#define MAX_TEMP			500		//	set maximum motor temerature - celsius
#define MAX_FULL			30		//	set maximum full Tank - litters
#define MAX_VOLT			12		//	set maximum Accamulator - voltage
#define VREF 				5.0   	//	set voltage reference
#define MAX_RES 			0xff 	//	set maximum resolution of ADC0808 (8bit)

#define INTERVAL_VOLT_1		10		//	Interval 1 min for volt alert
#define INTERVAL_VOLT_5		50		//	Interval 5 min for volt alert
#define INTERVAL_VOLT_10	100		//	Interval 10 min for volt alert
#define INTERVAL_FULL		10		//	Interval 1 min for full alert 
   
xdata u8 AtoD_Temp _at_ 0x4000;		// 	Temperatur sensor xdata
xdata u8 AtoD_Full _at_ 0x4800;		// 	Feul sensor xdata
xdata u8 AtoD_Volt _at_ 0x5000;		// 	Voltage sensor xdata


//--------------------------------------------------------------------------
// 	Functions PROTOTYPES
//--------------------------------------------------------------------------
u8 ADC_conversion(u8);
void scanTemp(bit force);
void scanFull(bit force);
void scanVolt(bit force);

//--------------------------------------------------------------------------
// 	Function
//--------------------------------------------------------------------------

//--------------------------------------------------------------------------
//	ADC_conversion
//--------------------------------------------------------------------------
// 	Return Value : 	unsigned char 
// 	Parameters :  	unsigned char 
//	Analog Sensor Pin Mapping
//	IN0-----> Temperatur sensor
//	IN1-----> Full sensor
//	IN2-----> Voltage sensor
//	IN3-----> Disconnected
//	IN4-----> Disconnected
//	IN5-----> Disconnected
//	IN6-----> Disconnected
//	IN7-----> Disconnected
//---------------------------------------------------------------------------
u8 ADC_conversion(u8 ADC_ch_no)
{
	u8 ADC_result;
	switch(ADC_ch_no)
	{
		case 0x00:   	//	IN0-----> Temperatur sensor
			AtoD_Temp = 0xFF;
			break;
		case 0x01:		//	IN1-----> Full sensor
			 AtoD_Full = 0xFF;
			break;
		case 0x02:		//	IN2-----> Voltage sensor
             AtoD_Volt = 0xFF;		
			break;
		default:
			return 0x00;
			break;
	}	
	delay_us(ADC_CONV_TIME); 		// 	conversion time for ADC0808	
	ADC_result = AtoD_Temp; 		//	storing ADC_result
	P0 	=	0x00;					//  clear the PORT
	return ADC_result; 				//	returning ADC_result
}

//--------------------------------------------------------------------------
//	scanTemp
//--------------------------------------------------------------------------
// 	Return Value : 	none 
// 	Parameters :  bit [0- regular scan, 1- force msg after scan ] 
//--------------------------------------------------------------------------
void scanTemp(bit force)
{
	u16 cast;
	// get value and calculate it:
	cast = (MAX_TEMP*ADC_conversion(0))/MAX_RES;
	// store results:
	settings.temp.tmpr = (u8)cast;

	if(settings.temp.tmpr > 45) //45 C
	{
		appendMsgList(&FMsg7);	
		return;
	}
	else if((settings.temp.alert)||(force))	// is temperature alert set 	
			if(settings.temp.tmpr > 35)	// 35 C
			{
				appendMsgList(&FMsg8);		
				return;
			}
	// if results ok and force set then add this msg:
	if(force) appendMsgList(&FMsg9);
	return;
}

//--------------------------------------------------------------------------
//	scanFull
//--------------------------------------------------------------------------
// 	Return Value : 	none 
// 	Parameters :  	bit [0- regular scan, 1- force msg after scan ]  
//--------------------------------------------------------------------------
void scanFull(bit force)
{
	u16 cast;
	// define msg intervale variable once for all the time:
	static u16 intervalFull = 0;
	// get value and calculate it:
	cast = (MAX_FULL*ADC_conversion(1))/MAX_RES;
	// store results:
	settings.tank.fuel = (u8)cast;

	// check for feul setting:
	switch(settings.tank.a_fule)
	{
		case 6:	 // feul between 30 and 25 litters
			if((settings.tank.fuel < 30)&&(settings.tank.fuel >= 25))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg22);
					setMsgListValue(&FMsg5, 30);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;	
				}
			}
		case 5:	 // feul between 25 and 20 litters
			if((settings.tank.fuel < 25)&&(settings.tank.fuel >= 20))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg21);
					setMsgListValue(&FMsg5, 25);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;	
				}
			}
		case 4:	 // feul between 20 and 15 litters
			if((settings.tank.fuel < 20)&&(settings.tank.fuel >= 15))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg20);
					setMsgListValue(&FMsg5, 20);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;	
				}
			}
		case 3:	 // feul between 15 and 10 litters
			if((settings.tank.fuel < 15)&&(settings.tank.fuel >= 10))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg19);
					setMsgListValue(&FMsg5, 15);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;	
				}
			}
		case 2:	 // feul between 10 and 5 litters
			if((settings.tank.fuel < 10)&&(settings.tank.fuel >= 5))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg18);
					setMsgListValue(&FMsg5, 10);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;	
				}
			}
		case 1:	 // feul between 5 and 0 litters
			// feul between 5 and 4 litters
			if((settings.tank.fuel < 5)&&(settings.tank.fuel >= 4))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg17);
					setMsgListValue(&FMsg5, 5);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;			    
				}
			}
			// feul between 4 and 3 litters
			if((settings.tank.fuel < 4)&&(settings.tank.fuel >= 3))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg16);
					setMsgListValue(&FMsg5, 4);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;			    
				}
			}
			// feul between 3 and 2 litters
			if((settings.tank.fuel < 3)&&(settings.tank.fuel >= 2))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg15);
					setMsgListValue(&FMsg5, 3);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;			    
				}
			}
			// feul between 2 and 1 litters
			if((settings.tank.fuel < 2)&&(settings.tank.fuel >= 1))
			{
				intervalFull++;	// increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg14);
					setMsgListValue(&FMsg5, 2);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;			    
				}
			}
			// feul less then 1 litter:
			if((settings.tank.fuel < 1)&&(settings.tank.fuel >= 0))
			{
				intervalFull++;	 // increment msg interval 
				if((intervalFull>= INTERVAL_FULL)||(force))
				{
					replaceMsgNode(&FMsg5, 2, &VMsg13);
					setMsgListValue(&FMsg5, 1);
					appendMsgList(&FMsg5);
					intervalFull = 0;
					return;			    
				}
			}
			break;
		default:
			break;
	}
	// if no other msg for feul and force set then add this msg: 
	if(force) appendMsgList(&FMsg6);
	return;
}

//--------------------------------------------------------------------------
//	scanVolt
//--------------------------------------------------------------------------
// 	Return Value : 	none 
// 	Parameters :  	bit [0- regular scan, 1- force msg after scan ]  
//--------------------------------------------------------------------------
void scanVolt(bit force)
{
	u16 cast;
	// define msg intervale variable once for all the time:
	static u16 intervalVolt = 0;
	// get value and calculate it:
	cast = (MAX_VOLT*ADC_conversion(2))/MAX_RES;
	// store results:
	settings.acc.voltage = (u8)cast;

	// check voltage results:
	if(settings.acc.voltage != 12)
	{
		intervalVolt++;
		// check accamulator msg alert time:
		switch(settings.acc.a_time)
		{
		 	case 0:	// msg alert is off!
				// if force set add this msg:
				if(force)  appendMsgList(&FMsg10);
				intervalVolt = 0;
				return;				
				break;
			case 1:	
				if((intervalVolt >= INTERVAL_VOLT_1)||(force))
				{
					appendMsgList(&FMsg10);
				    intervalVolt = 0;
					return;
				}				
				break;
			case 2:
				if((intervalVolt >= INTERVAL_VOLT_5)||(force))
				{
					appendMsgList(&FMsg10);
				    intervalVolt = 0;
					return;
				}				
				break;
			case 3:
				if((intervalVolt >= INTERVAL_VOLT_10)||(force))
				{
					appendMsgList(&FMsg10);
				    intervalVolt = 0;
					return;
				}				
			break;
			default:
				intervalVolt = 0;
				break;
		}
	} else 
		// fi no other msg and force set add this msg:
		if(force)  appendMsgList(&FMsg11);
	return;
}
	  
#endif
//===========================================================================
//                  End Of File "ADC0808_h.h"
//===========================================================================






