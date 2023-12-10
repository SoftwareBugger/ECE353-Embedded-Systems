/**
 * @file task_score.c
 * @author Dominic Valentini
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_score.h"
#include "lcd_images.h"
extern cyhal_uart_t remote_uart_obj;
TaskHandle_t maintain_score_task;
TaskHandle_t draw_score_task;
int player_one_score;
int player_two_score;
QueueHandle_t inactive_queue;
QueueHandle_t active_queue;

void task_maintain_score()
{
    while(1)
    {

    }
}

void task_draw_score()
{
    // while(1)
    // {
    //         lcd_draw_image(LEFT_BOUND + 40, UPPER_BOUND - 40 , 
    //         numberWidthPixels, numberHeightPixels, &zero_bitmaps, LCD_COLOR_ORANGE, LCD_COLOR_BLACK);
    // }
}

void task_score_init()
{
    xTaskCreate(task_maintain_score, 
    "Maintain Score", 
    configMINIMAL_STACK_SIZE, 
    NULL, 
    2, &maintain_score_task);

    xTaskCreate(task_draw_score, 
    "Draw Score", 
    configMINIMAL_STACK_SIZE,
    NULL, 
    2, &draw_score_task);
}