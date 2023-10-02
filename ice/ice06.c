/**
 * @file ice01.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-08-25
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "../main.h"

#if defined(ICE) && (FILE_ID == 6)

/*****************************************************************************/
/*  Custom Data Types                                                        */
/*****************************************************************************/
typedef enum {
    TIMER_ALERT_NONE,
    TIMER_ALERT_SW1,
    TIMER_ALERT_SW2,
    TIMER_ALERT_SW3,
}timer_alerts_t;

/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char ICE_DESCRIPTION[] = "ECE353: ICE06 - Timer Interrupts";
timer_alerts_t SW1;
timer_alerts_t SW2;
timer_alerts_t SW3;

#define TICKS_MS_010 1000000

const cyhal_timer_cfg_t ice_timer_cfg =
    {
        .compare_value = 0,              /* Timer compare value, not used */
        .period = TICKS_MS_010,          /* number of timer ticks for 10mS*/
        .direction = CYHAL_TIMER_DIR_UP, /* Timer counts up */
        .is_compare = false,             /* Don't use compare mode */
        .is_continuous = true,           /* Run timer indefinitely */
        .value = 0                       /* Initial value of counter */
};

/* Timer object used */
cyhal_timer_t ice_timer_obj;

/* Handler Alert Variables*/
/* ADD CODE */

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
/**
 * @brief
 *  Function used as Timer Handler
 */
void Handler_Timer(void *handler_arg, cyhal_timer_event_t event)
{
    /* Static Vars */
    static uint8_t ISRcount_SW1 = 0;
    static uint8_t ISRcount_SW2 = 0;
    static uint8_t ISRcount_SW3 = 0;
    uint32_t reg_val = PORT_BUTTONS->IN;

    /* Many mechanical buttons will bounce when they are pressed.
    *  The signal may oscillate between 0 and 1 for several milliseconds.
    *
    * We will debounce a button by sampling the button and detecting the first
    * 30mS interval of time when the button is low.  When that period of time is
    * detected, we will alert the main application.
    */

   /* ADD CODE */
   
    if ((reg_val & SW1_MASK) == 0) {
        ISRcount_SW1++;
        if (ISRcount_SW1 == 3) SW1 = TIMER_ALERT_SW1;
    }
    else {
        ISRcount_SW1 = 0;
    }

    if ((reg_val & SW2_MASK) == 0) {
        ISRcount_SW2 = ISRcount_SW2 + 1;
        if (ISRcount_SW2 == 3) SW2 = TIMER_ALERT_SW2;
    }
    else {
        ISRcount_SW2 = 0;
    }

    if ((reg_val & SW3_MASK) == 0) {
        ISRcount_SW3 = ISRcount_SW3 + 1;
        if (ISRcount_SW3 == 3) SW3 = TIMER_ALERT_SW3;
    }
    else {
        ISRcount_SW3 = 0;
    }
   

}

/**
 * @brief
 * This function will initialize all of the hardware resources for
 * the ICE
 */
void peripheral_init(void)
{
    cy_rslt_t rslt;

    /* Initialize the push buttons */
    push_buttons_init();
    
    /* Initialize a timer */
    rslt = cyhal_timer_init(&ice_timer_obj, NC, NULL);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Apply timer configuration such as period, count direction, run mode, etc. */
    rslt = cyhal_timer_configure(&ice_timer_obj, &ice_timer_cfg); 
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Set the frequency of timer*/
    rslt = cyhal_timer_set_frequency(&ice_timer_obj,100000000); 
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU

    /* Assign the ISR to execute on timer interrupt */
    cyhal_timer_register_callback(&ice_timer_obj,Handler_Timer,NULL);

    /* Set the event on which timer interrupt occurs and enable it */
    cyhal_timer_enable_event(&ice_timer_obj, CYHAL_TIMER_IRQ_TERMINAL_COUNT,3, true);

    /* Start the timer with the configured settings */
    rslt = cyhal_timer_start(&ice_timer_obj);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS); // If the initialization fails, halt the MCU
}

/*****************************************************************************/
/* Application Code                                                          */
/*****************************************************************************/
/**
 * @brief
 * This function implements the behavioral requirements for the ICE
 */
void main_app(void)
{
     /* Enter Infinite Loop*/
    while (1)
    {
        /* ADD CODE */

        /* Print if SW1 has been pressed. */
        if (SW1 == TIMER_ALERT_SW1) {
            printf("SW1 has been pressed\n");
            SW1 = 0;
        }
        /* Print if SW2 has been pressed. */
        if (SW2 == TIMER_ALERT_SW2) {
            printf("SW2 has been pressed\n");
            SW2 = 0;
        }
        
        /* Print if SW3 has been pressed. */
        if (SW3 == TIMER_ALERT_SW3) {
            printf("SW3 has been pressed\n");
            SW3 = 0;
        }

    }   
}
#endif