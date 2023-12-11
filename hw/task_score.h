/**
 * @file task_score.h
 * @author Dominic Valentini
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TASK_SCORE_H__
#define __TASK_SCORE_H__
#include "main.h"

extern TaskHandle_t maintain_score_task;
extern TaskHandle_t draw_score_task;
void task_score_init();

typedef struct score_message_t
{
    uint8_t player_one_score;
    uint8_t player_two_score;
} score_message_t;
#endif
