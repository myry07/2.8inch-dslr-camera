#include <stdio.h>
#include "adapter_lcd.h"
#include "st7789.h"
#include "cst816s.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "esp_log.h"

#define LCD_WIDTH 240
#define LCD_HEIGHT 198
#define SPI_MOSI_GPIO 10
#define SPI_SCLK_GPIO 9
#define SPI_CS_GPIO 13
#define LCD_DC_GPIO 12
#define LCD_RESET_GPIO 11
#define LCD_BL_GPIO 14

void lcd1_init(void)
{
    TFT_t dev;
    spi_master_init(&dev, SPI_MOSI_GPIO, SPI_SCLK_GPIO,
                    SPI_CS_GPIO, LCD_DC_GPIO, LCD_RESET_GPIO, LCD_BL_GPIO);
    lcdInit(&dev, LCD_WIDTH, LCD_HEIGHT, 0, 0, DIRECTION270);
    lcdFillScreen(&dev, BLACK);
    lcdDrawFillRect(&dev, 0, 0, 90, 90, RED);     // 左上
    // lcdDrawFillRect(&dev, 200, 0, 20, 20, GREEN); // 右上
    // lcdDrawFillRect(&dev, 0, 100, 20, 20, BLUE);  // 左下
    // lcdDrawFillRect(&dev, 200, 100, 20, 20, YELLOW);
}
