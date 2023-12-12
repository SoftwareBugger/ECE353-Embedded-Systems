/**
 * @file task_inactive.h
 * @author Adam Boho, Han Lyu, Dom Valentini
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_inactive.h"
extern score_message_t score_display;
TaskHandle_t inactive_task;
void task_update_inactive() {
    uint8_t score[2];
    while (1) {
        if (!active && player1_claimed && !ball_crossed) {
            int8_t data[4];
            if (ALERT_UART_RX) {
                memset(data, 0, 4);
                remote_uart_rx_data_async(data, 4);
                ALERT_UART_RX = false;
                balldx = data[0];
                balldy = data[1] - 6;
                ballY = (uint8_t)data[2];
                if (isplayer1) {
                    score_display.player_one_score = data[3];
                }
                else {
                    score_display.player_two_score = data[3];
                }
                ballX = SCREEN_X - ballWidthPixels/2 - 5;
                printf("balldx :%i, balldy :%i, ballY :%u, ballX :%u\n", balldx, balldy, ballY, ballX);
                active = true;
                ball_crossed = true;
            }
        }
    }
}
void task_inactive_init() {
    xTaskCreate(task_update_inactive, "update task inactive", configMINIMAL_STACK_SIZE, NULL, 2, &inactive_task);
}