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
 * @file glass_lcd.c
 * @author Nations 
 * @version v1.0.0
 *
 * @copyright Copyright (c) 2019, Nations Technologies Inc. All rights reserved.
 */

/* Includes ------------------------------------------------------------------*/
#include "glass_lcd.h"

/** @addtogroup BSP
  * @{
  */

/** @addtogroup N32L43x_EVAL
  * @{
  */

/** @defgroup N32L43x_EVAL_GLASS_LCD N32L43x_EVAL GLASS LCD
  * @brief This file includes the LCD Glass driver for LCD_XHO5002B Module of
  *        STM32L476G-EVAL board.
  * @{
  */


/* Private constants ---------------------------------------------------------*/

/** @defgroup N32L43x_EVAL_GLASS_LCD_Private_Constants Private Constants
  * @{
  */
#define ASCII_CHAR_SPACE              0x20  /*   */
#define ASCII_CHAR_FORWARD_SLASH      0x2F  /* / */
#define ASCII_CHAR_0                  0x30  /* 0 */
#define ASCII_CHAR_COLON              0x3A  /* : */
#define ASCII_CHAR_AT_SYMBOL          0x40  /* @ */
#define ASCII_CHAR_A                  0x41  /* A */
#define ASCII_CHAR_LEFT_OPEN_BRACKET  0x5B  /* [ */
/**
  * @}
  */

/* Private variables ---------------------------------------------------------*/

/** @defgroup N32L43x_EVAL_GLASS_LCD_Private_Variables Private Variables
  * @{
  */

/**
================================================================================
                              GLASS LCD MAPPING
================================================================================
               A
          ----------
          |         |
         F|         |B
          |         |
          ---- G ----
          |         |
         E|         |C
          |         |  _
          ----------- |_|DP  
              D

A LCD character coding is based on the following matrix:
             COM0    COM1    COM2    COM3     
  SEG(n)    { F ,     G ,     E ,     D   }
  SEG(n+1)  { A ,     B ,     C ,     DP  }
The character 2 for example is:
-----------------------------------------------------------
             COM0    COM1     COM2    COM3  
  SEG(n)    { 0 ,     1 ,      1 ,     1  }
  SEG(n+1)  { 1 ,     1 ,      0 ,     0  }
   --------------------------------------------------------
           =  2       3        1       1      hex

   => '2' = 0x002311

  */

LCD_HandleType LCDHandle;

/**
  * @brief LETTERS AND NUMBERS MAPPING DEFINITION
  */
#define  COM_NUM      4

__IO const uint32_t Mask[COM_NUM] =
  {
    0x0000F000, 0x00000F00, 0x000000F0, 0x0000000F
  };

const uint8_t Shift[COM_NUM] =
  {
    12, 8, 4, 0
  };


uint32_t Digit[COM_NUM]={0};     /* Digit frame buffer */


__IO const uint32_t NumberMap[10] =
  {
    /*   0           1           2          3           4   */
    0x00003231, 0x00000220, 0x00002311, 0x00002321, 0x00001320,
    /*    5         6            7          8           9   */
    0x00003121, 0x00003131, 0x00002220, 0x00003331, 0x00003321
  };
__IO const uint32_t LetterMap[26] =
  {
    /*  A            B          C           D           E            F   */
    0x00003231, 0x00000000, 0x00003011, 0x00000000, 0x00003111, 0x00003110,
    /*   G            H          I            J           K         L    */
    0x00003031, 0x00001331, 0x00000000, 0x00000221, 0x00000000, 0x00001011,
    /*   M          N           O            P          Q         R      */
    0x00000000, 0x00000000, 0x00000000, 0x00003310, 0x00000000, 0x00003330,
    /*   S           T           U           V           W           X   */
    0x00003121, 0x00000000, 0x00001231, 0x00000000, 0x00000000, 0x00000000,
    /*  Y          Z     */
    0x00000000, 0x00000000
  }; //Letter unable display use 0x00000000 

/**
  * @}
  */

/** @defgroup N32L43x_EVAL_GLASS_LCD_Private_Functions Private Functions
  * @{
  */
static void Convert(uint8_t* c, Point_Typedef Point, DoublePoint_Typedef DoublePoint);
static void LCD_MspInit(LCD_HandleType *hlcd);

/**
  * @}
  */

/** @addtogroup N32L43x_EVAL_GLASS_LCD_Exported_Functions
  * @{
  */

/**
  * @brief  Configures the LCD GLASS relative GPIO port IOs and LCD peripheral.
  * @retval None
  */
void BSP_LCD_GLASS_Init(void)
{
  LCDHandle.Instance              = LCD;
  LCDHandle.Init.Prescaler        = LCD_Prescaler_1;
  LCDHandle.Init.Divider          = LCD_DIV_16;
  LCDHandle.Init.Duty             = LCD_Duty_1_4;//com number
  LCDHandle.Init.Bias             = LCD_Bias_1_3; //electrical level number
  LCDHandle.Init.VoltageSource    = LCD_VoltageSource_Internal; // LCD_VOLTAGESOURCE_EXTERNAL
  LCDHandle.Init.Contrast         = LCD_ContrastLevel_3;//max voltage //LCD_CONTRASTLEVEL_7;
  LCDHandle.Init.DeadTime         = LCD_DeadTime_0;
  LCDHandle.Init.PulseOnDuration  = LCD_PulseOnDuration_7;//LCD_PULSEONDURATION_2
  LCDHandle.Init.HighDrive        = LCD_HighDriver_Disable;//
    LCDHandle.Init.HighDriveBuffer  = LCD_HighDriverBuffer_Disable;
  LCDHandle.Init.BlinkMode        = LCD_BlinkMode_Off;//LCD_BLINKMODE_SEG0_ALLCOM
  LCDHandle.Init.BlinkFreq   = LCD_BlinkFreq_Div_8;
  LCDHandle.Init.MuxSegment       = LCD_MuxSegment_Disable;


  LCD_RESET_HANDLE_STATE(&LCDHandle);

  /* Initialize the LCD */
  LCD_MspInit(&LCDHandle);
}

/**
  * @brief This function writes a char in the LCD frame buffer.
  * @param ch: the character to display.
  * @param Point: a point to add in front of char
  *        This parameter can be: POINT_OFF or POINT_ON
  * @param Column: flag indicating if a column has to be add in front
  *        of displayed character.
  *        This parameter can be: DOUBLEPOINT_OFF or DOUBLEPOINT_ON.
  * @param Position: position in the LCD of the caracter to write [1:7]
  * @retval None
  * @note  Required preconditions: The LCD should be cleared before to start the
  *        write operation.
  */
void BSP_LCD_GLASS_WriteChar(uint8_t* ch, uint8_t Point, uint8_t Column, uint8_t Position)
{
  /* To convert displayed character in segment in array digit */
  Convert(ch, (Point_Typedef)Point, (DoublePoint_Typedef)Column);
  switch(Position)
  {
    /* Position 1 on LCD,SEG5 and SEG6*/
    case 1:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFF9F, (Digit[0] << (uint32_t)0x05));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFF9F, (Digit[1] << (uint32_t)0x05));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFF9F, (Digit[2] << (uint32_t)0x05));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFF9F, (Digit[3] << (uint32_t)0x05));
      break;

    /* Position 2 on LCD,SEG7 and SEG8 */
    case 2:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFE7F, (Digit[0] << (uint32_t)0x07));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFE7F, (Digit[1] << (uint32_t)0x07));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFE7F, (Digit[2] << (uint32_t)0x07));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFE7F, (Digit[3] << (uint32_t)0x07));
      break;

    /* Position 3 on LCD,SEG10 and SEG11 */
    case 3:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFF3FF, (Digit[0] << (uint32_t)0x0A));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFF3FF, (Digit[1] << (uint32_t)0x0A));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFF3FF, (Digit[2] << (uint32_t)0x0A));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFF3FF, (Digit[3] << (uint32_t)0x0A));
      break;

    /* Position 4 on LCD,SEG19 and SEG20 */
    case 4:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFE7FFFF, (Digit[0] << (uint32_t)0x13));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFE7FFFF, (Digit[1] << (uint32_t)0x13));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFE7FFFF, (Digit[2] << (uint32_t)0x13));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFE7FFFF, (Digit[3] << (uint32_t)0x13));
      break;

    /* Position 5 on LCD,SEG22 and SEG23 */
    case 5:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFF3FFFFF, (Digit[0] << (uint32_t)0x16));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFF3FFFFF, (Digit[1] << (uint32_t)0x16));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFF3FFFFF, (Digit[2] << (uint32_t)0x16));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFF3FFFFF, (Digit[3] << (uint32_t)0x16));
      break;

    /* Position 6 on LCD,SEG24 and SEG25 */
    case 6:
      /* Write Digit 0 on COM0 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFCFFFFFF, (Digit[0] << (uint32_t)0x18));
      /* Write Digit 1 on COM1 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFCFFFFFF, (Digit[1] << (uint32_t)0x18));
      /* Write Digit 2 on COM2 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFCFFFFFF, (Digit[2] << (uint32_t)0x18));
      /* Write Digit 3 on COM3 */
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFCFFFFFF, (Digit[3] << (uint32_t)0x18));
      break;

    default:
      break;
  }

  /* Update the LCD display */
  LCD_UpdateDisplayRequest(LCDHandle.Instance);
}

/**
  * @brief Setting bar on LCD, writes bar value in LCD frame buffer
  * @param BarLevel: specifies the LCD GLASS Battery Level.
  *     This parameter can be one of the following values:
  *     @arg BATTERYLEVEL_OFF: LCD GLASS Batery Empty
  *     @arg BATTERYLEVEL_1_4: LCD GLASS Batery 1/4 Full
  *     @arg BATTERYLEVEL_1_2: LCD GLASS Batery 1/2 Full
  *     @arg BATTERYLEVEL_3_4: LCD GLASS Batery 3/4 Full
  *     @arg BATTERYLEVEL_FULL: LCD GLASS Batery Full
  * @retval None
  */
void BSP_LCD_GLASS_BarLevelConfig(uint8_t BarLevel)
{
  switch (BarLevel)
  {
  /* Battery Level Off */
  case BATTERYLEVEL_OFF:
    /* Set BATTERYLEVEL_1_4 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_1_2 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_3_4 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_FULL off and Battery positive sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFC, (uint32_t)(0x00000001));
    break;

  /* Battery Level 1/4 */
  case BATTERYLEVEL_1_4:
    /* Set BATTERYLEVEL_1_4  on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BATTERYLEVEL_1_2 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_3_4 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_FULL off and Battery positive sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFC, (uint32_t)(0x00000001));
    break;

  /* Battery Level 1/2 */
  case BATTERYLEVEL_1_2:
    /* Set BatteryLevel_1_4 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_1_2 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BATTERYLEVEL_3_4 off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFD, (uint32_t)(0x00000000));
    /* Set BATTERYLEVEL_FULL off and Battery positive sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFC, (uint32_t)(0x00000001));
    break;

  /* Battery Level 3/4 */
  case BATTERYLEVEL_3_4:
    /* Set BatteryLevel_1_4 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_1_2 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_3_4 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BATTERYLEVEL_FULL off and Battery positive sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFC, (uint32_t)(0x00000001));
    break;

  /* Battery Level Full */
  case BATTERYLEVEL_FULL:
    /* Set BatteryLevel_1_4 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_1_2 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_3_4 on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFD, (uint32_t)(0x00000002));
    /* Set BatteryLevel_FULL and Battery positive sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFC, (uint32_t)(0x00000003));
    break;

  default:
    break;
  }

  /* Update the LCD display */
  LCD_UpdateDisplayRequest(LCDHandle.Instance);
}
/**
  * @brief Setting Signal strength on LCD, writes Signal value in LCD frame buffer
  * @param SignalLevel: specifies the LCD GLASS Signal Level.
  *     This parameter can be one of the following values:
  *     @arg SIGNAL_LEVEL_OFF: LCD GLASS Signal None
  *     @arg SIGNAL_LEVEL_1_4: LCD GLASS Signal 1 cell
  *     @arg SIGNAL_LEVEL_1_2: LCD GLASS Signal 2 cells
  *     @arg SIGNAL_LEVEL_FULL: LCD GLASS Signal Full
  * @retval None
  */
void BSP_LCD_GLASS_SignalLevelConfig(uint8_t SignalLevel)
{
  switch (SignalLevel)
  {
  /* Signal Level None */
  case SIGNAL_LEVEL_NONE:
    /* Set SIGNAL_LEVEL sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_1_CELL off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    /* Set SIGNAL_LEVEL_2_CELLS off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    /* Set SIGNAL_LEVEL_FULL off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    break;

  /* Signal Level 1 Cell */
  case SIGNAL_LEVEL_1_CELL:
    /* Set SIGNAL_LEVEL sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_1_CELL on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_2_CELLS off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    /* Set SIGNAL_LEVEL_FULL off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    break;

  /* Signal Level 2 Cells */
  case SIGNAL_LEVEL_2_CELLS:
    /* Set SIGNAL_LEVEL sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_1_CELL on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_2_CELLS on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_FULL off  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFB, (uint32_t)(0x00000000));
    break;

  /* Signal Level Full */
  case SIGNAL_LEVEL_FULL:
    /* Set SIGNAL_LEVEL sign on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_1_CELL on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_2_CELLS on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    /* Set SIGNAL_LEVEL_FULL on  */
    LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFFFB, (uint32_t)(0x00000004));
    break;

  default:
    break;
  }

  /* Update the LCD display */
  LCD_UpdateDisplayRequest(LCDHandle.Instance);
}
/**
  * @brief This function Clear a char in the LCD RAM.
  * @param position: Position in the LCD of the caracter to write.
  *                  This parameter can be any value in range [1:7].
  * @retval None
  */
void BSP_LCD_GLASS_ClearChar(uint8_t position)
{
  switch (position)
  {
    /* Clear position 1 on LCD */
    case 1:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFF9F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFF9F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFF9F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFF9F, 0);
      break;

    /* Clear position 2 on LCD */
    case 2:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFFE7F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFFE7F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFFE7F, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFFE7F, 0);
      break;

    /* Clear position 3 on LCD */
    case 3:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFFFF3FF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFFFF3FF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFFFF3FF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFFFF3FF, 0);
      break;

    /* Clear position 4 on LCD */
    case 4:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFFE7FFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFFE7FFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFFE7FFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFFE7FFFF, 0);
      break;

    /* Clear position 5 on LCD */
    case 5:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFF3FFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFF3FFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFF3FFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFF3FFFFF, 0);
      break;

    /* Clear position 6 on LCD */
    case 6:
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM0_1, 0xFCFFFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM1_1, 0xFCFFFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM2_1, 0xFCFFFFFF, 0);
      LCD_Write(LCDHandle.Instance, LCD_RAM_COM3_1, 0xFCFFFFFF, 0);
      break;
    
    default:
      break;
  }
  /* Update the LCD display */
  LCD_UpdateDisplayRequest(LCDHandle.Instance);
}

/**
  * @brief  This function writes a char in the LCD RAM.
  * @param  Ch: The character to display.
  * @param  Point: A point to add in front of char.
  *          This parameter  can be one of the following values:
  *              @arg POINT_OFF: No point to add in front of char.
  *              @arg POINT_ON: Add a point in front of char.
  * @param  DoublePoint: Flag indicating if a apostrophe has to be add in front
  *                     of displayed character.
  *          This parameter  can be one of the following values:
  *              @arg DOUBLEPOINT_OFF: No colon to add in back of char.
  *              @arg DOUBLEPOINT_ON: Add an colon in back of char.
  * @param  Position: Position in the LCD of the caracter to write.
  *                   This parameter can be any value in range [1:7].
  * @retval None
  */
void BSP_LCD_GLASS_DisplayChar(uint8_t* Ch, Point_Typedef Point, DoublePoint_Typedef DoublePoint, uint8_t Position)
{
  /*!< LCD Write Char */
  BSP_LCD_GLASS_WriteChar(Ch, Point, DoublePoint, Position);

  /* Update the LCD display */
  LCD_UpdateDisplayRequest(LCDHandle.Instance);
}

/**
  * @brief  This function writes a char in the LCD RAM.
  * @param  ptr: Pointer to string to display on the LCD Glass.
  * @retval None
  */
void BSP_LCD_GLASS_DisplayString(uint8_t* ptr)
{
  uint8_t position = 0x01;

#if 0
  /*!< Send the string character by character on lCD */
  while ((*ptr != 0) && (position < 7))
  {
    /*!< Display one character on LCD */
    BSP_LCD_GLASS_WriteChar(ptr, 0, 0, position);
    /*!< Point on the next character */
    ptr++;
    /*!< Increment the character counter */
    position++;
  }
#else
  /*!< Send the string character by character on lCD */
  while ((*ptr != 0) && (position < 7))
  {
    if(*ptr == 0x2E)
    {
        if(position == 6)
            break;
        ptr++;
    }
    else
    {
        if(((*(ptr+1)) == 0x2E) & (position != 6))  
            BSP_LCD_GLASS_WriteChar(ptr, POINT_ON, 0, position); /*!< Display one character on LCD */
        else
            BSP_LCD_GLASS_WriteChar(ptr, 0, 0, position);
        /*!< Point on the next character */
        ptr++;
        /*!< Increment the character counter */
        position++;
    }
  }
#endif
}

/**
  * @brief This function writes a char in the LCD RAM.
  * @param ptr: Pointer to string to display on the LCD Glass.
  * @retval None
  * @note Required preconditions: Char is ASCCI value ordered with decimal point
  */
void BSP_LCD_GLASS_DisplayStrDeci(uint8_t* ptr)
{

}

/**
  * @brief  This function Clear the whole LCD RAM.
  * @retval None
  */
void BSP_LCD_GLASS_Clear(void)
{
  LCD_RamClear(LCDHandle.Instance);
}

/**
  * @}
  */

/** @addtogroup N32L43x_EVAL_LCD_Private_Functions
  * @{
  */

/**
  * @brief  LCD MSP Init.
  * @param  hlcd: LCD handle
  * @retval None
  */
static void LCD_MspInit(LCD_HandleType *hlcd)
{
  GPIO_InitType  gpioinitstruct = {0};
//  RCC_OscInitTypeDef oscinitstruct = {0};

  /*##-1- Enable PWR  peripheral Clock #######################################*/
//  __HAL_RCC_PWR_CLK_ENABLE();

  /*##-2- Allow Access and Reset the Backup Domaine ##########################*/
  /* Allow Access to Backup Domaine */
//  HAL_PWR_EnableBkUpAccess();

  /* Reset the Backup Domaine */
//  __HAL_RCC_BACKUPRESET_FORCE();
//  __HAL_RCC_BACKUPRESET_RELEASE();

  
  ////__HAL_RCC_LCD_FORCE_RESET();
  ////__HAL_RCC_LCD_RELEASE_RESET();
#if 0
  /*##-3- Configue LSI as RTC clock soucre ###################################*/
  oscinitstruct.OscillatorType =  RCC_OSCILLATORTYPE_LSI;//RCC_OSCILLATORTYPE_LSE;
  oscinitstruct.PLL.PLLState = RCC_PLL_NONE;
  oscinitstruct.LSIState = RCC_LSI_ON;//RCC_LSE_ON;
  if(HAL_RCC_OscConfig(&oscinitstruct) != HAL_OK)
  {
    while(1);
  }
 __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSI); //RCC_RTCCLKSOURCE_LSE
 __HAL_RCC_LCD_CLK_ENABLE();
#else  
   // ѡ��LCDʱ��ΪLSI
//  __HAL_RCC_LSI_ENABLE();
//  while (__HAL_RCC_GET_FLAG(RCC_FLAG_LSIRDY) == RESET);
//  __HAL_RCC_RTC_CONFIG(RCC_RTCCLKSOURCE_LSI);
//  ////__HAL_RCC_RTC_ENABLE(); 
//  __HAL_RCC_LCD_CLK_ENABLE();

#endif
  /*##-4- Enable LCD GPIO Clocks #############################################*/
  RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA|RCC_APB2_PERIPH_GPIOB|RCC_APB2_PERIPH_GPIOC, ENABLE);
    

  /*##-5- Configure peripheral GPIO ##########################################*/
  /* Configure Output for LCD */
  /* Port A */
  gpioinitstruct.Pin       = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10;
  gpioinitstruct.GPIO_Mode      = GPIO_Mode_AF_PP;
  gpioinitstruct.GPIO_Pull      = GPIO_No_Pull;
  gpioinitstruct.GPIO_Slew_Rate     = GPIO_Slew_Rate_High;
    gpioinitstruct.GPIO_Current   = GPIO_DC_4mA;
  gpioinitstruct.GPIO_Alternate= GPIO_AF11_LCD;
  GPIO_InitPeripheral(GPIOA, &gpioinitstruct);

  /* Configure Output for LCD */
  /* Port B */
  gpioinitstruct.Pin       = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11;
  GPIO_InitPeripheral(GPIOB, &gpioinitstruct);


  /* Configure Output for LCD */
  /* Port C*/
  gpioinitstruct.Pin       = GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3 | GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_6 | GPIO_PIN_7; //PC3 for VLCD
  GPIO_InitPeripheral(GPIOC, &gpioinitstruct);

}

/**
  * @brief  Converts an ascii char to the a LCD Digit (previous coding).
  * @param  c: a char to display.
  * @param  Point: a point to add in front of a char
  *         This parameter can be: POINT_OFF or POINT_ON
  * @param  DoublePoint: flag indicating if Double Point has to be added in front
  *         of the displayed character.
  *         This parameter can be: DOUBLEPOINT_ON or DOUBLEPOINT_OFF.
  * @retval None
  */
static void Convert(uint8_t* c, Point_Typedef Point, DoublePoint_Typedef DoublePoint)
{
  uint32_t ch = 0 , tmp = 0;
  uint8_t i = 0;

  /* The character c is a letter in upper case*/
  if ((*c < (uint8_t)ASCII_CHAR_LEFT_OPEN_BRACKET)&(*c > (uint8_t)ASCII_CHAR_AT_SYMBOL))
  {
    ch = LetterMap[*c-(uint8_t)ASCII_CHAR_A];
  }
  /* The character c is a number*/
  if ((*c < (uint8_t)ASCII_CHAR_COLON)&(*c > (uint8_t)ASCII_CHAR_FORWARD_SLASH))
  {
    ch = NumberMap[*c-(uint8_t)ASCII_CHAR_0];
  }
  /* The character c is a space character */
  if (*c == (uint8_t)ASCII_CHAR_SPACE)
  {
    ch = (uint32_t)0x00;
  }
  /* Set DP segment in the character that can be displayed if the point is on */
  if (Point == POINT_ON)
  {
    ch |= (uint32_t)0x00000002;
  }

  for (i = 0;i < COM_NUM; i++)
  {
    tmp = ch & Mask[i];
    Digit[i] = (uint8_t)(tmp >> (uint8_t)Shift[i]);
  }
}

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

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
