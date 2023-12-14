#include "task_sensor.h"
#include "lcd_images.h"

extern cyhal_i2c_t i2c_monarch_obj;
extern cy_rslt_t rslt;
TaskHandle_t read_reg_task;
TaskHandle_t process_data_task;
TaskHandle_t send_data_task;
TaskHandle_t i2c_init_task;

uint8_t read_data[4];

uint8_t dev_add_7 = 0x29; // 010 1001

uint8_t ch1_low = 0x88;
uint8_t ch1_high = 0x89;
uint8_t ch0_low = 0x8A;
uint8_t ch0_high = 0x8B;


bool light_enable;

extern QueueHandle_t send_light_queue;

//setup register, setup data
uint8_t setup_data[2] = {0x80, 0x01};

void i2c_read_command(uint8_t reg_add)
{
        uint8_t write_data[1] = {reg_add};
        rslt = cyhal_i2c_master_write(&i2c_monarch_obj, dev_add_7,
        write_data, 1, 0, true);

        rslt = cyhal_i2c_master_read(&i2c_monarch_obj, dev_add_7, 
        read_data, 4, 0, true);
}

void task_process_data()
{

    rslt = cyhal_i2c_master_write(&i2c_monarch_obj, dev_add_7,
    setup_data, 2, 0, true);
    while(1)
    {
        if (!gameOver) {
            i2c_read_command(ch1_low);
            uint16_t ch1_data = ((read_data[1] << 8) | read_data[0]);
            uint16_t ch2_data = ((read_data[3] << 8) | read_data[2]);
            if (ch1_data <= LIGHT_THRESHOLD || ch2_data <= LIGHT_THRESHOLD) light_enable = false;
            else light_enable = true;
            xQueueSend(send_light_queue, &light_enable, 5);
        }
        else vTaskDelay(0);
    }
}

void task_sensor_init()
{
    xTaskCreate(task_process_data,
    "Process Data", 
    configMINIMAL_STACK_SIZE,
    NULL,
    2, &process_data_task);

    send_light_queue = xQueueCreate(1, sizeof(light_enable));
}