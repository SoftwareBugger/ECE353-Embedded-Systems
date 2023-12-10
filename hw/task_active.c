#include "task_active.h"

TaskHandle_t update_task;
TaskHandle_t draw_player_task;
TaskHandle_t draw_ball_task;
bool cleared = false;
int offset = SCREEN_X/8;
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
            }         
            lcd_draw_image(ballX, ballY, ballHeightPixels, ballWidthPixels, ballBitmaps, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
            uint16_t fcolor = LCD_COLOR_BLUE;
            if (isplayer1) fcolor = LCD_COLOR_RED;
            lcd_draw_image(playerX, playerY, paddleLeftHeightPixels, paddleLeftWidthPixels, paddleLeftBitmaps, fcolor, LCD_COLOR_BLACK);
        }
    }
}
void task_draw_player(void *pvParameters) {
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

void task_active_init() {
    xTaskCreate(task_draw_player, "Active task", configMINIMAL_STACK_SIZE, NULL, 2, &draw_player_task);
    xTaskCreate(task_update, "update positions", configMINIMAL_STACK_SIZE, NULL, 2, &update_task);
}