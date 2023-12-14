#include "task_eeprom.h"
TaskHandle_t eeprom_task;
extern score_message_t score_display;
uint16_t addr = 0x0000;
void task_eeprom() {
    spi_init();
    while (1) {
        ulTaskNotifyTake(true, 5);
        if (gameOver) {
            eeprom_cs_init();
            eeprom_write_byte(addr, score_display.player_one_score*16+score_display.player_two_score*16);
        }
        else if (!player1_claimed && !read_last_score) {
            eeprom_cs_init();
            uint8_t lastscore = eeprom_read_byte(addr);
            score_display.player_one_score = lastscore >> 4;
            score_display.player_two_score = lastscore % 16;
            printf("1 :%u 2 :%u\n", lastscore >> 4, lastscore % 16);
            uint8_t *one_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_one_score]];
            uint8_t *two_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[score_display.player_two_score]];
            uint8_t *colon_bitmap = (uint8_t *)&proj_num_bitmaps[proj_num_offset[10]];
            lcd_draw_image(SCREEN_X/2 - 20, UPPER_BOUND/2 + 50, numberWidthPixels, 
            numberHeightPixels, one_bitmap , LCD_COLOR_BLUE, LCD_COLOR_BLACK);
            lcd_draw_image(SCREEN_X/2 + 20, UPPER_BOUND/2 + 50, numberWidthPixels, 
            numberHeightPixels, two_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
            lcd_draw_image(SCREEN_X/2, UPPER_BOUND/2 + 50, numberWidthPixels,
            numberHeightPixels, colon_bitmap, LCD_COLOR_BLUE, LCD_COLOR_BLACK);
            read_last_score = true;
        }
        else vTaskDelay(0);
    }
}
void task_eeprom_init() {
    xTaskCreate(task_eeprom, "eeprom task", configMINIMAL_STACK_SIZE, NULL, 2, &eeprom_task);
}