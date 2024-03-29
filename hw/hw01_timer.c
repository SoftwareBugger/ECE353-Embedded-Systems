/**
 * @file hw01_timer.c
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
#include "hw01_timer.h"
/*****************************************************************************/
/*  Function Declaration                                                     */
/*****************************************************************************/
void Handler_HW01_Timer(void *handler_arg, cyhal_timer_event_t event);

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
extern volatile hw01_timer_alerts_t SW1;
extern volatile hw01_timer_alerts_t SW2;
extern volatile hw01_timer_alerts_t SW3;
extern volatile hw01_timer_alerts_t INC;
extern volatile hw01_timer_alerts_t DEC;
extern volatile hw01_timer_alerts_t BLK;

/* Timer object and timer_cfg object */
cyhal_timer_t timer_obj;

cyhal_timer_cfg_t timer_cfg =
    {
        .compare_value = 0,              /* Timer compare value, not used */
        .period = 0,                     /* number of timer ticks */
        .direction = CYHAL_TIMER_DIR_UP, /* Timer counts up */
        .is_compare = false,             /* Don't use compare mode */
        .is_continuous = true,           /* Run timer indefinitely */
        .value = 0                       /* Initial value of counter */
};

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
    /* variables to keep track of time length through each Handler Call */
    static uint8_t ISRcount_SW1 = 0; 
    static uint8_t ISRcount_SW2 = 0;
    static uint8_t ISRcount_SW3 = 0;
    static uint8_t ISRcount_BLK = 0;
    static uint8_t ISRcount_SEC = 0;
    uint32_t reg_val = PORT_BUTTONS->IN; // read value of push buttons
    ISRcount_SEC = (ISRcount_SEC + 1) % 10;
    ISRcount_BLK = (ISRcount_BLK + 1) % 10;
    if (ISRcount_BLK <= 4) { // blinks the clock at 2 hZ rate
        BLK = HW01_ALERT_BLINK;
    }
    else BLK = HW01_ALERT_NONE;

    if (ISRcount_SEC == 0) { // updates current time at 1 hZ rate
        INC = HW01_ALERT_TIME_UPDATE;
    }
    else INC = HW01_ALERT_NONE;

    if ((reg_val & SW1_MASK) == 0) { //SW1 pushed
        ISRcount_SW1++; // inc count
        if (ISRcount_SW1 >= 20) { // if count is >= 20 it is considered a long push
            SW1 = HW01_ALERT_BUTTON_GT_2S;
            ISRcount_SW1 = 0;
        }
    }
    else { // set other alarm flags based on count, short if 20>count>0, none if count is 0
        if (ISRcount_SW1 < 20 && ISRcount_SW1 > 0) SW1 = HW01_ALERT_BUTTON_LT_2S;
        else if (ISRcount_SW1 >= 20) SW1 = HW01_ALERT_BUTTON_GT_2S;
        else if (ISRcount_SW1 == 0) SW1 = HW01_ALERT_NONE;
        ISRcount_SW1 = 0;
    }

    if ((reg_val & SW2_MASK) == 0) { // SW2 pushed, rest of if and else block is same as SW1
        ISRcount_SW2++;
        if (ISRcount_SW2 >= 20) { 
            SW2 = HW01_ALERT_BUTTON_GT_2S;
            ISRcount_SW2 = 0;
        }
    }
    else {
        if (ISRcount_SW2 < 20 && ISRcount_SW2 > 0) SW2 = HW01_ALERT_BUTTON_LT_2S;
        else if (ISRcount_SW2 >= 20) SW2 = HW01_ALERT_BUTTON_GT_2S;
        else if (ISRcount_SW2 == 0) SW2 = HW01_ALERT_NONE;
        ISRcount_SW2 = 0;
    }

    if ((reg_val & SW3_MASK) == 0) { // SW3 pushed, rest of if and else block is same as SW1/2
        ISRcount_SW3++;
        if (ISRcount_SW3 >= 20) {
            SW3 = HW01_ALERT_BUTTON_GT_2S;
            ISRcount_SW3 = 0;
        }
    }
    else {
        if (ISRcount_SW3 < 20 && ISRcount_SW3 > 0) SW3 = HW01_ALERT_BUTTON_LT_2S;
        else if (ISRcount_SW3 >= 20) SW3 = HW01_ALERT_BUTTON_GT_2S;
        else if (ISRcount_SW3 == 0) SW3 = HW01_ALERT_NONE;
        ISRcount_SW3 = 0;
    }

}

/*****************************************************************************/
/*  TCPWM Initialization Function                                            */
/*****************************************************************************/
void hw01_timer_init(uint32_t ticks)
{
    cy_rslt_t rslt;
    timer_cfg.period = ticks;
        /* Initialize a timer */
    rslt = cyhal_timer_init(&timer_obj, NC, NULL);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Apply timer configuration such as period, count direction, run mode, etc. */
    rslt = cyhal_timer_configure(&timer_obj, &timer_cfg); 
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Set the frequency of timer*/
    rslt = cyhal_timer_set_frequency(&timer_obj,100000000); 
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Assign the ISR to execute on timer interrupt */
    cyhal_timer_register_callback(&timer_obj,Handler_HW01_Timer,NULL);

    /* Set the event on which timer interrupt occurs and enable it */
    cyhal_timer_enable_event(&timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT,3, true);

    /* Start the timer with the configured settings */
    rslt = cyhal_timer_start(&timer_obj);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

}