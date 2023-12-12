#include "task_active.h"
#include "lcd_images.h"

TaskHandle_t update_task;
TaskHandle_t paddle_task;
TaskHandle_t clear_task;
TaskHandle_t read_xl_task;
bool cleared = false;
bool ball_crossed;
int offset = SCREEN_X/8;


extern QueueHandle_t send_score_queue;
score_message_t score_display;
uint8_t bitmap_one[];
uint8_t bitmap_two[];

bool in_contact() {
    return ((ballX - playerX < (ballWidthPixels + paddleLeftWidthPixels)/2 + 5) 
         && (ballX - playerX > -(ballWidthPixels + paddleLeftWidthPixels)/2 - 5)
         && (ballY - playerY < (ballHeightPixels + paddleLeftHeightPixels)/2 + 5)
         && (ballY - playerY > -(ballHeightPixels + paddleLeftHeightPixels)/2 - 5));
}
bool in_contact_below() {
    return ((ballX - playerX < ((paddleLeftWidthPixels - ballWidthPixels)/2 + 5))
         && (ballX - playerX > -((paddleLeftWidthPixels - ballWidthPixels)/2 + 5))
         && (ballY - playerY < (ballHeightPixels + paddleLeftHeightPixels)/2 + 5)
         && (ballY - playerY > 0));
}
bool in_contact_above() {
    return ((ballX - playerX < ((paddleLeftWidthPixels - ballWidthPixels)/2 + 5))
         && (ballX - playerX > -((paddleLeftWidthPixels - ballWidthPixels)/2 + 5))
         && (ballY - playerY > -((ballHeightPixels + paddleLeftHeightPixels)/2 + 5))
         && (ballY - playerY < 0));
}
bool in_contact_left() {
    return ((ballX - playerX < 0) 
         && (ballX - playerX > -((ballWidthPixels + paddleLeftWidthPixels)/2 + 5))
         && (ballY - playerY < ((paddleLeftHeightPixels - ballHeightPixels)/2 + 5))
         && (ballY - playerY > -((paddleLeftHeightPixels - ballHeightPixels)/2 + 5)));
}
bool in_contact_right() {
    return ((ballX - playerX < ((ballWidthPixels + paddleLeftWidthPixels)/2 + 5)) 
         && (ballX - playerX > 0)
         && (ballY - playerY < ((paddleLeftHeightPixels - ballHeightPixels)/2 + 5))
         && (ballY - playerY > -((paddleLeftHeightPixels - ballHeightPixels)/2 + 5)));
}


void task_update(void *pvParameters) {
    while (1) {
        static uint8_t counter = 0;
        counter = (counter + 1)%1;
        if (player1_claimed && cleared) {
            if (active) {
                xQueueReceive(send_score_queue, &score_display, portMAX_DELAY);
                uint8_t *one_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_one_score]];
                uint8_t *two_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_two_score]];
                uint8_t *colon_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[10]];
                lcd_draw_image(RIGHT_BOUND - 40, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, one_bitmap , LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 80, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, two_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 60, UPPER_BOUND - 40, numberWidthPixels,
                numberHeightPixels, colon_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                if (!cleared) {
                    xTaskNotifyGive(clear_task);
                }
                if (!serve_ball) {
                    balldy = (rand() % 4) - 2;
                    serve_ball = true;
                }
                if (ballX <= ballWidthPixels/2 + 5) {
                    balldx = -balldx;
                    if (balldx == 0) balldx = (rand() % 2) + 1;
                    bool reg = false;
                    if (isplayer1) {
                        xQueueSend(point_registered_queue, &reg, 5);
                    }
                    else {
                        reg = true;
                        xQueueSend(point_registered_queue, &reg, 5);
                    }
                }
                if (ballY <= ballHeightPixels/2 + 5) {
                    balldy = -balldy;
                    if (balldy == 0) balldy = (rand() % 2) + 1;
                }
                if (ballY >= SCREEN_Y - ballHeightPixels/2 - 5) {
                    balldy = -balldy;
                    if (balldy == 0) balldy = -(rand() % 2) - 1;
                }
                if (ballX >= SCREEN_X - ballWidthPixels/2 - 5 && balldx > 0) {
                    balldx = -balldx;
                    if (balldx == 0) balldx = -(rand() % 2) - 1;
                    remote_uart_tx_char_async(balldx);
                    remote_uart_tx_char_async(balldy + 6);
                    remote_uart_tx_char_async(ballY);
                    if (isplayer1) remote_uart_tx_char_async(score_display.player_one_score);
                    else remote_uart_tx_char_async(score_display.player_two_score);
                    remote_uart_tx_char_async('\n');
                    active = false;
                    ball_crossed = false;
                    xTaskNotifyGive(inactive_task);
                }
                if (in_contact_right()) {
                    if (playerX > paddleLeftWidthPixels/2 + 2) playerX -= 2;
                    balldx = (rand() % 2) + 1;
                    balldy = (rand() % 3);
                }
                else if (joystick_read_x() < JOYSTICK_THRESH_X_RIGHT_0P825V && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX++;  
                if (in_contact_left()) {
                    if (playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX += 2;
                    balldx = -(rand() % 2) - 1;
                    balldy = (rand() % 3);
                }
                else if (joystick_read_x() > JOYSTICK_THRESH_X_LEFT_2P475V && playerX > paddleLeftWidthPixels/2 + 2) playerX--;
                if (in_contact_above()) {
                    if (playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 2) playerY += 2;
                    balldx = (rand() % 3);
                    balldy = -(rand() % 2) - 1;
                }
                else if (joystick_read_y() > JOYSTICK_THRESH_Y_UP_2P475V && playerY > paddleLeftHeightPixels/2 + 2) playerY--;
                
                if (in_contact_below()) {
                    if (playerY > paddleLeftHeightPixels/2 + 2)playerY -= 2;
                    balldx = (rand() % 3);
                    balldy = (rand() % 2) + 1;
                }
                else if (joystick_read_y() < JOYSTICK_THRESH_Y_DOWN_0P825V && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 2) playerY++;
                    
                if (counter == 0) {
                    ballX = ballX + balldx;
                    ballY = ballY + balldy;
                }
                uint16_t fcolor = LCD_COLOR_BLUE;
                if (isplayer1) fcolor = LCD_COLOR_RED;
                
                if (active) {
                    lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, fcolor, LCD_COLOR_BLACK);
                    lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
                }
                else {
                    lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                }
            }
            else {
                if (joystick_read_x() < JOYSTICK_THRESH_X_RIGHT_0P825V && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX++;  
                if (joystick_read_x() > JOYSTICK_THRESH_X_LEFT_2P475V && playerX > paddleLeftWidthPixels/2 + 2) playerX--;
                if (joystick_read_y() > JOYSTICK_THRESH_Y_UP_2P475V && playerY > paddleLeftHeightPixels/2 + 2) playerY--;
                if (joystick_read_y() < JOYSTICK_THRESH_Y_DOWN_0P825V && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 2) playerY++;
                uint16_t fcolor = LCD_COLOR_BLUE;
                if (isplayer1) fcolor = LCD_COLOR_RED;
                lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, fcolor, LCD_COLOR_BLACK);
            }
        }
    }
}
void task_clear(void *pvParameters) {
    while (1) {
        ulTaskNotifyTake(true, 5);
        if (player1_claimed) {
            if (!cleared) {
                lcd_clear_screen(LCD_COLOR_BLACK);
                cleared = true;
            }

        }
    }
}
void task_read_xl(void *pvParameters) {
  spi_init();
  while (1)
  {
    lsm6dsm_orientation();
  }
}
void task_active_init() {
    // /* Wait sensor boot time */
    //xTaskCreate(task_move_paddle, "move paddle", configMINIMAL_STACK_SIZE, NULL, 2, &paddle_task);
    //xTaskCreate(task_clear, "Active task", configMINIMAL_STACK_SIZE, NULL, 2, &clear_task);
    //xTaskCreate(task_update, "update positions", configMINIMAL_STACK_SIZE, NULL, 2, &update_task);
    xTaskCreate(task_read_xl, "read xl", configMINIMAL_STACK_SIZE, NULL, 2, &read_xl_task);
}


