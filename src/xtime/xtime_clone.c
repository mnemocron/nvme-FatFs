/******************************************************************************
* Copyright (c) 2009 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
* @file xtime_clone.c
* xtime_clone emulates the functionality of xtime_l on microblaze systems 
* that are not based on an ARM Coretex PS.
* xtime_l usually provides access to the 64-bit Global Counter in the PMU.
*
******************************************************************************/
/***************************** Include Files *********************************/

#include "xtime_l.h"
//#include "xpseudo_asm.h"
#include "xil_types.h"
#include "xil_assert.h"
#include "xil_io.h"

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

/************************** Constant Definitions *****************************/

/************************** Variable Definitions *****************************/

/************************** Function Prototypes ******************************/
#if defined (XSLEEP_TIMER_IS_DEFAULT_TIMER)
#pragma message ("For the sleep routines, Global timer is being used")
#endif
/****************************************************************************/
/**
* @brief	Set the time in the Global Timer Counter Register.
*
* @param	Xtime_Global: 64-bit Value to be written to the Global Timer
*			Counter Register.
*
* @return	None.
*
* @note		When this function is called by any one processor in a multi-
*			processor environment, reference time will reset/lost for all
*			processors.
*
****************************************************************************/
void XTime_SetTime(XTime Xtime_Global)
{
	/* Disable Global Timer */
	Xil_Out32((u32)GLOBAL_TMR_BASEADDR + (u32)GTIMER_CONTROL_OFFSET, (u32)0x0);

	/* Updating Global Timer Counter Register */
	Xil_Out32((u32)GLOBAL_TMR_BASEADDR + (u32)GTIMER_COUNTER_LOWER_OFFSET, (u32)Xtime_Global);
	Xil_Out32((u32)GLOBAL_TMR_BASEADDR + (u32)GTIMER_COUNTER_UPPER_OFFSET,
		(u32)((u32)(Xtime_Global>>32U)));

	/* Enable Global Timer */
	Xil_Out32((u32)GLOBAL_TMR_BASEADDR + (u32)GTIMER_CONTROL_OFFSET, (u32)0x1);
}

/****************************************************************************/
/**
* @brief	Get the time from the Global Timer Counter Register.
*
* @param	Xtime_Global: Pointer to the 64-bit location which will be
*			updated with the current timer value.
*
* @return	None.
*
* @note		None.
*
****************************************************************************/
void XTime_GetTime(XTime *Xtime_Global)
{
	u32 low;
	u32 high;

	/* Reading Global Timer Counter Register */
	do
	{
		high = Xil_In32(GLOBAL_TMR_BASEADDR + GTIMER_COUNTER_UPPER_OFFSET);
		low = Xil_In32(GLOBAL_TMR_BASEADDR + GTIMER_COUNTER_LOWER_OFFSET);
	} while(Xil_In32(GLOBAL_TMR_BASEADDR + GTIMER_COUNTER_UPPER_OFFSET) != high);

	*Xtime_Global = (((XTime) high) << 32U) | (XTime) low;
}
