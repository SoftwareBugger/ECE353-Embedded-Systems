/**
 * @file hw01.h
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
#ifndef __HW01_H__
#define __HW01_H__

#include "hw01_draw.h"
#include "hw01_timer.h"
typedef enum {
    SET_TIME,
    RUN,
    SET_ALARM
}curr_mode;
/**
 * @brief 
 * Initializes the PSoC6 Peripherals used for HW01 
 */
void hw01_peripheral_init(void);

/**
 * @brief 
 * Implements the main application for HW01 
 */
void hw01_main_app(void);


#endif