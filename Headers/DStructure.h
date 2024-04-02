//===========================================================================
//                          "DStructure.h"        
//===========================================================================
#ifndef DStructure_H
#define DStructure_H

//--------------------------------------------------------------------------
// Includes
//--------------------------------------------------------------------------
#include "type_var_H.h"

//--------------------------------------------------------------------------
// Structs
//--------------------------------------------------------------------------

typedef struct  {
	u8	vMsgAddr;			//	Voice MESSAGE ADDRESS
	void *ptrNext;		    //	Pointer to next Voice MESSAGE 	
}	MSG_NODE;				//	Message Node Struct

typedef	struct  {
	MSG_NODE 	*ptrFirst;	//  Pointer to the first Voice MESSAGE
	const u8 	*ptrL0Str;	//  Line 0 String MESSAGE
	const u8 	*ptrL1Str;  //  Line 1 String MESSAGE
	u8 			value;		//  Value to present (for full!)
	void 		*ptrNext;	//	Pointer to next MESSAGE
}	MSG_LIST;				//	Message List Struct

typedef struct  {
	MSG_NODE *CNode;		//	Pointer to current msg Node
	MSG_LIST *CList;		//	Pointer to current msg List
	MSG_LIST *LList;		//	Pointer to the Last msg List	
}	MSG_IN_ACTION;			//  Message to envoke


typedef struct	{
	u8	speed;			//	Present Speed
	u8 	a_speed;		//	Speedometer Alert Speed	[1- 50Kph City (def) 
						//							 2- 60Kph City 
						//							 3- 70Kph City 
						//							 4- 80Kph Highway 
						//							 5- 90Kph Highway 
						//							 6- 100Kph Highway ]
}	Speedometer;		//	The Speedometer Struct

typedef	struct	{
	u8	fuel;			//	Fuel in litters												 	
	u8	a_fule;			//	Fuel Gauge Alert Litters [1- 5 litters(def) 
						//							  2- 10 litters 
						//							  3- 15 litters 
						//							  4- 20 litters 
						//							  5- 25 litters 
						//							  6- 30 litters ]
}	Fuel_Gauge;	   		//	The Fuel Gauge Struct

typedef struct	{
	u8	tmpr;			//	Temperature
	u8 	alert;			//	Temperature alert [1- Active(def) | 0- not Active]		
}	Thermometer;		//	The Thermometer Struct

typedef	struct	{
	u8	voltage;		//	Acamulator Voltage	
	u8	a_time;			//	Accumulator Alert Time	[0- not Active 
						//							 1- Any Minut(def) 
						//							 2- Any 5 Minuts 
						//							 3- Any 10 Minuts]  	
}	Accumulator;		//	The Accumulator Struct

typedef struct  {
	u8 	ls;				// 	Last doors state
	u8 	ps;				//	Present doors state
	u8 	lfd;			// 	Left front door
	u8 	rfd;			// 	Right front door
	u8	lbd;			// 	Left backdoor
	u8	rbd;			// 	Right backdoor
	u8 	alert;			// 	Doors alert	  [1- active(def) | 0- not Active]
} 	Doors;				// 	The Doors Struct


typedef	struct  {
	u8	key;			//	Entered Key
	u8 	bIndex;			//	Buffer index
	u8  buffer[4];		//	Input Buffer 	
}	KeyPad;				//	The KeyPad Struct

typedef struct {	
	Speedometer		speed;		// 	speed Sub-Struct
	Fuel_Gauge		tank;		// 	fuel Sub-Struct
	Thermometer		temp;		// 	temperatura Sub-Struct
	Accumulator 	acc;		// 	voltage Sub-Struct
	Doors			doors;		// 	doors Sub-Struct
	KeyPad			keys;		// 	keyPad Sub-Struct
	MSG_IN_ACTION	msg;		//	MSG Sub-Struct
	u8				fInterval;	//  Interval for overall msg								 	
} Settings;						//	The Settings Struct 

//---------------------------------------------------------------------------
// Global STATIC
//---------------------------------------------------------------------------
static Settings settings;

//---------------------------------------------------------------------------
// Define Messeges Data
//---------------------------------------------------------------------------
MSG_LIST FMsg1;		//	Incorrect instructions Message
MSG_NODE VMsg1;		//	part of voice msg

MSG_LIST FMsg2;		//	Speed deviation severe Message
MSG_NODE VMsg2;		//	part of voice msg
MSG_NODE VMsg3;		//	part of voice msg
MSG_NODE VMsg4;		//	part of voice msg
MSG_NODE VMsg5;		//	part of voice msg

MSG_LIST FMsg3;		//	Speed deviation Message
MSG_NODE VMsg6;		//	part of voice msg
MSG_NODE VMsg7;		//	part of voice msg
MSG_NODE VMsg8;		//	part of voice msg

MSG_LIST FMsg4;		//	Proper speed Message
MSG_NODE VMsg9;		//	part of voice msg
MSG_NODE VMsg10;	//	part of voice msg

MSG_LIST FMsg5;		//	Fuel is lower than [value] Liter Message
MSG_NODE VMsg11;	//	part of voice msg
MSG_NODE VMsg12;	//	part of voice msg
MSG_NODE VMsg13;	//	part of voice msg
MSG_NODE VMsg14;	//	part of voice msg
MSG_NODE VMsg15;	//	part of voice msg
MSG_NODE VMsg16;	//	part of voice msg
MSG_NODE VMsg17;	//	part of voice msg
MSG_NODE VMsg18;	//	part of voice msg
MSG_NODE VMsg19;	//	part of voice msg
MSG_NODE VMsg20;	//	part of voice msg
MSG_NODE VMsg21;	//	part of voice msg
MSG_NODE VMsg22;	//	part of voice msg
MSG_NODE VMsg23;	//	part of voice msg

MSG_LIST FMsg6;		//	Proper amount of fuel Message
MSG_NODE VMsg24;	//	part of voice msg
MSG_NODE VMsg25;	//	part of voice msg

MSG_LIST FMsg7;		//	Inanimate high temperature	Message
MSG_NODE VMsg26;	//	part of voice msg
MSG_NODE VMsg27;	//	part of voice msg

MSG_LIST FMsg8;		//	Temperature exceeded Message
MSG_NODE VMsg28;	//	part of voice msg
MSG_NODE VMsg29;	//	part of voice msg
MSG_NODE VMsg30;	//	part of voice msg

MSG_LIST FMsg9;		//	Proper temperature	Message
MSG_NODE VMsg31;	//	part of voice msg
MSG_NODE VMsg32;	//	part of voice msg

MSG_LIST FMsg10;	//	Improper voltage Message
MSG_NODE VMsg33;	//	part of voice msg
MSG_NODE VMsg34;	//	part of voice msg

MSG_LIST FMsg11;	//	Proper voltage Message
MSG_NODE VMsg35;	//	part of voice msg
MSG_NODE VMsg36;	//	part of voice msg

MSG_LIST FMsg12;	//	Front left door open Message
MSG_NODE VMsg37;	//	part of voice msg
MSG_NODE VMsg38;	//	part of voice msg
MSG_NODE VMsg39;	//	part of voice msg
MSG_NODE VMsg40;	//	part of voice msg

MSG_LIST FMsg13;	//	Front right door open Message
MSG_NODE VMsg41;	//	part of voice msg
MSG_NODE VMsg42;	//	part of voice msg
MSG_NODE VMsg43;	//	part of voice msg
MSG_NODE VMsg44;	//	part of voice msg

MSG_LIST FMsg14;	//	Rear left door open Message
MSG_NODE VMsg45;	//	part of voice msg
MSG_NODE VMsg46;	//	part of voice msg
MSG_NODE VMsg47;	//	part of voice msg
MSG_NODE VMsg48;	//	part of voice msg

MSG_LIST FMsg15;	//	Rear right door open Message
MSG_NODE VMsg49;	//	part of voice msg
MSG_NODE VMsg50;	//	part of voice msg
MSG_NODE VMsg51;	//	part of voice msg
MSG_NODE VMsg52;	//	part of voice msg

MSG_LIST FMsg16;	//	Proper doors Status Message
MSG_NODE VMsg53;	//	part of voice msg
MSG_NODE VMsg54;	//	part of voice msg

//---------------------------------------------------------------------------
// Function PROTOTYPE:
//---------------------------------------------------------------------------
void inIt_Settings();

//---------------------------------------------------------------------------
// The Function:
//---------------------------------------------------------------------------


//--------------------------------------------------------------------------
// inIt_settings	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: None
// Discription	: SetUp the "settings" struct, 
//                set all parameters to default values!
//                must to be envoked befor the first use 
//                of the "settings" struct!
//
//-------------------------------------------------------------------------
void inIt_settings()
{				
	// Speedometer  : speed, a_speed
	settings.speed.speed 		= 	0x00; 
	settings.speed.a_speed 		= 	1;	
	// Thermometer  : tmpr, alert
	settings.temp.tmpr			= 	0x00;			
	settings.temp.alert			= 	1;		
	// Fuel_Gauge	: fuel,  a_fule	
	settings.tank.fuel 			= 	0x00;	
	settings.tank.a_fule 		= 	1;		
	// Accumulator	: voltage, a_time
	settings.acc.voltage		=	0x00;
	settings.acc.a_time			=	1;		
	// Doors		: ls, ps, lfd, rfd, lbd, rbd, alert
	settings.doors.ls			=	0x00;
	settings.doors.ps			=	0x00;
	settings.doors.lfd			=	0;
	settings.doors.rfd			=	0;
	settings.doors.lbd			=	0;
	settings.doors.rbd			=	0;
	settings.doors.alert		=	1;	
	// KeyPad		: key, bIndex, 
	// -> buffer	: buffer[0], buffer[1], buffer[2], buffer[3]	
	settings.keys.key			=	0x00;
	settings.keys.bIndex 		= 	0;
	settings.keys.buffer[0]		=	'\0';
	settings.keys.buffer[1]		=	'\0';
	settings.keys.buffer[2]		=	'\0';
	settings.keys.buffer[3]		=	'\0';
	// Force System Message interval
	settings.fInterval			=	0;
	// Current Message Settings
	// CNode		: pointer to voice message node 
	// CList		: pointer to full message
	// LList		: pointer to Last full message
	settings.msg.CNode	=	0;
	settings.msg.CList	=	0;	
	settings.msg.LList 	=	0;
}

#endif
//===========================================================================
//                  End Of File "DStructure.h"
//===========================================================================
