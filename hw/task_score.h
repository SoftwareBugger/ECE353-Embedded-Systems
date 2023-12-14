/**
 * @file task_score.h
 * @author Adam Boho, Han Lyu, Dom Valentini
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TASK_SCORE_H__
#define __TASK_SCORE_H__
#include "main.h"

extern TaskHandle_t maintain_score_task;
extern TaskHandle_t draw_score_task;
extern time_t deltTime;
void task_score_init();

typedef struct score_message_t
{
    uint8_t player_one_score;
    uint8_t player_two_score;
} score_message_t;
#endif
