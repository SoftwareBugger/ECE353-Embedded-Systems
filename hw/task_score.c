/**
 * @file task_score.c
 * @author Adam Boho, Han Lyu, Dom Valencia
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_score.h"

void task_score (void *pvParameters) {
    ulTaskNotifyTake(1, portMAX_DELAY);
}


