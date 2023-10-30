/**
 * @file hw02.h
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-09-16
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __HW02_H__
#define __HW02_H__

#include "drivers/joystick.h"

#define SCREEN_X            320
#define SCREEN_Y            240

#define SCREEN_CENTER_COL    ((SCREEN_X/2)-1)
#define SCREEN_CENTER_ROW    ((SCREEN_Y/2)-1)

#define LINE_WIDTH          4
#define LINE_LENGTH         120 

#define SQUARE_SIZE         32

#define PADDING             2

#define LEFT_COL                      (SCREEN_CENTER_COL - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_COL                    (SCREEN_CENTER_COL)
#define RIGHT_COL                     (SCREEN_CENTER_COL + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_ROW                     (SCREEN_CENTER_ROW - SQUARE_SIZE - (2*PADDING) - LINE_WIDTH)
#define CENTER_ROW                    (SCREEN_CENTER_ROW)
#define LOWER_ROW                     (SCREEN_CENTER_ROW + SQUARE_SIZE + (2*PADDING) + LINE_WIDTH)

#define UPPER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define LOWER_HORIZONTAL_LINE_Y     (SCREEN_CENTER_ROW + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)

#define LEFT_HORIZONTAL_LINE_X      (SCREEN_CENTER_COL - (SQUARE_SIZE/2) - PADDING - LINE_WIDTH/2)
#define RIGHT_HORIZONTAL_LINE_X     (SCREEN_CENTER_COL + (SQUARE_SIZE/2) + PADDING + LINE_WIDTH/2)

#define FG_COLOR_X                LCD_COLOR_YELLOW
#define BG_COLOR_X                LCD_COLOR_BLACK
#define FG_COLOR_O                LCD_COLOR_CYAN
#define BG_COLOR_O                LCD_COLOR_BLACK

#define FG_COLOR_CLAIMED          LCD_COLOR_BLACK
#define BG_COLOR_CLAIMED          LCD_COLOR_RED

#define FG_COLOR_UNCLAIMED        LCD_COLOR_BLACK
#define BG_COLOR_UNCLAIMED        LCD_COLOR_GREEN

#define JOYSTICK_UP               0xD173
#define JOYSTICK_DOWN             0x2E8B
#define JOYSTICK_LEFT             0xD173
#define JOYSTICK_RIGHT            0x2E8B

extern char HW02_DESCRIPTION[];

typedef struct square {
    int col;
    int row;
    char player;
} square;

/**
 * @brief 
 * Initializes the PSoC6 Peripherals used for HW02 
 */
void hw02_peripheral_init(void);

/**
 * @brief 
 * Implements the main application for HW02 
 */
void hw02_main_app(void);

void move_active(void);
void draw_board(void);
bool is_active(square *sq);
bool claim_square();
void board_init(square board[3][3]);
void check_win();
void game_over_state();

#endif