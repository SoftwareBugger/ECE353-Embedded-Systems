/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "main.h"

char NAMES[] = "NAME1, NAME2";

int main(void)
{
    cy_rslt_t rslt;

    /* Initialize the device and board peripherals */
    rslt = cybsp_init() ;
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    printf_init();

    __enable_irq();

    /* Send the Clear Screen Escape Sequence*/
    printf("\x1b[2J\x1b[;H");

    printf("**************************************************\n\r");
    printf("* HW01 ECE353 F23\n\r");
    printf("* Date: %s\n\r", __DATE__);
    printf("* Time: %s\n\r", __TIME__);
    printf("* Names:%s\n\r", NAMES);
    printf("**************************************************\n\r");

    hw01_peripheral_init();

    hw01_main_app();

    for (;;)
    {
    }
}

/* [] END OF FILE */