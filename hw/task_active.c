/**
 * @file task_active.c
 * @author Adam Boho, Han Lyu, Dom Valentini
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_active.h"
#include "lcd_images.h"

TaskHandle_t update_task;
TaskHandle_t paddle_task;
TaskHandle_t clear_task;
TaskHandle_t read_xl_task;
TaskHandle_t light_task;
bool cleared = false;
bool ball_crossed;
int offset = SCREEN_X/8;
extern bool gameOver;
bool light_en;
int8_t x, y;

extern QueueHandle_t send_score_queue;
extern QueueHandle_t send_light_queue;
score_message_t score_display;
uint8_t bitmap_one[];
uint8_t bitmap_two[];

uint16_t colors[4] = {LCD_COLOR_BLUE, LCD_COLOR_CYAN, LCD_COLOR_RED, LCD_COLOR_MAGENTA};

uint16_t active_color = LCD_COLOR_BLUE;

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
        
        if (player1_claimed && cleared && !gameOver) {
            if (active) {
                xQueueReceive(send_score_queue, &score_display, 5);
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
                if (ballX < ballWidthPixels/2 + 5) {
                    balldx = -balldx;
                    if (balldx == 0) balldx = (rand() % 2) + 2;
                    bool reg = false;
                    if (isplayer1) {
                        xQueueSend(point_registered_queue, &reg, 5);
                    }
                    else {
                        reg = true;
                        xQueueSend(point_registered_queue, &reg, 5);
                    }
                    remote_uart_tx_char_async(99);
                    remote_uart_tx_char_async(99);
                    remote_uart_tx_char_async(99);
                    remote_uart_tx_char_async('\n');
                }
                //If ballY coordinate is recognizing a colosion with the bottom
                if (ballY < ballHeightPixels/2 + 5) {
                    balldy = -balldy;
                    //if ball speed is 0, give it a random pos value
                    if (balldy == 0) balldy = (rand() % 2) + 1;
                }
                //If ballY coordinate is recognizing a colosion with the top
                if (ballY > SCREEN_Y - ballHeightPixels/2 - 5) {
                    balldy = -balldy;
                    //if ball speed is 0, give it a random neg value
                    if (balldy == 0) balldy = -(rand() % 2) - 1;
                }
                //If ballX Coord is coliding with the 
                if (ballX > SCREEN_X - ballWidthPixels/2 - 5 && balldx > 0) {
                    balldx = -balldx;
                    if (balldx == 0) balldx = -(rand() % 2) - 2;
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
                    if (playerX > paddleLeftWidthPixels/2 + 5) playerX -= 2;
                    balldx = (rand() % 2) + 1;
                    balldy = (rand() % 2) + 1;
                }
                //else if (joystick_read_x() < JOYSTICK_THRESH_X_RIGHT_0P825V && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX++;  
                else if (x < -10 && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX += -(x/30);  
                if (in_contact_left()) {
                    if (playerX < SCREEN_X - paddleLeftWidthPixels/2 - 5) playerX += 2;
                    balldx = -(rand() % 2) - 1;
                    balldy = (rand() % 2) + 1;
                }
                //else if (joystick_read_x() > JOYSTICK_THRESH_X_LEFT_2P475V && playerX > paddleLeftWidthPixels/2 + 2) playerX--;
                else if (x > 10 && playerX > paddleLeftWidthPixels/2 + 5) playerX += -(x/30); 
                if (in_contact_above()) {
                    if (playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 5) playerY += 2;
                    balldx = (rand() % 2) + 1;
                    balldy = -(rand() % 2) - 1;
                }
                //else if (joystick_read_y() > JOYSTICK_THRESH_Y_UP_2P475V && playerY > paddleLeftHeightPixels/2 + 2) playerY--;
                else if (y < -10 && playerY > paddleLeftHeightPixels/2 + 5) playerY += (y/30); 
                if (in_contact_below()) {
                    if (playerY > paddleLeftHeightPixels/2 + 5) playerY -= 2;
                    balldx = (rand() % 2) + 1;
                    balldy = (rand() % 2) + 1;
                }
                //else if (joystick_read_y() < JOYSTICK_THRESH_Y_DOWN_0P825V && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 2) playerY++;
                else if (y > 10 && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 10) playerY += (y/30); 
                ballX = ballX + balldx;
                ballY = ballY + balldy;
                
                if (active) {
                    lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, active_color, LCD_COLOR_BLACK);
                    lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
                }
                else {
                    lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                }
            }
            else {
                //if (joystick_read_x() < JOYSTICK_THRESH_X_RIGHT_0P825V && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 2) playerX++;  
                if (x < -10 && playerX < SCREEN_X - paddleLeftWidthPixels/2 - 5) playerX += -(x/30); 
                //if (joystick_read_x() > JOYSTICK_THRESH_X_LEFT_2P475V && playerX > paddleLeftWidthPixels/2 + 2) playerX--;
                if (x > 10 && playerX > paddleLeftWidthPixels/2 + 5) playerX += -(x/30);
                //if (joystick_read_y() > JOYSTICK_THRESH_Y_UP_2P475V && playerY > paddleLeftHeightPixels/2 + 2) playerY--;
                if (y < -10 && playerY > paddleLeftHeightPixels/2 + 5) playerY += (y/30);
                //if (joystick_read_y() < JOYSTICK_THRESH_Y_DOWN_0P825V && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 2) playerY++;
                if (y > 10 && playerY < SCREEN_Y - paddleLeftHeightPixels/2 - 10) playerY += (y/30);
                lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, active_color, LCD_COLOR_BLACK);
            }

            xQueueReceive(send_score_queue, &score_display, portMAX_DELAY);
            // if (score_display.player_one_score == 9 || score_display.player_two_score == 9) {
            //     gameOver = true;
            // }
            uint8_t *one_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_one_score]];
            uint8_t *two_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_two_score]];
            uint8_t *colon_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[10]];  
            if (score_display.player_one_score == 9 || score_display.player_two_score == 9) {
                gameOver = true;
                lcd_draw_rectangle_centered(RIGHT_BOUND - 40, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, LCD_COLOR_BLACK);
                lcd_draw_rectangle_centered(RIGHT_BOUND - 80, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, LCD_COLOR_BLACK);
                lcd_draw_rectangle_centered(RIGHT_BOUND - 60, UPPER_BOUND - 40, numberWidthPixels,
                numberHeightPixels, LCD_COLOR_BLACK);
                xTaskNotifyGive(eeprom_task);
            } 
            else {
                lcd_draw_image(RIGHT_BOUND - 40, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, one_bitmap , LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 80, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, two_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 60, UPPER_BOUND - 40, numberWidthPixels,
                numberHeightPixels, colon_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
            }
            
        }
        else {                        
            vTaskDelay(0);
        }
    }
}

void task_light()
{
    while (1)
    {
        static bool prev = true;
        static int count = 0;
        xQueueReceive(send_light_queue, &light_en, portMAX_DELAY);
        

        if (light_en && !prev && isplayer1)
        {
            active_color = colors[count + 2];
            count = (count+1) % 2;
        }
        else if (light_en && !prev && !isplayer1)
        {
            active_color = colors[count];
            count = (count+1) % 2;
        }

        prev = light_en;

    }
}

void task_clear(void *pvParameters) {
    while (1) {
        ulTaskNotifyTake(true, 5);
        if (player1_claimed) {
            if (!cleared) {
                lcd_clear_screen(LCD_COLOR_BLACK);
                cleared = true;
                vTaskDelete(clear_task);
            }
            else vTaskDelay(0);

        }
    }
}
void task_read_xl(void *pvParameters) {
  while (1)
  {
    if (!gameOver) {
        static uint8_t counter = 0;
        imu_init();
        static int16_t avg_data[3];
        int16_t data[3];
        lsm6dsm_acceleration_raw_get(&dev_ctx, data);
        x = data[0]/100;
        y = data[1]/100 - 30;
        if (y < -100 || y > 100) y = 0;
    }
    else vTaskDelay(0);
  }
}
void task_active_init() {
    // /* Wait sensor boot time */
    //xTaskCreate(task_move_paddle, "move paddle", configMINIMAL_STACK_SIZE, NULL, 2, &paddle_task);
    xTaskCreate(task_clear, "Active task", configMINIMAL_STACK_SIZE, NULL, 2, &clear_task);
    xTaskCreate(task_update, "update positions", configMINIMAL_STACK_SIZE, NULL, 2, &update_task);
    xTaskCreate(task_read_xl, "read xl", configMINIMAL_STACK_SIZE, NULL, 2, &read_xl_task);
    xTaskCreate(task_light, "Light Task", configMINIMAL_STACK_SIZE, NULL, 2, &light_task);
}


