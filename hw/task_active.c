#include "task_active.h"
#include "lcd_images.h"

TaskHandle_t update_task;
TaskHandle_t draw_task;
TaskHandle_t read_xl_task;
bool cleared = false;
int offset = SCREEN_X/8;
<<<<<<< HEAD
stmdev_ctx_t dev_ctx;
=======

extern QueueHandle_t send_score_queue;
score_message_t score_display;
uint8_t bitmap_one[];
uint8_t bitmap_two[];


>>>>>>> e6e7a55179bc56e2f88ca3cd0a40d767e98fd853
void task_update(void *pvParameters) {
    while (1) {
        static uint8_t counter = 0;
        counter = (counter + 1)%1;
        if (player1_claimed && cleared) {
            if (!serve_ball) {
                balldy = (rand() % 3);
                serve_ball = true;
            }
            else if (ballX - playerX <= (5 + (ballWidthPixels + paddleLeftWidthPixels)/2) 
                  && ballX - playerX >= -(5 + (ballWidthPixels + paddleLeftWidthPixels)/2)  
                  && ballY - playerY <= (5 + (ballHeightPixels + paddleLeftHeightPixels)/2)
                  && ballY - playerY >= -(5 + (ballHeightPixels + paddleLeftHeightPixels)/2)) {
                    balldy = (rand() % 3);
                    balldx = -balldx;
                  }
            else if (ballX <= ballWidthPixels/2 + 2 || ballX >= SCREEN_X - ballWidthPixels/2 - 2) balldx = -balldx;
            else if (ballY <= ballHeightPixels/2 + 2 || ballY >= SCREEN_Y - ballHeightPixels/2 - 2) balldy = -balldy;
            if (counter == 0) {
                ballX = ballX + balldx;
                ballY = ballY + balldy;
                xTaskNotifyGive(draw_task);
            }         
            lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
            uint16_t fcolor = LCD_COLOR_BLUE;
            if (isplayer1) fcolor = LCD_COLOR_RED;
            lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, fcolor, LCD_COLOR_BLACK);


        }
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
    }
}
void task_draw(void *pvParameters) {
    while (1) {
        if (player1_claimed) {
            if (!cleared) 
            {
                lcd_clear_screen(LCD_COLOR_BLACK);
                cleared = true;
            }
            else {
            }
        }
    }
}
void task_read_xl(void *pvParameters) {
    while (1) {
        printf("here\n");
        lsm6dsm_orientation();
        printf("here hhh\n");
    }
}
void task_active_init() {
    xTaskCreate(task_draw, "Active task", configMINIMAL_STACK_SIZE, NULL, 2, &draw_task);
    xTaskCreate(task_update, "update positions", configMINIMAL_STACK_SIZE, NULL, 2, &update_task);
<<<<<<< HEAD
    xTaskCreate(task_read_xl, "read xl", configMINIMAL_STACK_SIZE, NULL, 2, &read_xl_task);
}
=======
}

>>>>>>> e6e7a55179bc56e2f88ca3cd0a40d767e98fd853
