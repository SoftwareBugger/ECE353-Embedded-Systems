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
cyhal_timer_t timer_obj_hw2;
cyhal_timer_cfg_t timer_cfg_hw2;

square board[3][3];
int active_sq[2];
char curr_player = 'x';
static char starting_player = 'x';


/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
void timer_Handler()
{
    move_active();
    claim_square();
    
}
/*****************************************************************************/
/*  HW02 Functions                                                           */
/*****************************************************************************/
void game_over_state()
{
    //__disable_irq();
    board_init(board);
    if (starting_player == 'x')
    {
        curr_player = 'o';
        starting_player = 'o';
    }
    else
    {
        curr_player = 'x';
        starting_player = 'x';
    }

    while(1)
    {
        if (get_buttons() == BUTTON_SW2_RELEASED)
        {
            //__enable_irq();
            lcd_clear_screen(LCD_COLOR_BLACK);
            draw_board();
            break;
        }
    }
}
void check_win()
{
    if (((board[0][0].player == board[1][0].player) && board[0][0].player == board[2][0].player))
    {
        switch(board[0][0].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[0][0].player == board[0][1].player) && board[0][0].player == board[0][2].player))
    {
        switch(board[0][0].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[0][0].player == board[1][1].player) && board[0][0].player == board[2][2].player))
    {
        switch(board[0][0].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[0][1].player == board[1][1].player) && board[0][1].player == board[2][1].player))
    {
        switch(board[0][1].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[0][2].player == board[1][2].player) && board[0][2].player == board[2][2].player))
    {
        switch(board[0][2].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;;
        }
    }
        else if (((board[1][0].player == board[1][1].player) && board[1][0].player == board[1][2].player))
    {
        switch(board[1][0].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[2][0].player == board[2][1].player) && board[2][0].player == board[2][2].player))
    {
        switch(board[2][0].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
        else if (((board[0][2].player == board[1][1].player) && board[0][2].player == board[2][0].player))
    {
        switch(board[0][2].player){
            case('x'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_X_wins();
                game_over_state();
                break;
            case('o'):
                lcd_clear_screen(LCD_COLOR_BLACK);
                lcd_O_wins();
                game_over_state();
                break;
            default:
                break;
        }
    }
    else
    {
        bool full = true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j].player == '\0')
                {
                    full = false;
                }
            }
        }
        if (full)
        {
            lcd_clear_screen(LCD_COLOR_BLACK);
            lcd_tie();
            game_over_state();
        }
    }
}

void draw_board(void)
{
    // Horizontal Lines
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);

    // Vertical Lines
    lcd_draw_rectangle_centered(LEFT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(RIGHT_HORIZONTAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (!is_active(&board[i][j])) {
                switch (board[i][j].player) {
                    case '\0':
                        lcd_draw_rectangle_centered(board[i][j].col, board[i][j].row, SQUARE_SIZE, SQUARE_SIZE, BG_COLOR_O);
                        lcd_draw_image(board[i][j].col, board[i][j].row, O_WIDTH, O_HEIGHT, Bitmaps_O, BG_COLOR_O, BG_COLOR_O);
                        break;
                    case 'x':
                        lcd_draw_rectangle_centered(board[i][j].col, board[i][j].row, SQUARE_SIZE, SQUARE_SIZE, BG_COLOR_X);
                        lcd_draw_image(board[i][j].col, board[i][j].row, X_WIDTH, X_HEIGHT, Bitmaps_X, FG_COLOR_X, BG_COLOR_X);
                        break;
                    case 'o':
                        lcd_draw_rectangle_centered(board[i][j].col, board[i][j].row, SQUARE_SIZE, SQUARE_SIZE, BG_COLOR_O);
                        lcd_draw_image(board[i][j].col, board[i][j].row, O_WIDTH, O_HEIGHT, Bitmaps_O, FG_COLOR_O, BG_COLOR_O);
                        break;
                }
                
            }
            else {
                uint8_t *map;
                uint8_t size[2];
                if (curr_player == 'x') {
                    map = Bitmaps_X;
                    size[0] = X_WIDTH;
                    size[1] = X_HEIGHT;
                }
                else {
                    map = Bitmaps_O;
                    size[0] = O_WIDTH;
                    size[1] = O_HEIGHT;
                }
                switch (board[i][j].player) {
                    case '\0':
                        lcd_draw_rectangle_centered(board[i][j].col, board[i][j].row, SQUARE_SIZE, SQUARE_SIZE, BG_COLOR_UNCLAIMED);
                        lcd_draw_image(board[i][j].col, board[i][j].row, size[0], size[1], map, FG_COLOR_UNCLAIMED, BG_COLOR_UNCLAIMED);
                        break;
                    default:
                        lcd_draw_rectangle_centered(board[i][j].col, board[i][j].row, SQUARE_SIZE, SQUARE_SIZE, BG_COLOR_CLAIMED);
                        lcd_draw_image(board[i][j].col, board[i][j].row, size[0], size[1], map, FG_COLOR_CLAIMED, BG_COLOR_CLAIMED);
                        break;
                }

            }
        }
    }
}
/**
 * @brief
 * moves the active square
 */
void move_active(void)
{
    static uint16_t x = 0;
    static uint16_t y = 0;
    if (x > JOYSTICK_LEFT || x < JOYSTICK_RIGHT || y > JOYSTICK_UP || y < JOYSTICK_DOWN) {
        x = joystick_read_x();
        y = joystick_read_y();
        return;
    }
    else {
        x = joystick_read_x();
        y = joystick_read_y();
        if (x > JOYSTICK_LEFT) 
        {
            if (active_sq[0] > 0) active_sq[0] = active_sq[0] - 1;
            else active_sq[0] = 2;
            draw_board();
        }
        else if (x < JOYSTICK_RIGHT)
        {
            if (active_sq[0] < 2) active_sq[0] = active_sq[0] + 1;
            else active_sq[0] = 0;
            draw_board();
        }

        if (y > JOYSTICK_UP) 
        {
            if (active_sq[1] > 0) active_sq[1] = active_sq[1] - 1;
            else active_sq[1] = 2;
            draw_board();
        }
        else if (y < JOYSTICK_DOWN)
        {
            if (active_sq[1] < 2) active_sq[1] = active_sq[1] + 1;
            else active_sq[1] = 0;
            draw_board();
        }
    }
}

void board_init(square board[3][3])
{
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j].player = '\0';
        }
    }

    board[0][0].col = LEFT_COL;
    board[0][0].row = UPPER_ROW;
    
    board[0][1].col = LEFT_COL;
    board[0][1].row = CENTER_ROW;

    board[0][2].col = LEFT_COL;
    board[0][2].row = LOWER_ROW;

    board[1][0].col = CENTER_COL;
    board[1][0].row = UPPER_ROW;

    board[1][1].col = CENTER_COL;
    board[1][1].row = CENTER_ROW;

    board[1][2].col = CENTER_COL;
    board[1][2].row = LOWER_ROW;

    board[2][0].col = RIGHT_COL;
    board[2][0].row = UPPER_ROW;

    board[2][1].col = RIGHT_COL;
    board[2][1].row = CENTER_ROW;

    board[2][2].col = RIGHT_COL;
    board[2][2].row = LOWER_ROW;

    active_sq[0] = 1;
    active_sq[1] = 1;

}

bool claim_square()
{
    if (get_buttons() == BUTTON_SW1_PRESSED) {
        if (board[active_sq[0]][active_sq[1]].player != '\0') return false;
        else {
            board[active_sq[0]][active_sq[1]].player = curr_player;
            if (curr_player == 'x') curr_player = 'o';
            else curr_player = 'x';
            draw_board();
            check_win();
            return true;
        }
    }
    return false;
}
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
    timer_init(&timer_obj_hw2, &timer_cfg_hw2, 10000000, timer_Handler);
}
bool is_active(square *sq) {
    return ((sq->col == board[active_sq[0]][active_sq[1]].col) && (sq->row == board[active_sq[0]][active_sq[1]].row));
}
/**
 * @brief
 * Implements the main application for HW02
 */
void hw02_main_app(void)
{
    board_init(board);
    draw_board();
    while(1)
    {

    }
}