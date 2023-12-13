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
// cyhal_timer_t proj_timer_obj;
// cyhal_timer_cfg_t proj_timer_cfg;
extern cyhal_uart_t remote_uart_obj;
// cyhal results
cy_rslt_t proj_rslt;

bool joystick_enabled;
volatile bool active;
bool player1_claimed;
bool serve_ball;
bool isplayer1;
bool gameOver = false;
// Player player;
// Ball ball;
uint16_t playerX;
uint16_t playerY;
uint16_t ballX;
uint8_t ballY;
int8_t balldx;
int8_t balldy;
int16_t angle;

// MOVE TO INDIVIDUAL TASK FILES 

QueueHandle_t position_queue;
QueueHandle_t player_selection_queue;
QueueHandle_t send_score_queue;
QueueHandle_t point_registered_queue;
QueueHandle_t send_light_queue;

uint16_t activeScore = 0;
uint16_t inactiveScore = 0;


/*****************************************************************************/
/*  Interrupt Handlers                                                       */
/*****************************************************************************/
// void proj_timer_handler(void)
// {
    
// }
void proj_main_app(void)
{
    player_selection_queue = xQueueCreate(1, sizeof(bool));
    position_queue = xQueueCreate(1, 50);
    player1_claimed = false;
    isplayer1 = false;
    playerX = paddleLeftWidthPixels/2 + 1;
    playerY = SCREEN_Y/2;
    ballX = paddleLeftWidthPixels + 10 + ballWidthPixels/2;
    ballY = SCREEN_Y/2;
    balldx = 1;
    balldy = 1;

    // Player player = {
    //     .x_pos_center = SCREEN_X/2,//paddleLeftHeightPixels/2,
    //     .y_pos_center = SCREEN_Y/3
    // };
    // Ball ball = {
    //     .speed = 3,
    //     .x_pos_center = 
    // };
    // task_draw_init();
    srand(time(NULL));
    task_button_init();
    //player1_claimed = true;
    //active = true;
    task_active_init();
    task_inactive_init();
    task_score_init();
    task_sensor_init();
    vTaskStartScheduler();

    while (1)
    {
    };

}

void proj_periph_init(void)
{
    // initialize push buttons

    // initialize LCD
    ece353_enable_lcd();

    // initialize joystick
    joystick_init();

    // initialize remote UART
    remote_uart_init();
    remote_uart_enable_interrupts();

    // initialize spi

    // // /* Init test platform */

    // initialize i2c
    
}

//*****************************************************************************
//
//! \brief Application defined malloc failed hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationMallocFailedHook()
{
    /* Handle Memory Allocation Errors */
    while (1)
    {
    }
}

//*****************************************************************************
//
//! \brief Application defined stack overflow hook
//!
//! \param  none
//!
//! \return none
//!
//*****************************************************************************
void vApplicationStackOverflowHook(TaskHandle_t pxTask, char *pcTaskName)
{
    // Handle FreeRTOS Stack Overflow
    while (1)
    {
    }
}