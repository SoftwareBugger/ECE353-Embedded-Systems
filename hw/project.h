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
#include "task_active.h"
#include "task_buttons.h"
#include "task_inactive.h"
#include "task_score.h"

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
#define PLAYER_LENGTH       24

#define CLAIME_PLAYER1      0x11

// ADC values
#define JOYSTICK_UP               0xD173
#define JOYSTICK_DOWN             0x2E8B
#define JOYSTICK_LEFT             0xD173
#define JOYSTICK_RIGHT            0x2E8B

// UART BYTES
#define ACK_BYTE                  0xF0

extern char PROJ_DESCRIPTION[];
extern bool active;
extern bool player1_claimed;
extern bool isplayer1;
extern bool serve_ball;
extern QueueHandle_t position_queue;
extern uint16_t playerX;
extern uint16_t playerY;
extern uint16_t ballX;
extern uint16_t ballY;
extern uint16_t balldx;
extern uint16_t balldy;
// extern Player player;
// typedef struct player {
//     uint16_t x_pos_center; // center position x of the player(paddle)
//     uint16_t y_pos_center; // center position y of the player(paddle)
//     uint16_t color; // the color of choice
// } Player;
// typedef struct ball {
//     uint16_t x_pos_center; // center position y of the ball
//     uint16_t y_pos_center; // center position x of the ball
//     int32_t angle; // -180 to 180 degrees 
//     uint16_t speed; // constant speed;
// } Ball;

// typedef struct coord{
//     uint16_t x; 
//     uint16_t y;
// } Coord;

// extern Player player;
/**
 * @brief 
 * Initializes the PSoC6 Peripherals used for project 
 */
void proj_periph_init(void);

/**
 * @brief 
 * Implements the main application for project
 */
void proj_main_app(void);

/**
 * @brief 
 * Handler for the timer
 */
void proj_timer_handler(void);

// /**
//  * @brief 
//  * Processes the ball hitting the player
//  */
// void proj_collision_handler(ball ball, player player);

#endif
