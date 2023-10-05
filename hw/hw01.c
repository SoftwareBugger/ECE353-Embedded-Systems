/**
 * @file hw01.c
 * @author Adam Boho (boho2@wisc.edu)
 * @author Han Lyu  (hlyu42@wisc.edu)
 * @author Dominic Valentini (dvalentini@wisc.edu)
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
    /* Initializes the screen to show the alarm time, and the clock time*/
    hw01_display_time(0, 0, HW01_LCD_TIME_COLOR);
    hw01_display_alarm(0, 0, HW01_LCD_ALARM_COLOR);
    hw01_draw_bell();
    
    /*Initialized variables to use later in the method*/
    uint8_t mode = SET_TIME;
    static int8_t sec = 0;
    static int8_t min = 0;
    static int8_t alarm_sec = 0;
    static int8_t alarm_min = 0;
    bool set_min = true;
    bool set_alarm = false;
    bool set_alarm_min = false;
    bool alarm_buzz = false;
    /*While loop that defines the interace of the program*/
    while (1)
    {
        switch (mode) {
            /*Code relating to SET_TIME*/
            case SET_TIME:
                /* If sw3 is pressed for more than 2 seconds, change the mode, 
                and clear the alert status.*/
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    SW3 = HW01_ALERT_NONE;
                    mode = RUN;
                    continue;
                }
                /* If sw3 is pressed for less than 2 seconds, the incrementor is 
                toggled between seconds and minutes, and the alert status is cleared.*/
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (set_min) set_min = false;
                    else set_min = true;
                    SW3 = HW01_ALERT_NONE;
                }
                //TODO
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
                /* If we are in set_min, and press SW2, we decrement the minutes, 
                and clear the alerts*/
    
                if (set_min && (SW2 != HW01_ALERT_NONE)) {
                    if (min >= 1) min = (min - 1)%3;
                    else min = (min + 2)%3;
                    SW2 = HW01_ALERT_NONE;
                }
                /* If we are in set_min mode and SW1 is  pressed, 
                increment the minutes and clear alerts. Note that minutes are rolled
                back to zero, if you incrememnt past two. */
                if (set_min && (SW1 != HW01_ALERT_NONE)) {
                    min = (min + 1)%3;
                    SW1 = HW01_ALERT_NONE;
                }
                /* If we are  NOT in set_min we are in "set seconds" and press SW2, we decrement the 
                seconds, and clear the alerts*/
                if ((!set_min) && (SW2 != HW01_ALERT_NONE)) {
                    if (sec >= 1) sec = (sec - 1)%60;
                    else sec = (sec + 59)%60;
                    SW2 = HW01_ALERT_NONE;
                }
                /* If we are  NOT in set_min we are in "set seconds" and press SW1, we increment the 
                seconds, and clear the alerts*/
                if ((!set_min) && (SW1 != HW01_ALERT_NONE)) {
                    sec = (sec + 1)%60;
                    SW1 = HW01_ALERT_NONE;
                }
                break;
            /* Code relating to RUN*/
            case RUN:
                /* If sw3 is hit for more than 2 seconds, the mode is changed to set_alarm
                and the alerts are cleared.*/
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    SW3 = HW01_ALERT_NONE;
                    mode = SET_ALARM;
                    continue;
                }
                /* If sw3 is hit for less than 2 seconds, it toggles the alarm (en/disable)*/
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (set_alarm) set_alarm = false;
                    else set_alarm = true;
                    SW3 = HW01_ALERT_NONE;
                }
                /* If INC has an equivalent value to HW01_ALERT_TIME_UPDATE, then the time is updates,
                specifically by incrementing the seconds, adding a minute, if we count a full 60 seconds.*/
                if (INC == HW01_ALERT_TIME_UPDATE) {
                    sec = (sec + 1)%60;
                    if (sec == 0) min = (min + 1)%3;
                    INC = HW01_ALERT_NONE;
                }
                /* If the values of the alarm and the clock are the same, then buzz the alarm.*/
                if (sec == alarm_sec && min == alarm_min && set_alarm) {
                    pwm_buzzer_start();
                    alarm_buzz = true;
                }
                /* If sw1 is hit for more than 2 seconds while the alarm is buzzing, the alarm stops.*/
                if (SW1 == HW01_ALERT_BUTTON_GT_2S && set_alarm && alarm_buzz){
                    pwm_buzzer_stop();
                    alarm_buzz = false;
                }

                if (alarm_buzz)
                {
                    hw01_display_time(min, sec, LCD_COLOR_RED);
                }
                else
                {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                }               
                /* This segment displays the time and alarm */
                hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                /* If the alarm is set, then display the bell.*/
                if (set_alarm) hw01_draw_bell();
                else hw01_erase_bell();
                break;
            /* Code related to SET_ALARM*/
            case SET_ALARM:
                /* If sw3 is held for longer than two seconds, we move to RUN mode, 
                and the alert is cleared*/
                if (SW3 == HW01_ALERT_BUTTON_GT_2S) {
                    SW3 = HW01_ALERT_NONE;
                    mode = RUN;
                    continue;
                }
                /* If sw3 is held for less than two seconds, the interface toggles between 
                incrementing seconds and minutes*/
                else if (SW3 == HW01_ALERT_BUTTON_LT_2S) {
                    if (!set_alarm_min) set_alarm_min = true;
                    else set_alarm_min = false;
                    SW3 = HW01_ALERT_NONE;
                }
                /* If INC has a equivalent value to HW01_ALERT_TIME_UPDATE, 
                then the time is incremented, rolling over if need be.*/
                if (INC == HW01_ALERT_TIME_UPDATE) {
                    sec = (sec + 1)%60;
                    if (sec == 0) min = (min + 1)%3;
                    INC = HW01_ALERT_NONE;
                }
                /* if BLK has the same value as HW01_ALERT_BLINK, then the 
                alarm is set to black.*/
                if (BLK == HW01_ALERT_BLINK) {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                    hw01_display_alarm(alarm_min, alarm_sec, LCD_COLOR_BLACK);
                    if (set_alarm) hw01_draw_bell();
                    else hw01_erase_bell();
                }
                /* in this statement if BLK != HW01_ALERT_BLINK then we change the 
                color of the alarm and time back to normal.*/
                else {
                    hw01_display_time(min, sec, HW01_LCD_TIME_COLOR);
                    hw01_display_alarm(alarm_min, alarm_sec, HW01_LCD_ALARM_COLOR);
                    if (set_alarm) hw01_draw_bell();
                    else hw01_erase_bell();
                }
                /* This if statement controls the incrementing of the alarm minutes, 
                then clearing the alerts */
                if (set_alarm_min && (SW2 != HW01_ALERT_NONE)) {
                    if (alarm_min >= 1) alarm_min = (alarm_min - 1)%3;
                    else alarm_min = (alarm_min + 2)%3;
                    SW2 = HW01_ALERT_NONE;
                }
                /* This if statement controls the decrementing of the alarm minutes, 
                then clearing the alerts */
                if (set_alarm_min && (SW1 != HW01_ALERT_NONE)) {
                    alarm_min = (alarm_min + 1)%3;
                    SW1 = HW01_ALERT_NONE;
                }
                 /* This if statement controls the incrementing of the alarm seconds, 
                 then clearing the alerts */
                if ((!set_alarm_min) && (SW2 != HW01_ALERT_NONE)) {
                    if (alarm_sec >= 1) alarm_sec = (alarm_sec - 1)%60;
                    else alarm_sec = (alarm_sec + 59)%60;
                    SW2 = HW01_ALERT_NONE;
                }
                 /* This if statement controls the decrementing of the alarm seconds, 
                then clearing the alerts */
                if ((!set_alarm_min) && (SW1 != HW01_ALERT_NONE)) {
                    alarm_sec = (alarm_sec + 1)%60;
                    SW1 = HW01_ALERT_NONE;
                }
                break; 
        }
    }
}
