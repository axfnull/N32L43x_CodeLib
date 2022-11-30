#include <stdio.h>
#include <stdint.h>
#include "n32l43x.h"
#include "User_Systick_Config.h"

/**
 * @brief  Configure the system tick clock.
 */
uint32_t DBG_SysTick_Config(uint32_t ticks)
{
    if (ticks > SysTick_LOAD_RELOAD_Msk)
        return (1); /* Reload value impossible */

    SysTick->LOAD = (ticks & SysTick_LOAD_RELOAD_Msk) - 1;       /* set reload register */
    NVIC_SetPriority(SysTick_IRQn, (1 << __NVIC_PRIO_BITS) - 1); /* set Priority for Cortex-M0 System Interrupts */
    SysTick->VAL  = 0;                                           /* Load the SysTick Counter Value */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk; /* Enable SysTick IRQ and SysTick Timer */
    SysTick->CTRL &= ~SysTick_CTRL_TICKINT_Msk;
    return (0); /* Function successful */
}

/**
 * @brief  Use the system tick clock to delay.
 */
void SysTick_Delay_Ms(__IO uint32_t ms)
{
    uint32_t i;
    RCC_ClocksType RCC_Clocks;
    RCC_GetClocksFreqValue(&RCC_Clocks);
    DBG_SysTick_Config(RCC_Clocks.SysclkFreq / 1000);

    for (i = 0; i < ms; i++)
    {
        /* When the value of the counter is reduced to 0, the bit 16 of the CRTL register is set to 1.
           When set to 1, the bit  will cleared to 0 with read
        */
        while (!((SysTick->CTRL) & (1 << 16)))
            ;
    }
    // Disable SysTick timer
    SysTick->CTRL &= ~SysTick_CTRL_ENABLE_Msk;
}
