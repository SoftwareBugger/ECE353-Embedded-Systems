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

static bool sw1_cur = false;
static bool sw1_prev;
static bool sw2_cur = false;
static bool sw2_prev;
static bool sw3_cur = false;
static bool sw3_prev;
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

    uint32_t reg_value = PORT_BUTTONS->IN;

    if ((reg_value & SW3_MASK) == 0)
    {
        sw3_cur = true;
    }
    else
    {
        sw3_cur = false;
    }

    if ((reg_value & SW2_MASK) == 0)
    {
        sw2_cur = true;
    }
    else
    {
        sw2_cur = false;
    }

    if ((reg_value & SW1_MASK) == 0)
    {
        sw1_cur = true;
    }
    else
    {
        
        sw1_cur = false;
    }

    if (sw3_cur)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return  BUTTON_SW3_PRESSED;
    }

    if (!sw3_cur && sw3_prev)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return BUTTON_SW3_RELEASED;
    }

    if (sw2_cur)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return  BUTTON_SW2_PRESSED;
    }

    if (!sw2_cur && sw2_prev)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return BUTTON_SW2_RELEASED;
    }

    if (sw1_cur)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return  BUTTON_SW1_PRESSED;
    }

    if (!sw1_cur && sw1_prev)
    {
    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;
        return BUTTON_SW1_RELEASED;
    }

    sw3_prev = sw3_cur;
    sw2_prev = sw2_cur;
    sw1_prev = sw1_cur;

    return BUTTON_INACTIVE;
}

/*****************************************************************************/
/* ICE 03 END */
/*****************************************************************************/