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
#ifndef __TASK_INACTIVE_H__
#define __TASK_INACTIVE_H__
#include "main.h"

typedef struct TurnInfo {
    uint16_t ballX;
    uint16_t balldx;
    uint16_t balldy;
};
#define portMAX_DELAY             ( TickType_t ) 0xffffffffUL
#endif
