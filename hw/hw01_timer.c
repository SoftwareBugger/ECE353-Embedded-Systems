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
hw01_timer_alerts_t SW1 = HW01_ALERT_NONE;
hw01_timer_alerts_t SW2 = HW01_ALERT_NONE;
hw01_timer_alerts_t SW3 = HW01_ALERT_NONE;
hw01_timer_alerts_t INC = HW01_ALERT_NONE;
hw01_timer_alerts_t DEC = HW01_ALERT_NONE;
hw01_timer_alerts_t BLK = HW01_ALERT_NONE;

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
    static uint8_t ISRcount_SW1 = 0;
    static uint8_t ISRcount_SW2 = 0;
    static uint8_t ISRcount_SW3 = 0;
    static uint8_t ISRcount_BLK = 0;
    static uint8_t ISRcount_SEC = 0;
    uint32_t reg_val = PORT_BUTTONS->IN;
    ISRcount_SEC = (ISRcount_SEC + 1) % 10;
    ISRcount_BLK = (ISRcount_BLK + 1) % 10;
    if (ISRcount_BLK == 0) {
        BLK = HW01_ALERT_BLINK;
    }
    else BLK = HW01_ALERT_NONE;

    if (ISRcount_SEC == 0) {
        INC = HW01_ALERT_TIME_UPDATE;
    }
    else INC = HW01_ALERT_NONE;

    if ((reg_val & SW1_MASK) == 0) {
        ISRcount_SW1++;
        if (ISRcount_SW1 >= 20) SW3 = HW01_ALERT_BUTTON_GT_2S;
    }
    else {
        if (ISRcount_SW1 < 20) SW1 = HW01_ALERT_BUTTON_LT_2S;
        else SW1 = HW01_ALERT_BUTTON_GT_2S;
        ISRcount_SW1 = 0;
    }

    if ((reg_val & SW2_MASK) == 0) {
        ISRcount_SW2++;
        if (ISRcount_SW2 >= 20) SW3 = HW01_ALERT_BUTTON_GT_2S;
    }
    else {
        if (ISRcount_SW2 < 20) SW2 = HW01_ALERT_BUTTON_LT_2S;
        else SW2 = HW01_ALERT_BUTTON_GT_2S;
        ISRcount_SW2 = 0;
    }

    if ((reg_val & SW3_MASK) == 0) {
        ISRcount_SW3++;
        if (ISRcount_SW3 >= 20) SW3 = HW01_ALERT_BUTTON_GT_2S;
    }
    else {
        if (ISRcount_SW3 < 20) SW3 = HW01_ALERT_BUTTON_LT_2S;
        else SW3 = HW01_ALERT_BUTTON_GT_2S;
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
