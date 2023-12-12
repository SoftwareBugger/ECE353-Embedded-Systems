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
bool cleared = false;
bool ball_crossed;
int offset = SCREEN_X/8;
extern bool gameOver;


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
        
        if (player1_claimed && cleared && !gameOver) {
            if (active) {
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
                //If ballY coordinate is recognizing a colosion with the bottom
                if (ballY <= ballHeightPixels/2 + 5) {
                    balldy = -balldy;
                    //if ball speed is 0, give it a random pos value
                    if (balldy == 0) balldy = (rand() % 2) + 1;
                }
                //If ballY coordinate is recognizing a colosion with the top
                if (ballY >= SCREEN_Y - ballHeightPixels/2 - 5) {
                    balldy = -balldy;
                    //if ball speed is 0, give it a random neg value
                    if (balldy == 0) balldy = -(rand() % 2) - 1;
                }
                //If ballX Coord is coliding with the 
                if (ballX >= SCREEN_X - ballWidthPixels/2 - 5 && balldx > 0) {
                    balldx = -balldx;
                    if (balldx == 0) balldx = -(rand() % 2) - 1;
                    printf("send balldx :%i, balldy :%i, ballY :%u, ballX :%u\n", balldx, balldy, ballY, ballX);
                    remote_uart_tx_char_async(balldx);
                    remote_uart_tx_char_async(balldy + 6);
                    remote_uart_tx_char_async(ballY);
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
                vTaskDelay(10);
            }
            remote_uart_tx_data_async();
            xQueueReceive(send_score_queue, &score_display, portMAX_DELAY);
            if (score_display.player_one_score == 9 || score_display.player_two_score == 9) {
                gameOver = true;
            }
            uint8_t *one_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_one_score]];
            uint8_t *two_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_two_score]];
            uint8_t *colon_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[10]];
            if (gameOver){
                                
                lcd_draw_image(RIGHT_BOUND - 40, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, one_bitmap , LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 80, UPPER_BOUND - 40, numberWidthPixels, 
                numberHeightPixels, two_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                lcd_draw_image(RIGHT_BOUND - 60, UPPER_BOUND - 40, numberWidthPixels,
                numberHeightPixels, colon_bitmap, LCD_COLOR_BLACK, LCD_COLOR_BLACK);
                lcd_draw_image((SCREEN_X)/2, (SCREEN_Y)/2, gameOverWidthPixels, gameOverHeightPixels, gameOverBitmaps,LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                if (one_bitmap == 9){
                lcd_draw_image(RIGHT_BOUND - 140, UPPER_BOUND - 60, numberWidthPixels, 
                numberHeightPixels, one_bitmap , LCD_COLOR_GREEN, LCD_COLOR_BLACK); 
                } else {
                    lcd_draw_image(RIGHT_BOUND - 140, UPPER_BOUND - 60, numberWidthPixels, 
                numberHeightPixels, one_bitmap , LCD_COLOR_WHITE, LCD_COLOR_BLACK); 
                }
                if (two_bitmap == 9){
                    lcd_draw_image(RIGHT_BOUND - 180, UPPER_BOUND - 60, numberWidthPixels, 
                    numberHeightPixels, two_bitmap, LCD_COLOR_GREEN, LCD_COLOR_BLACK);
                } else {
                    lcd_draw_image(RIGHT_BOUND - 180, UPPER_BOUND - 60, numberWidthPixels, 
                    numberHeightPixels, two_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);  
                }
                lcd_draw_image(RIGHT_BOUND - 160, UPPER_BOUND - 60, numberWidthPixels,
                numberHeightPixels, colon_bitmap, LCD_COLOR_WHITE, LCD_COLOR_BLACK);
                
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
      /* Initialize mems driver interface */
  uint8_t whoamI, rst;
  uint8_t tx_buffer[1000];
  stmdev_ctx_t dev_ctx;
  lsm6dsm_int1_route_t int_1_reg;
  /* Uncomment if interrupt generation on 6D INT2 pin */
  // lsm6dsm_int2_route_t int_2_reg;
  platform_init();
  platform_delay(15);
  dev_ctx.write_reg = platform_write;
  dev_ctx.read_reg = platform_read;

  /* Check device ID */
  lsm6dsm_device_id_get(&dev_ctx, &whoamI);

  if (whoamI != LSM6DSM_ID)
  {
    printf("Device not found\n\r");
    while (1)
    {
      /* manage here device not found */
    }
  }

  /* Restore default configuration */
  lsm6dsm_reset_set(&dev_ctx, PROPERTY_ENABLE);

  do
  {
    lsm6dsm_reset_get(&dev_ctx, &rst);
  } while (rst);

  /* Set XL Output Data Rate */
  lsm6dsm_xl_data_rate_set(&dev_ctx, LSM6DSM_XL_ODR_416Hz);
  /* Set 2g full XL scale */
  lsm6dsm_xl_full_scale_set(&dev_ctx, LSM6DSM_2g);
  /* Set threshold to 60 degrees */
  lsm6dsm_6d_threshold_set(&dev_ctx, LSM6DSM_DEG_60);
  /* Use HP filter */
  lsm6dsm_xl_hp_path_internal_set(&dev_ctx, LSM6DSM_USE_HPF);
  /* LPF2 on 6D function selection */
  lsm6dsm_6d_feed_data_set(&dev_ctx, LSM6DSM_LPF2_FEED);
  /* Enable interrupt generation on 6D INT1 pin */
  lsm6dsm_pin_int1_route_get(&dev_ctx, &int_1_reg);
  int_1_reg.int1_6d = PROPERTY_ENABLE;
  lsm6dsm_pin_int1_route_set(&dev_ctx, int_1_reg);

  /* Wait Events */
  while (1)
  {
    uint8_t ctrl6_c;
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_CTRL6_C, &ctrl6_c, 1);
    lsm6dsm_write_reg(&dev_ctx, IMU_REG_CTRL6_C, (ctrl6_c & 0xEF), 1);
    int16_t xl;
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTX_H_XL, &xl, 1);
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTX_L_XL, (char *)(&xl) + 1, 1);

    int16_t yl;
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTY_H_XL, &yl, 1);
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTY_L_XL, (char *)(&yl) + 1, 1);

    int16_t zl = 1;
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTZ_H_XL, &zl, 1);
    lsm6dsm_read_reg(&dev_ctx, IMU_REG_OUTZ_L_XL, (char *)(&zl) + 1, 1);

    printf("xl is %i, yl is %i, zl is %i\n", xl, yl, zl);
  }
}
void task_active_init() {
    // /* Wait sensor boot time */
    //xTaskCreate(task_move_paddle, "move paddle", configMINIMAL_STACK_SIZE, NULL, 2, &paddle_task);
    xTaskCreate(task_clear, "Active task", configMINIMAL_STACK_SIZE, NULL, 2, &clear_task);
    xTaskCreate(task_update, "update positions", configMINIMAL_STACK_SIZE, NULL, 2, &update_task);
    //xTaskCreate(task_read_xl, "read xl", configMINIMAL_STACK_SIZE, NULL, 2, &read_xl_task);
}


