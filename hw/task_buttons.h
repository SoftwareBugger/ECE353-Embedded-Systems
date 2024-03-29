/**
 * @file task_buttons.h
 * @author Han Lyu, Adam Boho, Dom Valencia
 * @brief Selects role of the players
 * @version 0.1
 * @date 2023-12-09
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TASK_SELECT_H__
#define __TASK_SELECT_H__
#include "main.h"
extern TaskHandle_t select_task; 
extern TaskHandle_t ack_task;
void task_button_init();
void task_ack();

#endif
