/**
 * @file hw02.c
 * @author Dominic Valentini (dvalentini@wisc.edu)
 * @author Adam Boho (boho2@wisc.edu)
 * @author Han Lyu (hlyu42@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "main.h"
#include "project.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"


/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char PROJ_DESCRIPTION[] = "ECE353: Project; Dominic Valentini, Adam Boho, Han Lyu";
// timer objects and uart object
cyhal_timer_t proj_timer_obj_proj;
cyhal_timer_cfg_t proj_timer_cfg_proj;
extern cyhal_uart_t proj_remote_uart_proj;
// cyhal results

/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
void proj_timer_handler(void)
{
    
}
void proj_main_app(void)
{

}

void proj_periph_init(void)
{

}