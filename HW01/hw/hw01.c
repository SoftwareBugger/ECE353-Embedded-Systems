/**
 * @file hw01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "hw01.h"
#include "main.h"

/*****************************************************************************/
/*  Function Declaration                                                     */
/*****************************************************************************/

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/

/**
 * @brief
 * Initializes the PSoC6 Peripherals used for HW01
 */
void hw01_peripheral_init(void)
{
    /* Initialize the pushbuttons */
    push_buttons_init();

    /* Initalize the LEDs */
    leds_init();

    /* Initialize the LCD */
    ece353_enable_lcd();

    /* Initialize the buzzer */
    pwm_buzzer_init();

    /* Intitialize a timer to generate an interrupt every 100mS*/
    hw01_timer_init(0); /* MODIFY with correct Ticks Count for 100mS*/
}



/**
 * @brief
 * Implements the main application for HW01
 */
void hw01_main_app(void)
{

    hw01_display_time(0, 0, HW01_LCD_TIME_COLOR);
    hw01_display_alarm(0, 0, HW01_LCD_ALARM_COLOR);
    hw01_draw_bell();

    while (1)
    {
    }
}