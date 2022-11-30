/*****************************************************************************
 * Copyright (c) 2019, Nations Technologies Inc.
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
 * @file main.c
 * @author Nations 
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "n32l43x.h"
#include "log.h"
#include "n32l43x_rcc.h"
#include "User_Sysclock_Config.h"
#include "User_Key_Config.h"


/** @addtogroup PWR_STOP
 * @{
 */



/**
 * @brief  Delay function.
 *     @arg nCount
 */
void delay(vu32 nCount)
{
    vu32 index = 0;
    for (index = (34000 * nCount); index != 0; index--)
    {
    }
}

/**
 * @brief  Main program.
 */
int main(void)
{
    /*!< At this stage the microcontroller clock setting is already configured,
         this is done through SystemInit() function which is called from startup
         file (startup_n32l43x_xx.s) before to branch to application main.
         To reconfigure the default setting of SystemInit() function, refer to
         system_n32l43x.c file
       */
    /* Initialize USART,TX: PA9 RX: PA10*/
    log_init(); 
    /* Enable PWR Clock */
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
      /* Initialize key button interrupt to wakeup LP SLEEP mode*/
    KeyInputExtiInit(KEY_INPUT_PORT, KEY_INPUT_PIN);
      /* Clear the EXIT Interrupt flag */
    EXTI_ClrITPendBit(EXTI_LINE0);
    /*  Enable the DBG_STOP to keep debug in low power  */
    DBG_ConfigPeriph(DBG_SLEEP, ENABLE);
    while (1)
    {
        /* Insert a long delay */
        delay(1000);
        log_info("\r\n MCU Prepare Enter LP Sleep Mode Core Stop Run \r\n");
        /* Request to enter LP SLEEP mode*/
        PWR_EnterLowPowerSleepMode(SLEEP_OFF_EXIT, PWR_SLEEPENTRY_WFE);
        /* MCU wakeup from LP SLEEP mode by interrupt and goto the LP RUN mode */
        delay(10);
        /* Exit LP RUN mode*/
        PWR_ExitLowPowerRunMode();
        /* Switch sysclok from MSI to PLL */
        SetSysClockToPLL(108000000,SYSCLK_PLLSRC_HSE_PLLDIV2);
        log_info("\r\n MCU Run In Run Mode Sysclock From PLL(108MHz) \r\n");
    }
}


