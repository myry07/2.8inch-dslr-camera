#include <stdio.h>
#include "st7789.h"
#include "cst816t.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define I2C_SDA     5
#define I2C_SCL     4
#define TOUCH_RST   15

void app_main(void)
{
    TFT_t dev;
    spi_master_init(&dev, SPI_MOSI_GPIO, SPI_SCLK_GPIO,
                    SPI_CS_GPIO, LCD_DC_GPIO, LCD_RESET_GPIO, LCD_BL_GPIO);
    lcdInit(&dev, LCD_WIDTH, LCD_HEIGHT, 0, 20);
    lcdFillScreen(&dev, CYAN);
    lcdDrawFillRect(&dev, 100, 100, 140, 140, RED);

    gpio_config_t rst_conf = {
        .pin_bit_mask = 1ULL << TOUCH_RST,
        .mode = GPIO_MODE_OUTPUT,
        .pull_up_en = GPIO_PULLUP_DISABLE,
        .pull_down_en = GPIO_PULLDOWN_DISABLE,
        .intr_type = GPIO_INTR_DISABLE
    };
    gpio_config(&rst_conf);
    gpio_set_level(TOUCH_RST, 0);
    vTaskDelay(pdMS_TO_TICKS(10));
    gpio_set_level(TOUCH_RST, 1);
    vTaskDelay(pdMS_TO_TICKS(200));

    cst816t_cfg_t touch_cfg = {
        .sda = I2C_SDA,
        .scl = I2C_SCL,
        .fre = 200*1000,
        .x_limit = LCD_WIDTH,
        .y_limit = LCD_HEIGHT,
    };
    cst816t_init(&touch_cfg);

    // 触摸轮询主循环
    while (1)
    {
        int16_t x = 0, y = 0;
        int state = 0;
        cst816t_read(&x, &y, &state);
        ESP_LOGI("main", "x: %u, y: %u, state: %d", x, y ,state);

        if (state)
        {
            ESP_LOGI("TOUCH", "Touch at: x=%d, y=%d", x, y);
            lcdDrawFillCircle(&dev, x, y, 10, RED);
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}
