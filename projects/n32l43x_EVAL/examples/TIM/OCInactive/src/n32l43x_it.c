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
 * @file n32l43x_it.c
 * @author Nations
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "n32l43x_it.h"
#include "main.h"

/** @addtogroup N32L43x_StdPeriph_Template
 * @{
 */

/******************************************************************************/
/*            Cortex-M4 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
 * @brief  This function handles NMI exception.
 */
void NMI_Handler(void)
{
}

/**
 * @brief  This function handles Hard Fault exception.
 */
void HardFault_Handler(void)
{
    /* Go to infinite loop when Hard Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Memory Manage exception.
 */
void MemManage_Handler(void)
{
    /* Go to infinite loop when Memory Manage exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Bus Fault exception.
 */
void BusFault_Handler(void)
{
    /* Go to infinite loop when Bus Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles Usage Fault exception.
 */
void UsageFault_Handler(void)
{
    /* Go to infinite loop when Usage Fault exception occurs */
    while (1)
    {
    }
}

/**
 * @brief  This function handles SVCall exception.
 */
void SVC_Handler(void)
{
}

/**
 * @brief  This function handles Debug Monitor exception.
 */
void DebugMon_Handler(void)
{
}

/**
 * @brief  This function handles SysTick Handler.
 */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 N32L43x Peripherals Interrupt Handlers                     */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_n32l43x.s).                                                 */
/******************************************************************************/

/**
 * @brief  This function handles TIM2 global interrupt request.
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetIntStatus(TIM2, TIM_INT_CC1) != RESET)
    {
        /* Clear TIM2 Capture Compare1 interrupt pending bit*/
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC1);

        /* PC.06 turnoff after 1000 ms */
        GPIO_ResetBits(GPIOC, GPIO_PIN_6);
    }
    else if (TIM_GetIntStatus(TIM2, TIM_INT_CC2) != RESET)
    {
        /* Clear TIM2 Capture Compare2 interrupt pending bit*/
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC2);

        /* PC.07 turnoff after 500 ms */
        GPIO_ResetBits(GPIOC, GPIO_PIN_7);
    }
    else if (TIM_GetIntStatus(TIM2, TIM_INT_CC3) != RESET)
    {
        /* Clear TIM2 Capture Compare3 interrupt pending bit*/
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC3);

        /* PC.08 turnoff after 250 ms */
        GPIO_ResetBits(GPIOC, GPIO_PIN_8);
    }
    else
    {
        /* Clear TIM2 Capture Compare4 interrupt pending bit*/
        TIM_ClrIntPendingBit(TIM2, TIM_INT_CC4);

        /* PC.09 turnoff after 125 ms */
        GPIO_ResetBits(GPIOC, GPIO_PIN_9);
    }
}

/**
 * @}
 */
