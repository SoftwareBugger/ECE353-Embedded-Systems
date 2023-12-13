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

void task_i2c_init()
{
    i2c_init();

    rslt = cyhal_i2c_master_write(&i2c_monarch_obj, dev_add_7,
    setup_data, 2, 0, true);

    while(1)
    {}
}

void i2c_read_command(uint8_t reg_add)
{
        uint8_t write_data[1] = {reg_add};
        rslt = cyhal_i2c_master_write(&i2c_monarch_obj, dev_add_7,
        write_data, 1, 0, true);

        rslt = cyhal_i2c_master_read(&i2c_monarch_obj, dev_add_7, 
        read_data, 4, 0, true);
}

void task_read_reg()
{
    while(1)
    {
       i2c_read_command(ch1_low);

    }
}

void task_process_data()
{
    while(1)
    {
        uint16_t ch1_data = ((read_data[1] << 8) | read_data[0]);
        uint16_t ch2_data = ((read_data[3] << 8) | read_data[2]);
        printf("%d\n", ch1_data);
        if (ch1_data <= LIGHT_THRESHOLD || ch2_data <= LIGHT_THRESHOLD) light_enable = false;
        else light_enable = true;
    }
}

void task_send_data()
{
    while(1)
    {
        xQueueSend(send_light_queue, &light_enable, portMAX_DELAY);
    }
}

void task_sensor_init()
{
    xTaskCreate(task_i2c_init,
    "I2C Init",
    configMINIMAL_STACK_SIZE, 
    NULL,
    2, &i2c_init_task);

    xTaskCreate(task_read_reg,
    "Read Register",
    configMINIMAL_STACK_SIZE,
    NULL,
    2, &read_reg_task);

    xTaskCreate(task_process_data,
    "Process Data", 
    configMINIMAL_STACK_SIZE,
    NULL,
    2, &process_data_task);

    xTaskCreate(task_send_data,
    "Send Data",
    configMINIMAL_STACK_SIZE,
    NULL,
    2, &send_data_task);


    send_light_queue = xQueueCreate(1, sizeof(light_enable));
}