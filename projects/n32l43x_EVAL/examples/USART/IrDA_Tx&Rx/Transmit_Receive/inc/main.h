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

//#define _USART1_USART2_
//#define _USART3_UART4_
#define _UART4_UART5_

#ifdef _USART1_USART2_
#define USARTy            USART1
#define USARTy_GPIO       GPIOB
#define USARTy_CLK        RCC_APB2_PERIPH_USART1
#define USARTy_GPIO_CLK   RCC_APB2_PERIPH_GPIOB
#define USARTy_RxPin      GPIO_PIN_7
#define USARTy_TxPin      GPIO_PIN_8
#define USARTy_Rx_GPIO_AF GPIO_AF0_USART1
#define USARTy_Tx_GPIO_AF GPIO_AF0_USART1
#define USARTy_APBxClkCmd RCC_EnableAPB2PeriphClk

#define USARTz            USART2
#define USARTz_GPIO       GPIOA
#define USARTz_CLK        RCC_APB1_PERIPH_USART2
#define USARTz_GPIO_CLK   RCC_APB2_PERIPH_GPIOA
#define USARTz_RxPin      GPIO_PIN_3
#define USARTz_TxPin      GPIO_PIN_2
#define USARTz_Rx_GPIO_AF GPIO_AF4_USART2
#define USARTz_Tx_GPIO_AF GPIO_AF4_USART2
#define USARTz_APBxClkCmd RCC_EnableAPB1PeriphClk
#define USARTz_IRQn       USART2_IRQn
#define USARTz_IRQHandler USART2_IRQHandler
#endif

#ifdef _USART3_UART4_
#define USARTy            USART3
#define USARTy_GPIO       GPIOC
#define USARTy_CLK        RCC_APB1_PERIPH_USART3
#define USARTy_GPIO_CLK   RCC_APB2_PERIPH_GPIOC
#define USARTy_RxPin      GPIO_PIN_11
#define USARTy_TxPin      GPIO_PIN_10
#define USARTy_Rx_GPIO_AF GPIO_AF5_USART3
#define USARTy_Tx_GPIO_AF GPIO_AF5_USART3
#define USARTy_APBxClkCmd RCC_EnableAPB1PeriphClk

#define USARTz            UART4
#define USARTz_GPIO       GPIOB
#define USARTz_CLK        RCC_APB2_PERIPH_UART4
#define USARTz_GPIO_CLK   RCC_APB2_PERIPH_GPIOB
#define USARTz_RxPin      GPIO_PIN_15
#define USARTz_TxPin      GPIO_PIN_14
#define USARTz_Rx_GPIO_AF GPIO_AF6_USART2
#define USARTz_Tx_GPIO_AF GPIO_AF6_USART2
#define USARTz_APBxClkCmd RCC_EnableAPB2PeriphClk
#define USARTz_IRQn       UART4_IRQn
#define USARTz_IRQHandler UART4_IRQHandler
#endif

#ifdef _UART4_UART5_
#define USARTy            UART4
#define USARTy_GPIO       GPIOC
#define USARTy_CLK        RCC_APB2_PERIPH_UART4
#define USARTy_GPIO_CLK   RCC_APB2_PERIPH_GPIOC
#define USARTy_RxPin      GPIO_PIN_11
#define USARTy_TxPin      GPIO_PIN_10
#define USARTy_Rx_GPIO_AF GPIO_AF6_UART4
#define USARTy_Tx_GPIO_AF GPIO_AF6_UART4
#define USARTy_APBxClkCmd RCC_EnableAPB2PeriphClk

#define USARTz            UART5
#define USARTz_GPIO       GPIOB
#define USARTz_CLK        RCC_APB2_PERIPH_UART5
#define USARTz_GPIO_CLK   RCC_APB2_PERIPH_GPIOB
#define USARTz_RxPin      GPIO_PIN_5
#define USARTz_TxPin      GPIO_PIN_4
#define USARTz_Rx_GPIO_AF GPIO_AF7_UART5
#define USARTz_Tx_GPIO_AF GPIO_AF6_UART5
#define USARTz_APBxClkCmd RCC_EnableAPB2PeriphClk
#define USARTz_IRQn       UART5_IRQn
#define USARTz_IRQHandler UART5_IRQHandler
#endif

typedef enum
{
    FAILED = 0,
    PASSED = !FAILED
} TestStatus;

void RCC_Configuration(void);
void GPIO_Configuration(void);
TestStatus Buffercmp(uint8_t* pBuffer1, uint8_t* pBuffer2, uint16_t BufferLength);
void Delay(__IO uint32_t nCount);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H__ */
