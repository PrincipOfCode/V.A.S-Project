//===========================================================================
//             				"OUTPUTS.h"
//===========================================================================
#ifndef OUTPUTS
#define OUTPUTS

//---------------------------------------------------------------------------
// Includes
//---------------------------------------------------------------------------
#include "REG_89C51.h"
#include "type_var_H.h"
#include "Delays_H.h"
#include "DStructure.h"
#include "lcd_TC1602B.h"
#include "ISD25120.h"

//---------------------------------------------------------------------------
// Global CONSTANTS
//---------------------------------------------------------------------------

// define the all the voice msgs addresses that stored in the ISD: 
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
#define MSG_TEMPERATURA		0x83
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

#define FORCE_MESSAGE_INTERVAL	100	// Interval 1 min for Message force

//--------------------------------------------------------------------------
// 	Functions PROTOTYPES
//--------------------------------------------------------------------------
void setMsgNode(MSG_NODE *ptrThis,u8 msgAddr);
void appendMsgNode(MSG_NODE *ptrThis, MSG_NODE *ptrNext);
void replaceMsgNode(MSG_LIST *ptrList, u8 position, MSG_NODE *ptrNew);
void setMsgList(MSG_LIST *ptrThis, MSG_NODE *ptrFirst, const u8 *ptrL0Str, const u8 *ptrL1Str);
void setMsgListValue(MSG_LIST *ptrThis, u8 val);
void appendMsgList(MSG_LIST *ptrNext);
void inItOutPuts();
void playMsg();
bit msgExist(void);


//--------------------------------------------------------------------------
// 	Functions
//--------------------------------------------------------------------------


//--------------------------------------------------------------------------
// setMsgNode	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: 1. pointer (to the voice msg struct)
//                2. voice msg address (in the ISD)
// Discription	: This function set the value of the 
//                voice msg address (for ISD) in the 
//                voice msg struct by refference.
//
//-------------------------------------------------------------------------
void setMsgNode(MSG_NODE *ptrThis,u8 msgAddr)
{
	ptrThis->vMsgAddr 	= 	msgAddr;	// set voice msg address in the struct.
	ptrThis->ptrNext	=	0;			// set next struct pointer to zero.
}

//--------------------------------------------------------------------------
// appendMsgNode	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: 1. pointer (to the voice msg struct)
//                2. pointer (to the next voice msg struct)
// Discription	: This function set the pointer to the  
//                secound (next) voice msg struct, 
//                to build linked list!
//
//-------------------------------------------------------------------------
void appendMsgNode(MSG_NODE *ptrThis, MSG_NODE *ptrNext)
{
	ptrThis->ptrNext	=	(MSG_NODE *)ptrNext;	
}

//--------------------------------------------------------------------------
// replaceMsgNode	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: 1. pointer (to the voice msg list struct,
//                   the HEAD of the voice msg linked list).
//                2. position in the voice msg linked list,
//                   first element (not msg list struct) 
//                   have position zero!
//                3. pointer (to new voice msg struct!).
// Discription	: This function replace element in the 
//                linked list by new element.  
////////////////////// [ Example ] /////////////////////////////////////////
// pos:		0				1				2
//   Parent element	   Old element	   Child element
//     ##########      ##########      ########## 
//     # V  # P-+--x-> # V  # P-+--x-> # V  # P-+--> ... 
//	   #######+##  	   ##########	   ##########
//			  |	   						 ^
//            |        New element       |
//            |        ##########      	 |
//            \------> # V  # P-+--------/
//	            	   ##########		 
//-------------------------------------------------------------------------
void replaceMsgNode(MSG_LIST *ptrList, u8 position, MSG_NODE *ptrNew)
{
	u8 i; 	               // in use for index search
	MSG_NODE *ptrP, *tmp;  // pointers for parrent and child
 	if(ptrList)			   // if this msg List not null then act
	{		
		ptrP = ptrList->ptrFirst;  // set pointer to the first voice msg struct
		if(position == 0)  // if firse element then: msg list struct is parrent
		{
			ptrP = ptrP->ptrNext;					// set pointer to next struct in the list (the child)
			ptrList->ptrFirst =	(MSG_NODE *)ptrNew;	// set pointer to the new voice msg struct from the msg list struct 
			(MSG_NODE *)ptrNew->ptrNext = ptrP;		// set pointer from the new voice msg to the next (child) msg node struct
		}
		else			   // if not first element: 
		{			
			for(i=0;i<position;i++) // seek the element in the linked list  
			{
				tmp = ptrP;		    // set temporary pointer to the present voice msg truct
				ptrP = ptrP->ptrNext; // set pointer to the next voice msg struct in the list
			}
			
			ptrP = ptrP->ptrNext;   //  set pointer to the next voice msg struct in the list
			tmp->ptrNext = (MSG_NODE *)ptrNew;  // set temporary (parent) pointer to the new voice msg struct
			(MSG_NODE *)ptrNew->ptrNext = ptrP;	// set the new voice msg struct next pointer to the child struct in the list.		
		}
	}
}


//--------------------------------------------------------------------------
// setMsgList	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: 1. pointer (to the voice msg list struct 
//                            - the HEAD of the voice msg list)
//                2. pointer (to the first voice msg struct in the list)
//                3. pointer (to the constant string [array of chars] 
//                            to present in the first line in LCD)
//                4. pointer (to the constant string [array of chars] 
//                            to present in the secound line in LCD)
// Discription	: This function set the pointer to the 
//                first voice msg in the list, and
//                set the pointers to the strings 
//                that pressents this msg on the LCD!
//
//-------------------------------------------------------------------------
void setMsgList(MSG_LIST *ptrThis, MSG_NODE *ptrFirst, const u8 *ptrL0Str, const u8 *ptrL1Str)
{
 	ptrThis->ptrFirst 	= 	ptrFirst;  // set pointer to the first voice msg struct.
	ptrThis->ptrL0Str 	= 	ptrL0Str;  // set pointer to the first line String.
	ptrThis->ptrL1Str 	= 	ptrL1Str;  // set pointer to the secound line String.
	ptrThis->value		=	0;		   // set the nummeric value to zero.
	ptrThis->ptrNext	=	0;		   // set msg list pointer to zero (stand alone!).
}

//--------------------------------------------------------------------------
// setMsgListValue
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: 1. pointer (to this msg list struct).
//                2. decimal value to present with the msg.
// Discription	: This function set the value of the 
//                msg list struct to present in the msg, 
//                by refference to this msg list struct.
//
//-------------------------------------------------------------------------
void setMsgListValue(MSG_LIST *ptrThis, u8 val)
{
	ptrThis->value		=	val;
}

//--------------------------------------------------------------------------
// appendMsgList	 
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: pointer (to the current msg list struct)
// Discription	: This function add the current 
//                msg list struct to the end of the 
//                system msg list if he is not in this
//                list, the chack is by comparring this 
//				  msg list struct pointer to the pointers
//                in the system msg list!
//
//-------------------------------------------------------------------------
void appendMsgList(MSG_LIST *ptrNext)
{
	MSG_LIST *tmpPtr; // define temporary pointer
	bit isSet = 0;	  // set the check results to false
	if (settings.msg.LList) // true when system msg list not empty:
	{
		tmpPtr = settings.msg.CList; // set temporary pointer to the current system msg that playing now
		do	// pass over the system msg list to the end
		{
			if(tmpPtr == ptrNext) isSet = 1;  // compare this msg list struct pointer to the temporary msg list struct pointer
		  	tmpPtr = tmpPtr->ptrNext;		  // set temporary msg list struct pointer to next in the system msg list.
		}while(tmpPtr != settings.msg.LList->ptrNext);
		if(!isSet)	 // true if this msg list struct not in the system msg list!
		{
			settings.msg.LList->ptrNext	= (MSG_LIST *)ptrNext;	  // add the msg to the end of the list by set the pointer
			settings.msg.LList = settings.msg.LList->ptrNext;	  // set last system msg list pointer to the same location as the add msg next pointer
			settings.msg.LList->ptrNext = 0;					  // set end of the system msg list (set pointer to zero!)
		}
	}
	else				    // system msg list empty: set this msg as first!
	{
		settings.msg.LList = (MSG_LIST *)ptrNext;			// set last system msg list pointer to this one!
		settings.msg.CList = (MSG_LIST *)ptrNext;			// set current system msg list pointer to this one!
		settings.msg.CNode = settings.msg.CList->ptrFirst;	// set current system voice msg pointer to first voice msg struct of the added msg list!
		settings.msg.CList->ptrNext = 0;					// set end of the system msg list (set pointer to zero!)
	}
}

//--------------------------------------------------------------------------
// inItOutPuts
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: None
// Discription	: This function SetUp (build) all the
//                complex Outupt messages.  
//                By setting the values of all the MSG list
//                structs (the msg) and his voice msg parts,
//                and connect by the pointers the voice msgs
//                to a linked list and to ther HEADs 
//                the msg list structs! 
//                This function must to be envoked befor 
//                the first use of the OUTPUTS in the proggram! 
//
//-------------------------------------------------------------------------
void inItOutPuts()
{
	// set the "Oncorrect instructions" msg:
	setMsgNode(&VMsg1, MSG_WRONG);
	setMsgList(&FMsg1, &VMsg1, "Incorrect       ","instructions    ");

	// set the "Speed deviation severe" msg:
	setMsgNode(&VMsg2, MSG_HARIGA);
	setMsgNode(&VMsg3, MSG_HAMURA);
	setMsgNode(&VMsg4, MSG_MIN_HAMEHIRUT);
	setMsgNode(&VMsg5, MSG_HAMUTERET);		
	appendMsgNode(&VMsg2, &VMsg3);
	appendMsgNode(&VMsg3, &VMsg4);
	appendMsgNode(&VMsg4, &VMsg5);
	setMsgList(&FMsg2, &VMsg2, "Speed deviation ","severe          ");

	// set the "Speed deviation" msg:
	setMsgNode(&VMsg6, MSG_HARIGA);
	setMsgNode(&VMsg7, MSG_M_HAMEHIRUT);
	setMsgNode(&VMsg8, MSG_HAMUTERET);	
	appendMsgNode(&VMsg6, &VMsg7);
	appendMsgNode(&VMsg7, &VMsg8);
	setMsgList(&FMsg3, &VMsg6, "Speed deviation ","                ");
    
	// set the "Proper speed" msg:
	setMsgNode(&VMsg9, MSG_MEHIRUT);
	setMsgNode(&VMsg10, MSG_TKINA);		
	appendMsgNode(&VMsg9, &VMsg10);
	setMsgList(&FMsg4, &VMsg9, "Proper speed    ","                ");	

	// set the "Fuel is lower than Liter" msg:
	setMsgNode(&VMsg11, MSG_KAMUT_DELEK);
	setMsgNode(&VMsg12, MSG_KTANA_ME);
	setMsgNode(&VMsg13, MSG_1);	
	setMsgNode(&VMsg14, MSG_2);
	setMsgNode(&VMsg15, MSG_3);
	setMsgNode(&VMsg16, MSG_4);
	setMsgNode(&VMsg17, MSG_5);
	setMsgNode(&VMsg18, MSG_10);
	setMsgNode(&VMsg19, MSG_15);
	setMsgNode(&VMsg20, MSG_20);
	setMsgNode(&VMsg21, MSG_25);
	setMsgNode(&VMsg22, MSG_30);
	setMsgNode(&VMsg23, MSG_LITER);			
	appendMsgNode(&VMsg11, &VMsg12);
	appendMsgNode(&VMsg12, &VMsg17);
	appendMsgNode(&VMsg17, &VMsg23);
	
	setMsgList(&FMsg5, &VMsg11, "Fuel is lower   ","than    Liter   ");	
	setMsgListValue(&FMsg5, 5);  // set default value for the fule msg to 5 (litters)

	// set the "Proper amount of fuel" msg:
	setMsgNode(&VMsg24, MSG_KAMUT_DELEK);
	setMsgNode(&VMsg25, MSG_TKINA);		
	appendMsgNode(&VMsg24, &VMsg25);
	setMsgList(&FMsg6, &VMsg24, "Proper amount   ","of fuel         ");	

	// set the "Inanimate high temperature" msg:
	setMsgNode(&VMsg26, MSG_TEMPERATURA);
	setMsgNode(&VMsg27, MSG_MESUKENET_STOP);		
	appendMsgNode(&VMsg26, &VMsg27);
	setMsgList(&FMsg7, &VMsg26, "Inanimate high  ","temperature     ");	

	// set the "Temperature exceeded" msg:
	setMsgNode(&VMsg28, MSG_SIM_LEV);
	setMsgNode(&VMsg29, MSG_TEMPERATURA);		
	setMsgNode(&VMsg30, MSG_HARIGA);		
	appendMsgNode(&VMsg28, &VMsg29);
	appendMsgNode(&VMsg29, &VMsg30);
	setMsgList(&FMsg8, &VMsg28, "Temperature     ","exceeded        ");	
    
	// set the "Proper temperature" msg:
	setMsgNode(&VMsg31, MSG_TEMPERATURA);
	setMsgNode(&VMsg32, MSG_TKINA);			
	appendMsgNode(&VMsg31, &VMsg32);
	setMsgList(&FMsg9, &VMsg31, "Proper          ","temperature     ");	

	// set the "Improper voltage" msg:
	setMsgNode(&VMsg33, MSG_METAH_MAZBER);
	setMsgNode(&VMsg34, MSG_LO_TAKIN);			
	appendMsgNode(&VMsg33, &VMsg34);
	setMsgList(&FMsg10, &VMsg33, "Improper voltage","                ");	

    // set the "Proper voltage" msg:
	setMsgNode(&VMsg35, MSG_METAH_MAZBER);
	setMsgNode(&VMsg36, MSG_TAKIN);			
	appendMsgNode(&VMsg35, &VMsg36);
	setMsgList(&FMsg11, &VMsg35, "Proper voltage  ","                ");	

	// set the "Front left door open" msg:
	setMsgNode(&VMsg37, MSG_DELET);
	setMsgNode(&VMsg38, MSG_SMALE);			
	setMsgNode(&VMsg39, MSG_KEDMIT);
	setMsgNode(&VMsg40, MSG_PTUHA);
	appendMsgNode(&VMsg37, &VMsg38);
	appendMsgNode(&VMsg38, &VMsg39);
	appendMsgNode(&VMsg39, &VMsg40);
	setMsgList(&FMsg12, &VMsg37, "Front left door ","open            ");	
    
	// set the "Front right door open" msg:
	setMsgNode(&VMsg41, MSG_DELET);
	setMsgNode(&VMsg42, MSG_YAMIN);			
	setMsgNode(&VMsg43, MSG_KEDMIT);
	setMsgNode(&VMsg44, MSG_PTUHA);
	appendMsgNode(&VMsg41, &VMsg42);
	appendMsgNode(&VMsg42, &VMsg43);
	appendMsgNode(&VMsg43, &VMsg44);
	setMsgList(&FMsg13, &VMsg41, "Front right door","open            ");	

	// set the "Rear left door open" msg:
	setMsgNode(&VMsg45, MSG_DELET);
	setMsgNode(&VMsg46, MSG_SMALE);			
	setMsgNode(&VMsg47, MSG_AHORIT);
	setMsgNode(&VMsg48, MSG_PTUHA);
	appendMsgNode(&VMsg45, &VMsg46);
	appendMsgNode(&VMsg46, &VMsg47);
	appendMsgNode(&VMsg47, &VMsg48);
	setMsgList(&FMsg14, &VMsg45, "Rear left door  ","open            ");	
    
	// set the "Rear right door open" msg:
	setMsgNode(&VMsg49, MSG_DELET);
	setMsgNode(&VMsg50, MSG_YAMIN);			
	setMsgNode(&VMsg51, MSG_AHORIT);
	setMsgNode(&VMsg52, MSG_PTUHA);
	appendMsgNode(&VMsg49, &VMsg50);
	appendMsgNode(&VMsg50, &VMsg51);
	appendMsgNode(&VMsg51, &VMsg52);
	setMsgList(&FMsg15, &VMsg49, "Rear right door ","open            ");	

	// set the "Proper doors Status" msg:
	setMsgNode(&VMsg53, MSG_MAZAV_HADLATOT);
	setMsgNode(&VMsg54, MSG_TAKIN);			
	appendMsgNode(&VMsg53, &VMsg54);
	setMsgList(&FMsg16, &VMsg53, "Proper doors    ","Status          ");	

}

//--------------------------------------------------------------------------
// playMsg
//--------------------------------------------------------------------------
//
// Return Value : None
// Parameters 	: None
// Discription	: This function push the current msg to
//                the LCD and also play the current part
//                of the voice msg (by ISD functions).  
//                the function use system msg pointer to
//                pass over the msgs in the list and there 
//                voice msg parts, any time ONE voice msg 
//                part envoked (played)!
//
//-------------------------------------------------------------------------
void playMsg()
{
	// check if this is the first voice msg of the msg:
	if((settings.msg.CList->ptrFirst == settings.msg.CNode)&&(settings.msg.CList->ptrFirst))
	{
		print_lcd(0,0,settings.msg.CList->ptrL0Str);  // print the first line of the msg String.
		print_lcd(1,0,settings.msg.CList->ptrL1Str);  // print the secound line of the msg String.		
		if(settings.msg.CList->value != 0)			  // check if there is decimal value to present 
		                                              // (will have value only if this is a feul msg!).
			print_dec_lcd(1,4,settings.msg.CList->value);  // print the decimal value.

	}
	if(settings.msg.CList)
	{
		if(settings.msg.CNode != 0) // check current voice msg pointer (true when there is voice msg to execute!).
		{
			// execute/play this MSG Node:
			playback_ISD(settings.msg.CNode->vMsgAddr);	
			// set pointer to next MSG Node:
			settings.msg.CNode = settings.msg.CNode->ptrNext;
		}
		else   // if no msg voice to execute find next one:
		{
			if((settings.msg.CList->ptrNext != 0)&&(settings.msg.LList != settings.msg.CList)) // check if there is more msg in the system msg list to envoke:
			{			
				// Go to next MSG List Element:
				settings.msg.CList = settings.msg.CList->ptrNext;
				// Set First Node Message:
				settings.msg.CNode = settings.msg.CList->ptrFirst;
			}
			else  // no more msgs to play, set system msg pointers to ZERO! 
			{
				// when current element = last element = 0 then no more msg in the list!
				settings.msg.CList = 0; // set current system msg list pointer to zero!
			   	settings.msg.CNode = 0;	// set current system voice msg pointer to zero!
				settings.msg.LList = 0;	// set last system msg list pointer to zero!
			}
		}
	}
}

//--------------------------------------------------------------------------
// msgExist
//--------------------------------------------------------------------------
//
// Return Value : bit [0- false (empty), 1- true (not empty)]
// Parameters 	: None
// Discription	: The Function check if there is msg in the 
//                system msg list to play, by comparing  
//                the pointers to zero, if empty then pointers
//                must to point to zero!
//                else the system msg list not empty!
//
//-------------------------------------------------------------------------
bit msgExist()
{
	if((settings.msg.CList == 0)&&(settings.msg.LList == 0))	return 0;
	return 1;

}


#endif
//===========================================================================
//                  End Of File "OUTPUTS.h"
//===========================================================================