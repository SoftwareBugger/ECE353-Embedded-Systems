/**
 * @file io-sw.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-07
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "io-sw.h"

/*****************************************************************************/
/* ICE 02 START */
/*****************************************************************************/
void push_buttons_init(void)
{
    cy_rslt_t rslt;
    rslt = cyhal_gpio_init(PIN_SW1, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    rslt = cyhal_gpio_init(PIN_SW2, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    rslt = cyhal_gpio_init(PIN_SW3, CYHAL_GPIO_DIR_INPUT, CYHAL_GPIO_DRIVE_NONE, 0);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);
} 
/*****************************************************************************/
/* ICE 02 END */
/*****************************************************************************/


/*****************************************************************************/
/* ICE 03 START */
/*****************************************************************************/
/**
 * @brief
 * Returns which button has been pressed and then released. 
 *  
 * This function should examine the current state of each button and
 * compare it with the previous state of the button.  If the current
 * state is not-pressed and the previous state was pressed, return that
 * the button has been released.
 * 
 * If none of the buttons have been released, check to see if the button is 
 * currently being pressed.  If it is, return that the button is being pressed
 * 
 * If multiple buttons are pressed/released, return the button state of the button
 * with the highest SW number (SW3 has highest priority, then SW2, then SW1)
 * 
 * This function should only read the IN register once.
 * 
 * @return button_state_t 
 * Returns which of the buttons is currently being pressed.  
 */
button_state_t get_buttons(void)
{
    button_state_t sw = BUTTON_INACTIVE;
    uint32_t readInput = PORT_BUTTONS->IN;

    static bool sw_prev3 = false;
    static bool sw_curr3 = false;
    static bool sw_prev2 = false;
    static bool sw_curr2 = false;
    static bool sw_prev1 = false;
    static bool sw_curr1 = false;

    if ((readInput & SW1_MASK) == 0) 
    {
        sw_curr1 = true;
    }
    else
    {
        sw_curr1 = false;
    }
    
    if (sw_prev1 == false && sw_curr1 == true) sw = BUTTON_SW1_PRESSED;
    else if (sw_curr1 == false && sw_prev1 == true) sw = BUTTON_SW1_RELEASED;

    if ((readInput & SW2_MASK) == 0) 
    {
        sw_curr2 = true;
    }
    else
    {
        sw_curr2 = false;
    }
    
    if (sw_prev2 == false && sw_curr2 == true) sw = BUTTON_SW2_PRESSED;
    else if (sw_curr2 == false && sw_prev2 == true) sw = BUTTON_SW2_RELEASED;

    if ((readInput & SW3_MASK) == 0) 
    {
        sw_curr3 = true;
    }
    else
    {
        sw_curr3 = false;
    }

    if (sw_prev3 == false && sw_curr3 == true) sw = BUTTON_SW3_PRESSED;
    else if (sw_curr3 == false && sw_prev3 == true) sw = BUTTON_SW3_RELEASED;

    sw_prev3 = sw_curr3;
    sw_prev2 = sw_curr2;
    sw_prev1 = sw_curr1;
    
    return sw;
}

/*****************************************************************************/
/* ICE 03 END */
/*****************************************************************************/