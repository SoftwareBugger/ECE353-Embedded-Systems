/**
 * @file project.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __PROJECT_H__
#define __PROJECT_H__

#include "drivers/joystick.h"

#define SCREEN_X            320
#define SCREEN_Y            240

#define SCREEN_CENTER_COL    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_ROW    ((SCREEN_Y/2)-1)

#define LINE_WIDTH          4
#define LINE_LENGTH         120 

#define SQUARE_SIZE         32

#define PADDING             2

// ADC values
#define JOYSTICK_UP               0xD173
#define JOYSTICK_DOWN             0x2E8B
#define JOYSTICK_LEFT             0xD173
#define JOYSTICK_RIGHT            0x2E8B

// UART BYTES
#define PLAYER1_SELECTION         0x5A
#define ACK_BYTE                  0xF0
#define X_SELECTION               0x58
#define O_SELECTION               0x4F

extern char PROJECT_DESCRIPTION[];
// data structure for the square

/**
 * @brief 
 * Initializes the PSoC6 Peripherals used for HW02 
 */
void proj_periph_init(void);

/**
 * @brief 
 * Implements the main application for HW02 
 */
void proj_main_app(void);

/**
 * @brief 
 * Handler for the timer
 */
void proj_timer_handler(void);

#endif
