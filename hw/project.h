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
 

#define PADDING             2

#define RIGHT_BOUND         320
#define LEFT_BOUND          0
#define LOWER_BOUND         0
#define UPPER_BOUND         240

#define PLAYER_ALT          15
#define PLAYER_HEIGHT       6
#define PLAYER_LENGTH       20


// ADC values
#define JOYSTICK_UP               0xD173
#define JOYSTICK_DOWN             0x2E8B
#define JOYSTICK_LEFT             0xD173
#define JOYSTICK_RIGHT            0x2E8B

// UART BYTES
#define ACK_BYTE                  0xF0

extern char PROJECT_DESCRIPTION[];

typedef struct player {
    uint16_t x_pos;
    uint16_t color;
    bool active;
} player;

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
