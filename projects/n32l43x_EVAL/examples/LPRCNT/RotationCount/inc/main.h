/*****************************************************************************
 * Copyright (c) 2022, Nations Technologies Inc.
 *
 * All rights reserved.
 * ****************************************************************************
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the disclaimer below.
 *
 * Nations' name may not be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * DISCLAIMER: THIS SOFTWARE IS PROVIDED BY NATIONS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT ARE
 * DISCLAIMED. IN NO EVENT SHALL NATIONS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * ****************************************************************************/

/**
 * @file main.h
 * @author Nations 
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#ifndef __MAIN_H__
#define __MAIN_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "n32l43x.h"
#include "glass_lcd.h"
#include "n32l43x_lprcnt.h"
#include "n32l43x_exti.h"
#include "log.h"
/*Led1-PB0,Led2-PB1,Led3-PE0,Led4-PE1,Led5-PE5*/
#define PORT_GROUP1 GPIOD

#define LED1_PORT   PORT_GROUP1

#define LED1_PIN    GPIO_PIN_0

#ifdef __cplusplus
}
#endif

/* LPRCNT SENSOR CHANNAL PARAGRAM*/
//chanal0
#define CHANAL0_TIME_VIBRATION         70  
#define CHANAL0_TIME_DISCHARGE         2 
#define CHANAL0_TIME_CHARGE            3 

#define CHANAL0_THRESHOLD_DACREF       58
#define CHANAL0_THRESHOLD_UNDAMPED     62
#define CHANAL0_THRESHOLD_DAMPED       58
//chanal1
#define CHANAL1_TIME_VIBRATION         70 
#define CHANAL1_TIME_DISCHARGE         5 
#define CHANAL1_TIME_CHARGE            3 

#define CHANAL1_THRESHOLD_DACREF       58
#define CHANAL1_THRESHOLD_UNDAMPED     54
#define CHANAL1_THRESHOLD_DAMPED       51

//chanal2
#define CHANAL2_TIME_VIBRATION         70 
#define CHANAL2_TIME_DISCHARGE         5
#define CHANAL2_TIME_CHARGE            3 

#define CHANAL2_THRESHOLD_DACREF       58
#define CHANAL2_THRESHOLD_UNDAMPED     29
#define CHANAL2_THRESHOLD_DAMPED       28

/* LPRCNT SENSOR SCAN PERIOD*/
#define NORMAL_HIGH_PER   5
#define NORMAL_LOW_PER   330
#define NORMAL_SW_TIM   15

//circle
#define REPORT_CIRCLE  100


#endif /* __MAIN_H__ */
/**
 * @}
 */

/**
 * @}
 */

/**
 * @}
 */
