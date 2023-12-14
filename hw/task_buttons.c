/**
 * @file task_buttons.c
 * @author Han Lyu, Adam Boho, Dom Valencia
 * @brief 
 * @version 0.1
 * @date 2023-12-10
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include "task_buttons.h"
extern cyhal_uart_t remote_uart_obj;
TaskHandle_t select_task; 
TaskHandle_t ack_task;
cyhal_gpio_callback_data_t sw1_callback_data;
cyhal_gpio_callback_data_t sw2_callback_data;
//extern score_message_t score_display;
void sw1_handler()
{
    BaseType_t xHigherPriorityTaskWoken;

    /* The xHigherPriorityTaskWoken parameter must be initialized to pdFALSE as
     it will get set to pdTRUE inside the interrupt safe API function if a
     context switch is required. */
    xHigherPriorityTaskWoken = pdFALSE;

    /* ADD CODE */
    /* Send a notification directly to the task to which interrupt processing
     * is being deferred.
     */
    if (!player1_claimed) {
        vTaskNotifyGiveFromISR(select_task, &xHigherPriorityTaskWoken);
        portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
    }

    /* ADD CODE */
    /* Call the function that will force the task that was running prior to the
     * interrupt to yield*/
}

void sw1_irq_enable(void)
{
    sw1_callback_data.callback = sw1_handler;
    cyhal_gpio_register_callback(PIN_SW1, &sw1_callback_data);
    cyhal_gpio_enable_event(PIN_SW1, CYHAL_GPIO_IRQ_FALL, 3, true);
}

void task_select() {
    while (1) {
        printf("called\n");
        ulTaskNotifyTake(true, portMAX_DELAY);
        remote_uart_tx_char_async(CLAIME_PLAYER1);
        remote_uart_tx_char_async('\n');
    }
}
void task_ack() {
    while (1) {
        if (!player1_claimed && ALERT_UART_RX) {
            char msg;
            remote_uart_rx_data_async(&msg, 1);
            ALERT_UART_RX = false;
            if (msg == ACK) {
                player1_claimed = true;
                isplayer1 = true;
                active = true;
                serve_ball = false;
                startTime = time(NULL);
                vTaskDelete(select_task);
                vTaskDelete(ack_task);
            }
            else if (msg == CLAIME_PLAYER1) {
                player1_claimed = true;
                isplayer1 = false;
                active = false;
                startTime = time(NULL);
                remote_uart_tx_char_async(ACK);
                remote_uart_tx_char_async('\n');
                vTaskDelete(select_task);
                vTaskDelete(ack_task);
            }
        }
    }
}
void task_button_init() {
    push_buttons_init();
    sw1_irq_enable();
    lcd_draw_image(
        (SCREEN_X)/2,
        (SCREEN_Y)/2,
        welcomeWidthPixels,
        welcomeHeightPixels,
        welcomeBitmaps,
        LCD_COLOR_GREEN,
        LCD_COLOR_BLACK
    );
    xTaskCreate(task_select, "Select player 1", configMINIMAL_STACK_SIZE, NULL, 3, &select_task);
    xTaskCreate(task_ack, "Confirm player 1", configMINIMAL_STACK_SIZE, NULL, 2, &ack_task);
}