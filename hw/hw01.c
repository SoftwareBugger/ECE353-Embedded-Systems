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
volatile hw01_timer_alerts_t SW1 = HW01_ALERT_NONE;
volatile hw01_timer_alerts_t SW2 = HW01_ALERT_NONE;
volatile hw01_timer_alerts_t SW3 = HW01_ALERT_NONE;
volatile hw01_timer_alerts_t INC = HW01_ALERT_NONE;
volatile hw01_timer_alerts_t DEC = HW01_ALERT_NONE;
volatile hw01_timer_alerts_t BLK = HW01_ALERT_NONE;
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

    hw01_display_time(0, 0, HW01_LCD_TIME_COLOR);
    hw01_display_alarm(0, 0, HW01_LCD_ALARM_COLOR);
    hw01_draw_bell();
    
    uint8_t mode = SET_TIME;
    static int8_t sec = 0;
    static int8_t min = 0;
    static int8_t alarm_sec = 0;
    static int8_t alarm_min = 0;
    bool set_min = false;
    bool set_alarm = false;
    bool set_alarm_min = false;
    while (1)
    {
        switch (mode) {
            case SET_TIME:
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    mode = RUN;
                    SW3 = HW01_ALERT_NONE;
                    continue;
                }
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (set_min) set_min = false;
                    else set_min = true;
                    SW3 = HW01_ALERT_NONE;
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
                break;
            case RUN:
                printf("here\n");
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    mode = SET_ALARM;
                    SW3 = HW01_ALERT_NONE;
                    continue;
                }
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (set_alarm) set_alarm = false;
                    else set_alarm = true;
                    SW3 = HW01_ALERT_NONE;
                }
                if (INC == HW01_ALERT_TIME_UPDATE) {
                    sec = (sec + 1)%60;
                    if (sec == 0) min = (min + 1)%3;
                    INC = HW01_ALERT_NONE;
                }
                if (sec == alarm_sec && min == alarm_min && set_alarm) {
                    pwm_buzzer_start(void);
                }
                hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                if (set_alarm) hw01_draw_bell();
                else hw01_erase_bell();
                break;
            case SET_ALARM:
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    mode = SET_ALARM;
                    SW3 = HW01_ALERT_NONE;
                    continue;
                }
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (set_alarm_min) set_alarm_min = false;
                    else set_alarm_min = true;
                    SW3 = HW01_ALERT_NONE;
                }
                if (INC == HW01_ALERT_TIME_UPDATE) {
                    sec = (sec + 1)%60;
                    if (sec == 0) min = (min + 1)%3;
                    INC = HW01_ALERT_NONE;
                }
                if (BLK == HW01_ALERT_BLINK) {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                    hw01_display_alarm(alarm_min, alarm_sec, LCD_COLOR_BLACK);
                    if (set_alarm) hw01_draw_bell();
                    else hw01_erase_bell();
                }
                else {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                    hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                    if (set_alarm) hw01_draw_bell();
                    else hw01_erase_bell();
                }
                if (set_alarm_min && (SW2 != HW01_ALERT_NONE)) {
                    if (alarm_min >= 1) alarm_min = (alarm_min - 1)%3;
                    else alarm_min = (alarm_min + 2)%3;
                    SW2 = HW01_ALERT_NONE;
                }
                if (set_alarm_min && (SW1 != HW01_ALERT_NONE)) {
                    alarm_min = (alarm_min + 1)%3;
                    SW1 = HW01_ALERT_NONE;
                }
                if ((!set_alarm_min) && (SW2 != HW01_ALERT_NONE)) {
                    if (alarm_sec >= 1) alarm_sec = (alarm_sec - 1)%60;
                    else alarm_sec = (alarm_sec + 59)%60;
                    SW2 = HW01_ALERT_NONE;
                }
                if ((!set_alarm_min) && (SW1 != HW01_ALERT_NONE)) {
                    alarm_sec = (alarm_sec + 1)%60;
                    SW1 = HW01_ALERT_NONE;
                }
                break;
        }
    }
}