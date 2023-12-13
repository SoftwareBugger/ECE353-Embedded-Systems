/**
 * @file task_active.h
 * @author Han Lyu, Adam Boho, Dom Valencia
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
extern TaskHandle_t clear_task;
extern TaskHandle_t light_task;
extern bool cleared;
extern bool ball_crossed;
void task_active_init();
#endif