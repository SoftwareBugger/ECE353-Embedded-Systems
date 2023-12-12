/**
 * @file task_score.c
<<<<<<< HEAD
 * @author Adam Boho, Han Lyu, Dom Valentini
 * @brief 
 * @version 0.1
 * @date 2023-08-25
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_score.h"
#include "lcd_images.h"
extern cyhal_uart_t remote_uart_obj;
TaskHandle_t maintain_score_task;
TaskHandle_t send_score_task;
score_message_t score_message;
QueueHandle_t inactive_queue;
QueueHandle_t active_queue;
extern QueueHandle_t send_score_queue;
extern QueueHandle_t point_registered_queue;
bool registered_score;
uint8_t player_one_ = 0;
uint8_t player_two_ = 0;



void task_maintain_score()
{
    while(1)
    {
        // If registered score is a 0, it means player two has scored and should be sent from the active task
        // IF registered score is a 1, it means player one has scored and should be sent from the inactive task
        xQueueReceive(point_registered_queue, &registered_score, portMAX_DELAY);
        if (registered_score)
        {
            player_one_ = score_message.player_one_score + 1;
        }
        else
        {
            player_two_ = score_message.player_two_score + 1;
        }
    }
}

void task_send_score()
{   
    while(1)
    {
        score_message.player_one_score = player_one_;
        score_message.player_two_score = player_two_;
        xQueueSend(send_score_queue, &score_message, 5);
    }
}

void task_score_init()
{
    xTaskCreate(task_maintain_score, 
    "Maintain Score", 
    configMINIMAL_STACK_SIZE, 
    NULL, 
    2, &maintain_score_task);

    xTaskCreate(task_send_score, 
    "Send Score", 
    configMINIMAL_STACK_SIZE,
    NULL, 
    2, &send_score_task);

    send_score_queue = xQueueCreate(1, sizeof(score_message_t));
    point_registered_queue = xQueueCreate(1, sizeof(registered_score));
}

