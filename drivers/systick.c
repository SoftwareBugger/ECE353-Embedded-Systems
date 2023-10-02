/**
 * @file systick.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "systick.h"

/**
 * @brief 
 *  Initilaizes the SysTick Timer for a configurable interval of time. 
 * @param ticks 
 *  The Number clock cycles 
 */
void systick_init(uint32_t ticks)
{
    if (ticks > 0xFFFFFF) 
    {
        // only allowing less than 24 bits for counting
        return false;
    }
    // Turn off Systick timer
    SysTick->CTRL = 0;
    // Set current value to 0
    SysTick->VAL = 0;
    // Set the period
    SysTick->LOAD = ticks - 1;
    // Set the clock source to the main cpu and turn on the timer
    SysTick->CTRL = SYSTICK_CTRL_CLKSOURCE | SYSTICK_CTRL_ENABLE;
    return true;
}


bool systick_expired(void)
{
    // If none zero at 16 bit, the timer has done counting
    if (SysTick->CTRL & SYSTICK_CTRL_COUNTFLAG) 
    {
        return true;
    }
    else 
    {
        return false;
    }
}