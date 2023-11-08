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
cy_rslt_t rslt;

square board[3][3];
int active_sq[2];
char curr_player = 'x';
bool player_one_selected;
bool char_selected;
bool player_one;
bool is_active_player;


/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
void timer_Handler()
{
    // the timer handler moves active square and claims new square
    if (player_one_selected && char_selected && is_active_player) {
        move_active();
        claim_square();
    }
    else if (!player_one_selected) player_one_sel();
    else if (!char_selected) {
        starting_char_sel();
    }
    else if (!is_active_player) {
        wait_for_turn();
    }
    
}
/*****************************************************************************/
/*  HW02 Functions                                                           */
/*****************************************************************************/
void wait_for_turn()
{
    lcd_wait_for_other_player();
    char msg;
    remote_uart_rx_data_async(&msg, 1);
    if (msg != 0x00 && msg != 0x01 && msg != 0x02 && 
    msg != 0x10 && msg != 0x11 && msg != 0x12 &&
    msg != 0x20 && msg != 0x21 && msg != 0x22)
    {
        return;
    }
    else
    {
        int i = (msg & 0x03);
        int j = ((msg & 0x30) >> 4);
        if (curr_player == 'x') board[j][i].player = 'o';
        else board[j][i].player = 'x';
        lcd_clear_other_player();
        draw_board();
        is_active_player = true;
    }
    draw_board();
        
}

void starting_char_sel()
{
    char msg;
    remote_uart_rx_data_async(&msg, 1);
    if (player_one)
    {
        uint8_t button = get_buttons();
        if (button == BUTTON_SW2_RELEASED && !char_selected) {
            if (curr_player == 'x')
            {
                remote_uart_tx_char_async(X_SELECTION);
                remote_uart_tx_char_async('\n');
            }
            else
            {
                remote_uart_tx_char_async(O_SELECTION);
                remote_uart_tx_char_async('\n');
            }
        }
        else if (button == BUTTON_SW1_RELEASED && !char_selected)
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
        if (msg == ACK_BYTE) {
            is_active_player = true;
            char_selected = true;
        }
    }
    else
    {
        if (msg == X_SELECTION)
        {
            curr_player = 'o';
            remote_uart_tx_char_async(ACK_BYTE);
            remote_uart_tx_char_async('\n');
            char_selected = true;
        }
        else if (msg == O_SELECTION)
        {
            curr_player = 'x';
            remote_uart_tx_char_async(ACK_BYTE);
            remote_uart_tx_char_async('\n');
            char_selected = true;
        }
    }
    
}

void wait_for_ack()
{
    char msg;
    remote_uart_rx_data_async(&msg, 1);
    while(msg != ACK_BYTE)
    {
        remote_uart_rx_data_async(&msg, 1);
    }
}

void player_one_sel()
{   
    char msg;
    // remote_uart_rx_data_async(&msg, 1);
    // if (msg == PLAYER1_SELECTION) {
    //     remote_uart_tx_char_async(ACK_BYTE);
    //     player_one = false;
    //     player_one_selected = true;
    // }
    // else if (get_buttons() ==  BUTTON_SW2_PRESSED)
    // {
    //     printf("pressed\n");
    //     remote_uart_tx_char_async(PLAYER1_SELECTION);
    //     wait_for_ack();
    //     player_one = true;
    //     player_one_selected = true;
    // }
    if (get_buttons() ==  BUTTON_SW2_RELEASED) {
        printf("sent selection\n");
        remote_uart_tx_char_async(PLAYER1_SELECTION);
        remote_uart_tx_char_async('\n');
        player_one = true;
    }
    remote_uart_rx_data_async(&msg, 1);
    if (msg == PLAYER1_SELECTION) {
        printf("got selection\n");
        remote_uart_tx_char_async(ACK_BYTE);
        remote_uart_tx_char_async('\n');
        player_one_selected = true;
        player_one = false;
        lcd_clear_screen(LCD_COLOR_BLACK);
        draw_board();
    }
    else if (player_one && msg == ACK_BYTE) {
        printf("got ack\n");
        player_one_selected = true;
        lcd_clear_screen(LCD_COLOR_BLACK);
        draw_board();
    }
    printf("got nothing\n");
}


void send_to_remote(uint8_t *msg)
{
    // I think these will get changed to functions from remote_uart_tx.c - currently placeholder
    // cy_rslt_t rslt = cyhal_uart_putc(&remote_uart_obj, msg);
    // CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    remote_uart_tx_data_async(msg);


}

void receive_from_remote(uint8_t *msg)
{
    // I think these will get changed to functions from remote_uart_rx.c - currently placeholder
    // cy_rslt_t rslt = cyhal_uart_getc(&remote_uart_obj, msg, 0); 
    // CY_ASSERT(rslt == CY_RSLT_SUCCESS);

    rslt = remote_uart_rx_data_async(msg, 1);
    printf("msg = %i\n", *msg);
    CY_ASSERT(rslt == CY_RSLT_SUCCESS);
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
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, UPPER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(SCREEN_CENTER_COL, LOWER_HORIZONTAL_LINE_Y, LINE_LENGTH, LINE_WIDTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(LEFT_VERTICAL_LINE_X, SCREEN_CENTER_ROW + 20, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);
    lcd_draw_rectangle_centered(RIGHT_VERTICAL_LINE_X, SCREEN_CENTER_ROW + 20, LINE_WIDTH, LINE_LENGTH, LCD_COLOR_BLUE);

    // draw the square according to their status
    if (char_selected || player_one) {
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
                    if (board[i][j].player == 'x') {
                        map = Bitmaps_X;
                        size[0] = X_WIDTH;
                        size[1] = X_HEIGHT;
                    }
                    else if (board[i][j].player == 'o') {
                        map = Bitmaps_O;
                        size[0] = O_WIDTH;
                        size[1] = O_HEIGHT;
                    }
                    else {
                        map = (curr_player == 'x')?Bitmaps_X:Bitmaps_O;
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
    else if (!char_selected) {
        lcd_wait_for_other_player();
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
            draw_board();
            check_win();
            char msg = (active_sq[0] << 4) + active_sq[1];
            remote_uart_tx_char_async(msg);
            remote_uart_tx_char_async('\n');
            is_active_player = false;
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
    remote_uart_enable_interrupts();
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
    lcd_clear_screen(LCD_COLOR_BLACK);
    lcd_select_player1();
    player_one_selected = false;
    char_selected = false;
    while (!player_one_selected) {
        
    }
    while (!char_selected) {

    }
    while(1)
    {

    }
}