#include "task_eeprom.h"
TaskHandle_t eeprom_task;
void task_eeprom() {
    while (1) {
        eeprom_cs_init();

    }
}
void task_eeprom_init() {
    //xTaskCreate(task_eeprom, "eeprom task", configMINIMAL_STACK_SIZE, NULL, 2, &eeprom_task);
}