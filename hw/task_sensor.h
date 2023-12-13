/**
 * @file task_sensor.h
 * @author Dominic Valentini
 * @brief 
 * @version 0.1
 * @date 2023-12-11
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#ifndef __TASK_SENSOR_H__
#define __TASK_SENSOR_H__

#define LIGHT_THRESHOLD     20
                            

#include "main.h"

extern TaskHandle_t read_reg_task;
extern TaskHandle_t process_data_task;
extern TaskHandle_t send_data_task;
extern TaskHandle_t i2c_init_task;


void task_sensor_init();
void i2c_read_command(uint8_t reg_add);


#endif