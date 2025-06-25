#include <stdio.h>
#include "adapter_lcd.h"

#define I2C_SDA     5
#define I2C_SCL     4
#define TOUCH_RST   15

void app_main(void)
{
    lcd1_init();

    // cst816s_cfg_t cfg = {
    //     .sda = I2C_SDA,
    //     .scl = I2C_SCL,
    //     .fre = 400000,
    //     .x_limit = LCD_WIDTH,
    //     .y_limit = LCD_HEIGHT
    // };
    // cst816s_init(&cfg);

    // while (1) {
    //     int16_t x, y;
    //     int state;
    //     cst816s_read(&x, &y, &state);
    //     if (state) {
    //         ESP_LOGI("TOUCH", "Touch: (%d, %d)", x, y);
    //         lcdDrawFillCircle(&dev, x, y, 5, RED);
    //     }
    //     vTaskDelay(pdMS_TO_TICKS(50));
    // }
}