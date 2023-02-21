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
 * @file glass_lcd.h
 * @author Nations 
 * @version V1.2.1
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _GLASS_LCD_H
#define _GLASS_LCD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "n32l43x.h"   
#include "n32l43x_lcd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup N32L43x_EVAL
  * @{
  */

/** @addtogroup N32L43x_EVAL_GLASS_LCD
  * @{
  */

/* Exported types ------------------------------------------------------------*/

/** @defgroup N32L43x_EVAL_GLASS_LCD_Exported_Types Exported Types
  * @{
  */
/**
  * @brief LCD Glass point
  * Warning: element values correspond to LCD Glass point.
  */

typedef enum
{
  POINT_OFF = 0,
  POINT_ON = 1
}Point_Typedef;

/**
  * @brief LCD Glass Double point
  * Warning: element values correspond to LCD Glass Double point.
  */
typedef enum
{
  DOUBLEPOINT_OFF = 0,
  DOUBLEPOINT_ON = 1
}DoublePoint_Typedef;

/**
  * @brief LCD Glass Battery Level
  * Warning: element values correspond to LCD Glass Battery Level.
  */

typedef enum
{
  BATTERYLEVEL_OFF  = 0,
  BATTERYLEVEL_1_4  = 1,
  BATTERYLEVEL_1_2  = 2,
  BATTERYLEVEL_3_4  = 3,
  BATTERYLEVEL_FULL = 4
}BatteryLevel_TypeDef;

/**
  * @brief LCD Glass Battery Level
  * Warning: element values correspond to LCD Glass Battery Level.
  */

typedef enum
{
  SIGNAL_LEVEL_NONE  = 0,
  SIGNAL_LEVEL_1_CELL  = 1,
  SIGNAL_LEVEL_2_CELLS  = 2,
  SIGNAL_LEVEL_FULL = 3
}SignalLevel_TypeDef;

/**
  * @}
  */

/** @defgroup N32L43x_EVAL_GLASS_LCD_Exported_Constants Exported Constants
  * @{
  */
#define DOT             0x8000 /* for add decimal point in string */
#define DOUBLE_DOT      0x4000 /* for add decimal point in string */

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/

/** @defgroup N32L43x_EVAL_GLASS_LCD_Exported_Functions Exported Functions
  * @{
  */
void BSP_LCD_GLASS_Init(void);
void BSP_LCD_GLASS_BlinkConfig(uint32_t BlinkMode, uint32_t BlinkFrequency);
void BSP_LCD_GLASS_Contrast(uint32_t Contrast);
void BSP_LCD_GLASS_DisplayChar(uint8_t* Ch, Point_Typedef Point, DoublePoint_Typedef DoublePoint, uint8_t Position);
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr);
void BSP_LCD_GLASS_WriteChar(uint8_t* ch, uint8_t Point, uint8_t Column, uint8_t Position);
void BSP_LCD_GLASS_ClearChar(uint8_t position);
void BSP_LCD_GLASS_DisplayStrDeci(uint8_t* ptr);
void BSP_LCD_GLASS_Clear(void);

void BSP_LCD_GLASS_BarLevelConfig(uint8_t BarLevel);
void BSP_LCD_GLASS_SignalLevelConfig(uint8_t SignalLevel);

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

#ifdef __cplusplus
}
#endif

#endif /* __N32L43x_EVAL_GLASS_LCD_H */

/************************ (C) COPYRIGHT Nations Technologies Inc *****END OF FILE****/
