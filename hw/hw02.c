/**
 * @file hw02.c
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "main.h"
#include "hw02.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"


/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char HW02_DESCRIPTION[] = "ECE353: HW02 Name1, Name2";


/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/

/*****************************************************************************/
/*  HW02 Functions                                                           */
/*****************************************************************************/

/**
 * @brief
 * Initializes the PSoC6 Peripherals used for HW01
 */
void hw02_peripheral_init(void)
{
    /* Initialize the pushbuttons */
    push_buttons_init();

    /* Initialize the LCD */
    ece353_enable_lcd();

    /* Initialize the joystick*/
    joystick_init();

    /* Initialize the remote UART */
    //remote_uart_init();

    /* Initialize Timer to generate interrupts every 100mS*/
}

/**
 * @brief
 * Implements the main application for HW02
 */
void hw02_main_app(void)
{
    tic_tac_toe_example_board();

    while(1)
    {

    }
}