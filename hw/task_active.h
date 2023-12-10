/**
 * @file task_active.h
 * @author Han Lyu
 * @brief 
 * @version 0.1
 * @date 2023-12-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TASK_ACTIVE_H__
#define __TASK_ACTIVE_H__
#include "main.h"

extern TaskHandle_t update_task;
extern TaskHandle_t draw_player_task;
extern TaskHandle_t draw_ball_task;
void task_active_init();
#endif