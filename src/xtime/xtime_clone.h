/******************************************************************************
* Copyright (c) 2009 - 2021 Xilinx, Inc.  All rights reserved.
* SPDX-License-Identifier: MIT
******************************************************************************/

/*****************************************************************************/
/**
* @file xtime_clone.h
* xtime_clone emulates the functionality of xtime_l on microblaze systems 
* that are not based on an ARM Coretex PS.
* xtime_l usually provides access to the 64-bit Global Counter in the PMU.
*
******************************************************************************/

/**
*@cond nocomments
*/

#ifndef XTIME_CLONE_H /* prevent circular inclusions */
#define XTIME_CLONE_H /* by using protection macros */

#ifdef __cplusplus
extern "C" {
#endif

/***************************** Include Files *********************************/

#include "xil_types.h"
#include "xparameters.h"

/***************** Macros (Inline Functions) Definitions *********************/

/**************************** Type Definitions *******************************/

typedef u64 XTime;

/************************** Constant Definitions *****************************/
#define GLOBAL_TMR_BASEADDR               XPAR_TIMER_0_BASEADDRESS
#define GTIMER_COUNTER_LOWER_OFFSET       0x00U
#define GTIMER_COUNTER_UPPER_OFFSET       0x04U
#define GTIMER_CONTROL_OFFSET             0x08U

#define COUNTS_PER_SECOND          (XPAR_CPU_CORTEXA9_CORE_CLOCK_FREQ_HZ /1)
/************************** Variable Definitions *****************************/

/**
*@endcond
*/

/************************** Function Prototypes ******************************/

void XTime_SetTime(XTime Xtime_Global);
void XTime_GetTime(XTime *Xtime_Global);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* XTIME_CLONE_H */
/**
* @} End of "addtogroup a9_time_apis".
*/
