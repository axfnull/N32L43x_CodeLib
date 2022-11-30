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
 * @file main.c
 * @author Nations 
 * @version v1.2.0
 *
 * @copyright Copyright (c) 2022, Nations Technologies Inc. All rights reserved.
 */
#include "main.h"
#include <stdio.h>
#include <stdint.h>
#include "n32l43x_lprcnt.h"
#include "delay.h"



void LPRCNT_INT_Config(void);
void LprcntSensorChannelParagram(void);
void LprcntIoInit(void);


/**
 * @brief  Main program.
 */




int main(void)
{
    
    /*SystemInit() function has been called by startup file startup_n32l43x.s*/

    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_PWR, ENABLE);
    RCC_EnableLsi(ENABLE); // 
    while(RCC_GetFlagStatus(RCC_CTRLSTS_FLAG_LSIRD) == RESET); //waite LSI stable
    //Enable PRCNT clock
    RCC_EnableRETPeriphClk(RCC_RET_PERIPH_LPRCNT,ENABLE);
    RCC_ConfigLSXClk(RCC_LSXCLK_SRC_LSI);
    /*  Enable the DBG_STOP to keep debug in low power  */
    LprcntIoInit();
    LprcntSensorChannelParagram();  
    LPRCNTModeEnable(START);

    while (1)
    {

    }
}
/**
 * @brief  LprcntCampIoInit.
 * @param NONE
 */
void LprcntIoInit(void)
{
    GPIO_InitType GPIO_InitStructure;
    LPRCNT_COMP_InitType COMP_Initial;
    GPIO_InitStruct(&GPIO_InitStructure);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP,ENABLE);
    RCC_EnableAPB1PeriphClk(RCC_APB1_PERIPH_COMP_FILT, ENABLE);
    //Comp position IO Init(PA0,PA1,PA2)
    RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_GPIOA, ENABLE);    
    GPIO_InitStructure.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_3 ; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Analog;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);

#if 1//COMP1_DEBUG_OUT
    //COMP outputIO PA11
    //RCC_EnableAPB2PeriphClk( RCC_APB2_PERIPH_GPIOA, ENABLE);  
    GPIO_InitStructure.Pin = GPIO_PIN_11  ; 
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Alternate = GPIO_AF7_COMP1;
    GPIO_InitPeripheral(GPIOA, &GPIO_InitStructure);
#endif
    
    COMP_Initial.InmSel            = INMSEL_VREF_VC1;
    COMP_Initial.Hyst              = HYST_HIGH;
    COMP_Initial.LowPoweMode       = ENABLE;
    LPRCNT_CompInit(&COMP_Initial);
    COMP_Enable(COMP1,ENABLE);

}


/**
 * @brief  LprcntInit.
 * @param sensor channel paragram setting.
 * @param time paragram setting.
 * @param work mode select.
 */
void LprcntSensorChannelParagram(void)
{
    LPRCNT_InitType param;
    //clock and charge voltage
    param.PrescaleDiv = LPRCNT_PRESCALER_DIV4;
    param.ChargeVol = POWERSELECT1V65;
    param.AutoDetEn = DISABLE;
    param.AutoWaitPer = AUTODETPERIOD4;
      
    //Scan preriod
    param.NormalFreq.low_speed    = NORMAL_LOW_PER;
    param.NormalFreq.hight_speed  = NORMAL_HIGH_PER;
    param.NormalFreq.swtich_time  = NORMAL_SW_TIM;
    param.AlarmFreq = FRETIME4;
    //Channel_0 time
    param.ChTime[0].vibrationtime = CHANAL0_TIME_VIBRATION;
    param.ChTime[0].dischargetime = CHANAL0_TIME_DISCHARGE;
    param.ChTime[0].chargetime = CHANAL0_TIME_CHARGE;
    //Channel_1 time
    param.ChTime[1].vibrationtime = CHANAL1_TIME_VIBRATION;
    param.ChTime[1].dischargetime = CHANAL1_TIME_DISCHARGE;
    param.ChTime[1].chargetime = CHANAL1_TIME_CHARGE;   
    //Channel_2 time
    param.ChTime[2].vibrationtime = CHANAL2_TIME_VIBRATION;
    param.ChTime[2].dischargetime = CHANAL2_TIME_DISCHARGE;
    param.ChTime[2].chargetime = CHANAL2_TIME_CHARGE;
    //Channel_0 threshold
    param.ChTH[0].dacreference = CHANAL0_THRESHOLD_DACREF;
    param.ChTH[0].undampedTh = CHANAL0_THRESHOLD_UNDAMPED;
    param.ChTH[0].dampedTh = CHANAL0_THRESHOLD_DAMPED;
    //Channel_1 threshold
    param.ChTH[1].dacreference = CHANAL1_THRESHOLD_DACREF;
    param.ChTH[1].undampedTh = CHANAL1_THRESHOLD_UNDAMPED;
    param.ChTH[1].dampedTh = CHANAL1_THRESHOLD_DAMPED;
    //Channel_2 threshold
    param.ChTH[2].dacreference = CHANAL2_THRESHOLD_DACREF;
    param.ChTH[2].undampedTh = CHANAL2_THRESHOLD_UNDAMPED;
    param.ChTH[2].dampedTh = CHANAL2_THRESHOLD_DAMPED;
    //set work mode and circle
    param.WorkMode = CAL_MODE;
    param.Circle   = REPORT_CIRCLE;
    //Interruput config
    LPRCNT_INT_Config(); 
    param.Int       = REPORT_INT;
    param.Int       = ENABLE;        
    LPRCNTInit(&param);
}


/**
 * @brief  Inserts a delay time.
 * @param count specifies the delay time length.
 */
void Delay(uint32_t count)
{
    for (; count > 0; count--)
        ;
}
/**
 * @brief  Configures LED GPIO.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedInit(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIO_InitType GPIO_InitStructure;

    /* Check the parameters */
    assert_param(IS_GPIO_ALL_PERIPH(GPIOx));
    GPIO_InitStruct(&GPIO_InitStructure);
    /* Enable the GPIO Clock */
    if (GPIOx == GPIOA)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOA, ENABLE);
    }
    else if (GPIOx == GPIOB)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOB, ENABLE);
    }
    else if (GPIOx == GPIOC)
    {
        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOC, ENABLE);
    }
    else
    {
        if (GPIOx == GPIOD)
        {
            RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_GPIOD, ENABLE);
        }
    }
    GPIO_InitStruct(&GPIO_InitStructure);
    GPIO_InitStructure.Pin        = Pin;
    GPIO_InitStructure.GPIO_Current = GPIO_DC_4mA;
    GPIO_InitStructure.GPIO_Pull    = GPIO_No_Pull;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_Out_PP;
    GPIO_InitPeripheral(GPIOx, &GPIO_InitStructure);
}
/**
 * @brief  Turns selected Led on.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOn(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Turns selected Led Off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedOff(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->PBC = Pin;
}
/**
 * @brief  Turns selected Led on or off.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be one of the following values:
 *  @arg GPIO_PIN_0~GPIO_PIN_15: set related pin on
 *      @arg (GPIO_PIN_0<<16)~(GPIO_PIN_15<<16): clear related pin off
 */
void LedOnOff(GPIO_Module* GPIOx, uint32_t Pin)
{
    GPIOx->PBSC = Pin;
}
/**
 * @brief  Toggles the selected Led.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LedBlink(GPIO_Module* GPIOx, uint16_t Pin)
{
    GPIOx->POD ^= Pin;
}

/**
 * @brief  LPRCNT_INT_Config.
 * @param GPIOx x can be A to G to select the GPIO port.
 * @param Pin This parameter can be GPIO_PIN_0~GPIO_PIN_15.
 */
void LPRCNT_INT_Config(void)
{
    NVIC_InitType NVIC_InitStructure;
    EXTI_InitType EXTI_InitStruct;
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_3);

    // Configure interruput line
    NVIC_InitStructure.NVIC_IRQChannel = COMP_1_2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);
    
    EXTI_InitStruct.EXTI_Line = EXTI_LINE21;
    EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStruct.EXTI_Trigger = EXTI_Trigger_Rising_Falling;
    EXTI_InitStruct.EXTI_LineCmd = ENABLE;
    EXTI_InitPeripheral(&EXTI_InitStruct);
}
/**
 * @}
 */
