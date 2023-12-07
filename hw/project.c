/**
 * @file hw02.c
 * @author Dominic Valentini (dvalentini@wisc.edu)
 * @author Adam Boho (boho2@wisc.edu)
 * @author Han Lyu (hlyu42@wisc.edu)
 * @brief
 * @version 0.1
 * @date 2023-09-16
 *
 * @copyright Copyright (c) 2023
 *
 */
#include "main.h"
#include "project.h"


/*****************************************************************************/
/*  Global Variables                                                         */
/*****************************************************************************/
char PROJ_DESCRIPTION[] = "ECE353: Project; Dominic Valentini, Adam Boho, Han Lyu";
// timer objects and uart object
cyhal_timer_t proj_timer_obj;
cyhal_timer_cfg_t proj_timer_cfg;
extern cyhal_uart_t proj_remote_uart;
// cyhal results
cy_rslt_t proj_rslt;

bool joystick_enabled;
bool two_player;

// MOVE TO INDIVIDUAL TASK FILES 
TaskHandle_t active_task;
void task_active(void *pvParameters);
TaskHandle_t send_task;
void task_send(void *pvParamaters);
TaskHandle_t inactive_task;
void task_inactive(void *pvParameters);
TaskHandle_t score_task;
void task_score(void *pvParameters);
TaskHandle_t draw_task;
void task_draw(void *pvParameters);

QueueHandle_t position_queue;




/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
void proj_timer_handler(void)
{
    
}
void proj_main_app(void)
{
    position_queue = xQueueCreate(1, sizeof(coord));

    xTaskCreate(active_task, "Active", configMINIMAL_STACK_SIZE, NULL, 2, NULL);

}

void proj_periph_init(void)
{
    // initialize push buttons
    push_buttons_init();

    // initialize LCD
    ece353_enable_lcd();

    // initialize joystick
    joystick_init();

    // initialize remote UART
    remote_uart_init();
    remote_uart_enable_interrupts();

    // initialize timer, 10ms
    timer_init(&proj_timer_obj, &proj_timer_cfg, 1000000, proj_timer_handler);

    // initialize imu
    platform_init();

    // initialize i2c
    i2c_init();
}

void proj_collision_handler(ball ball, player player)
{
    // if ball hits player, change y direction
    if (ball.y_pos == PLAYER_ALT + 1 && ball.x_pos > player.x_pos_left && ball.x_pos < player.x_pos_right)
    {
        ball.y_pos  == -1 * ball.y_pos;
    }
}