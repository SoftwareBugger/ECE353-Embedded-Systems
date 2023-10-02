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
uint8_t mode = SET_TIME;
int8_t sec = 0;
int8_t min = 0;
int8_t alarm_sec = 0;
int8_t alarm_min = 0;
bool set_min = false;
extern hw01_timer_alerts_t SW1;
extern hw01_timer_alerts_t SW2;
extern hw01_timer_alerts_t SW3;
extern hw01_timer_alerts_t INC;
extern hw01_timer_alerts_t DEC;
extern hw01_timer_alerts_t BLK;
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
    hw01_timer_init(10000000); /* MODIFY with correct Ticks Count for 100mS*/
}



/**
 * @brief
 * Implements the main application for HW01
 */
void hw01_main_app(void)
{
    sec = 0;
    min = 0;
    set_min = false;

    hw01_display_time(0, 0, HW01_LCD_TIME_COLOR);
    hw01_display_alarm(0, 0, HW01_LCD_ALARM_COLOR);
    hw01_draw_bell();

    while (1)
    {
        uint8_t run_sec;
        uint8_t run_min;
        switch (mode) {
            case SET_TIME:
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    mode = RUN;
                    continue;
                }
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    set_min = !set_min;
                }
                if (BLK == HW01_ALERT_BLINK) {
                    hw01_display_time(min, sec, LCD_COLOR_BLACK);
                    hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                    hw01_erase_bell();
                }
                else {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                    hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                    hw01_erase_bell();
                }
                if (set_min && (SW2 != HW01_ALERT_NONE)) {
                    if (min >= 1) min = (min - 1)%3;
                    else min = (min + 2)%3;
                    SW2 = HW01_ALERT_NONE;
                }
                if (set_min && (SW1 != HW01_ALERT_NONE)) {
                    min = (min + 1)%3;
                    SW1 = HW01_ALERT_NONE;
                }
                if ((!set_min) && (SW2 != HW01_ALERT_NONE)) {
                    if (sec >= 1) sec = (sec - 1)%60;
                    else sec = (sec + 59)%60;
                    SW2 = HW01_ALERT_NONE;
                }
                if ((!set_min) && (SW1 != HW01_ALERT_NONE)) {
                    sec = (sec + 1)%60;
                    SW1 = HW01_ALERT_NONE;
                }
                printf("%i : %i\n", min, sec);
                break;
            case RUN:
                run_sec = sec;
                run_min = min;
                if (INC == HW01_ALERT_TIME_UPDATE) {
                    run_sec = (run_sec + 1)%60;
                    if (run_sec == 0) run_min = (run_min + 1)%3;
                    INC = HW01_ALERT_NONE;
                }
                hw01_display_time(run_min, run_sec, HW01_LCD_TIME_COLOR);
                hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                hw01_draw_bell();
                break;
            case SET_ALARM:
                break;
        }
    }
}