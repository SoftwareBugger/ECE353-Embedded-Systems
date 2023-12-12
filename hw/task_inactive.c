/**
 * @file task_inactive.h
 * @author Adam Boho, Han Lyu, Dom Valencia
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_inactive.h"
extern QueueHandle_t position_queue;
void task_inactive (void *pvParamaters) {
    char* data;
    remote_uart_rx_interrupts_init();
    remote_uart_rx_data_async(&data, 100);
    struct TurnInfo turnInfo;
    data = strtok(NULL, ",");
    turnInfo.ballX = data;
    data = strtok(NULL, ",");
    turnInfo.balldx = data;
    data = strtok(NULL, ",");
    turnInfo.balldy = data; 
    xQueueSend(&position_queue, &turnInfo, portMAX_DELAY );
}