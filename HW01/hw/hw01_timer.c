/**
 * @file hw01_timer.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "hw01_timer.h"
/*****************************************************************************/
/*  Function Declaration                                                     */
/*****************************************************************************/
void Handler_HW01_Timer(void *handler_arg, cyhal_timer_event_t event);

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/

/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_HW01_Timer(void *handler_arg, cyhal_timer_event_t event)
{
    CY_UNUSED_PARAMETER(handler_arg);
    CY_UNUSED_PARAMETER(event);
}

/*****************************************************************************/
/*  TCPWM Initialization Function                                            */
/*****************************************************************************/
void hw01_timer_init(uint32_t ticks)
{

}
