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
    static bool state1_p;
    static bool state2_p;
    static bool state3_p;

    uint32_t reg_val = GPIO_PRT6->IN ;
    if (((reg_val & SW1_MASK)==0)) {
        state1_p = true;
    }
    if (((reg_val & SW2_MASK)==0)) {
        state2_p = true;
    }
    if (((reg_val & SW3_MASK)==0)) {
        state3_p = true;
    }
    if (state3_p) {
        return BUTTON_SW3_PRESSED;
    }
    else if (state2_p) {
        return BUTTON_SW2_PRESSED;
    }
    else if (state1_p) {
        return BUTTON_SW1_PRESSED;
    }

    if (((reg_val & ~SW1_MASK)==1)) {
        state1_p = false;
    }
    if (((reg_val & ~SW2_MASK)==1)) {
        state2_p = false;
    }
    if (((reg_val & ~SW3_MASK)==1)) {
        state3_p = false;
    }
    if (state3_p) {
        return BUTTON_SW3_RELEASED;
    }
    else if (state2_p) {
        return BUTTON_SW2_RELEASED;
    }
    else if (state3_p) {
        return BUTTON_SW3_RELEASED;
    }



    
    
}

/*****************************************************************************/
/* ICE 03 END */
/*****************************************************************************/