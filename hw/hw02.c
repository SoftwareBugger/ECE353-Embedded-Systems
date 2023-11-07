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
#include "hw02.h"
#include "hw02-lcd-staff.h"
#include "hw02-images.h"


/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char HW02_DESCRIPTION[] = "ECE353: HW02 Dominic Valentini, Adam Boho, Han Lyu";
cyhal_timer_t timer_obj_hw2;
cyhal_timer_cfg_t timer_cfg_hw2;

extern cyhal_uart_t remote_uart_obj;

square board[3][3];
int active_sq[2];
char curr_player = 'x';
bool player_one;


/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
void timer_Handler()
{
    // the timer handler moves active square and claims new square
    move_active();
    claim_square();
    
}
/*****************************************************************************/
/*  HW02 Functions                                                           */
/*****************************************************************************/
void wait_for_turn()
{
    __disable_irq();
    draw_board();
    lcd_wait_for_other_player();
    uint8_t msg;
    receive_from_remote(&msg);
    while (msg != 0x00 && msg != 0x01 && msg != 0x02 && 
    msg != 0x10 && msg != 0x11 && msg != 0x12 &&
    msg != 0x20 && msg != 0x21 && msg != 0x22)
    {
        receive_from_remote(&msg);
    }
        int i = (msg & 0x03);
        int j = ((msg & 0x30) >> 4);
        board[i][j].player = curr_player;
        draw_board();
        if (curr_player == 'x')
        {
            curr_player = 'y';
        }
        else
        {
            curr_player = 'x';
        }
        __enable_irq();
}

void starting_char_sel()
{
    if (player_one)
    {
        while(get_buttons() != BUTTON_SW2_RELEASED)
        {
            if (get_buttons() == BUTTON_SW1_RELEASED)
            {
                if (curr_player == 'x')
                {
                    curr_player = 'o';
                    draw_board();
                }
                else
                {
                    curr_player = 'x';
                    draw_board();
                }
            }
        }
        if (curr_player == 'x')
        {
            send_to_remote(X_SELECTION);
            wait_for_ack();
        }
        else
        {
            send_to_remote(Y_SELECTION);
            wait_for_ack();
        }   
    }

    else
    {
        uint8_t msg;
        tic_tac_toe_draw_grid();
        lcd_wait_for_other_player();
        receive_from_remote(&msg);
        while(msg != X_SELECTION && msg != Y_SELECTION)
        {
            receive_from_remote(&msg);
        }
        if (msg == X_SELECTION)
        {
            curr_player = 'x';
            send_ack_byte();
            wait_for_turn();
        }
        else if (msg == Y_SELECTION)
        {
            curr_player = 'o';
            send_ack_byte();
            wait_for_turn();
        }
    }
    
}

void send_ack_byte()
{
    send_to_remote(ACK_BYTE);
}

void wait_for_ack()
{
    uint8_t msg;
    receive_from_remote(&msg);
    while(msg != ACK_BYTE)
    {
        receive_from_remote(&msg);
    }
}

void player_one_sel()
{   
    __disable_irq();
    lcd_clear_screen(LCD_COLOR_BLACK);
    lcd_select_player1();
    uint8_t msg;
    receive_from_remote(&msg);
    while(get_buttons() != BUTTON_SW2_RELEASED && msg != PLAYER1_SELECTION)
    {
        receive_from_remote(&msg);
        if (get_buttons() ==  BUTTON_SW2_RELEASED)
        {
            send_to_remote(PLAYER1_SELECTION);
            player_one = true;;
            wait_for_ack();
            starting_char_sel();
        }
        else if (msg == PLAYER1_SELECTION)
        {
            send_ack_byte();
            player_one = false;
            starting_char_sel();
        }
    }
    __enable_irq();
}


void send_to_remote(uint8_t msg)
{
    // I think these will get changed to functions from remote_uart_tx.c - currently placeholder
    // cy_rslt_t rslt = cyhal_uart_putc(&remote_uart_obj, msg);
    // CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    remote_uart_tx_data_async(&msg);


}

void receive_from_remote(uint8_t *msg)
{
    // I think these will get changed to functions from remote_uart_rx.c - currently placeholder
    // cy_rslt_t rslt = cyhal_uart_getc(&remote_uart_obj, msg, 0); 
    // CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    bool rslt = remote_uart_rx_data_async(msg, 8);
    if (rslt == false)
    {
        return 0xFF;
    }
}

/**
 * @brief define the behavior when the game is over
 * 
 */
void game_over_state()
{
    // reinitialize the board if the game is over, also switch order of the two players
    board_init(board);
    // when button two is pressed, start a new game by clearing the screen and redraw the board
    while(1)
    {
        if (get_buttons() == BUTTON_SW2_RELEASED)
        {
            lcd_clear_screen(LCD_COLOR_BLACK);
            player_one_sel();
            draw_board();
            break;
        }
    }
}
/**
 * @brief check if there is a winner or a tie
 * 
 */
void check_win()
{
    // check if there is a winner in the first row
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
    // check the first column
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
        // check the diagonal line
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
        // check the second row
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
        // check the third row
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
        // check the second column
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
        // check the third column
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
        // check the other diagonal line
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
    // no winner check for a tie
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

/**
 * @brief draw the board on the LCD screen
 * 
 */
void draw_board(void)
{
    // Horizontal Lines
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);

    // Vertical Lines
    lcd_draw_rectangle_centered(LEFT_VERTICAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(RIGHT_VERTICAL_LINE_X, SCREEN_CENTER_ROW, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);

    // draw the square according to their status
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // in case when the square is not active
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
            // when the square is active
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
 * @brief moves the active square
 */
void move_active(void)
{
    // variables that hold the values of the joystick
    static uint16_t x = 0;
    static uint16_t y = 0;
    // if not at center position before, reread
    if (x > JOYSTICK_LEFT || x < JOYSTICK_RIGHT || y > JOYSTICK_UP || y < JOYSTICK_DOWN) {
        x = joystick_read_x();
        y = joystick_read_y();
        return;
    }
    // read the value and move active square
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

/**
 * @brief initialize the board
 * 
 * @param board 
 */
void board_init(square board[3][3])
{
    // all squares have no player
    for (int i = 0; i < 3; i++) 
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j].player = '\0';
        }
    }
    // the coordinates on the LCD are fixed for each square
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

    // the active square starts at the center
    active_sq[0] = 1;
    active_sq[1] = 1;

}

/**
 * @brief claim a square on the board
 * 
 * @return true when the claim is successful
 * @return false when the claim failed
 */
bool claim_square()
{
    // button 1 pressed, try to claim
    if (get_buttons() == BUTTON_SW1_PRESSED) {
        if (board[active_sq[0]][active_sq[1]].player != '\0') return false;
        else {
            board[active_sq[0]][active_sq[1]].player = curr_player;
            uint8_t msg = (active_sq[0] << 4) + active_sq[1];
            send_to_remote(msg);
            wait_for_ack();
            if (curr_player == 'x') curr_player = 'o';
            else curr_player = 'x';
            draw_board();
            check_win();
            wait_for_turn();
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
    remote_uart_init();
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
    // only initialize the borad and draw it for the first time, leave other jobs to the timer handler
    board_init(board);
    player_one_sel();
    draw_board();
    while(1)
    {

    }
}