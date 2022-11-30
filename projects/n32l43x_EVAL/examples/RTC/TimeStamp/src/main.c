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
#include "log.h"
#include "n32l43x_rtc.h"
#include "n32l43x.h"
#include "User_LED_Config.h"
#include "User_RTC_Config.h"
#include "User_Systick_Config.h"

/** @addtogroup RTC_Calendar
 * @{
 */
/**
 * @brief  EXTI PD8 I/O config and use the EXTI interrupt to trigger time stamp.
 */
void EXTI_PB8_TimeStamp_Configuration(uint32_t TSEdgeSel)
{
    GPIO_InitType GPIO_InitStructure;
    GPIO_InitStruct(&GPIO_InitStructure);
    RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB | RCC_APB2_PERIPH_AFIO, ENABLE);
    /* Configure PB15 in alternate function mode */
    GPIO_InitStructure.Pin = GPIO_PIN_8;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;
    GPIO_InitPeripheral(GPIOB, &GPIO_InitStructure);
    /* Connect PB15 to RTC_AF1 */
    EXTI_RTCTimeStampSel(EXTI_TSSEL_LINE8);
    /* Connect EXTI15 Line to PB15 pin */
    GPIO_ConfigEXTILine(GPIOB_PORT_SOURCE, GPIO_PIN_SOURCE8);
}


void EXTI19_TAMPER_IRQn_Configuration(FunctionalState NewState,uint32_t TSEdgeSel)
{
    //GPIO_InitType GPIO_InitStructure;
    EXTI_InitType EXTI_InitStructure;
    NVIC_InitType NVIC_InitStructure;
    EXTI_ClrITPendBit(EXTI_LINE19);
    EXTI_InitStructure.EXTI_Line                          = EXTI_LINE19;
    EXTI_InitStructure.EXTI_Mode                          = EXTI_Mode_Interrupt;
    if(TSEdgeSel == 0x01)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Rising;  
    else if(TSEdgeSel == 0x02)
        EXTI_InitStructure.EXTI_Trigger   = EXTI_Trigger_Falling;
    else
        printf("\r\n The TSEdgeSel value is error! \r\n");
    EXTI_InitStructure.EXTI_LineCmd                       = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStructure);
    /* Enable the RTC Alarm Interrupt */
    NVIC_InitStructure.NVIC_IRQChannel                    = TAMPER_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority  = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority         = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd                 = NewState;
    NVIC_Init(&NVIC_InitStructure);
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
    /* Initialize LEDs on n32l43x-EVAL board */
    LEDInit(LED1_PORT, LED1_PIN);
    LEDOff(LED1_PORT, LED1_PIN);
    /* Initialize USART,TX: PA9 RX: PA10*/
    log_init();
    log_info("\r\n RTC Init \r\n");
    /* RTC date and time default value*/
    RTC_DateAndTimeDefaultVale();
    /* RTC clock source select */
    RTC_CLKSourceConfig(RTC_CLK_SRC_TYPE_LSE, true, true);
    RTC_PrescalerConfig();
    /* Adjust time by values entered by the user on the hyperterminal */
    RTC_DateRegulate();
    RTC_TimeRegulate();
    /* Adjust time by values entered by the user on the hyperterminal */
    RTC_ConfigCalibOutput(RTC_CALIB_OUTPUT_1HZ);
    /* Calibrate output config,push pull */
    RTC_ConfigOutputType(RTC_OUTPUT_PUSHPULL);
    /* Calibrate output enable*/
    RTC_EnableCalibOutput(ENABLE);
    /* Configure EXTI PD8 pin  connected to RTC TimeStamp
    (while externally feeding PD8 with 1HZ signal output from PC13)
    */
    EXTI_PB8_TimeStamp_Configuration(1);
    EXTI19_TAMPER_IRQn_Configuration(ENABLE,1);
    /* clear RTC time stamp flag  */
    RTC_ClrFlag(RTC_FLAG_TISF);
    RTC_ClrFlag(RTC_FLAG_TISOVF);
    RTC_EnableTimeStamp(RTC_TIMESTAMP_EDGE_FALLING, ENABLE);
    RTC_ConfigInt(RTC_INT_TS,ENABLE);
    while(1)
    {
        if (RTC_GetITStatus(RTC_INT_TS) != RESET)
        {
           /* Every interval delay (1s) displays calendar and clock stamp register contents*/
           RTC_DateShow();
           RTC_TimeShow();
           RTC_TimeStampShow();
           RTC_ClrFlag(RTC_FLAG_TISF);
           RTC_ClrFlag(RTC_FLAG_TISOVF);
        }
        SysTick_Delay_Ms(1000);
    }
}

