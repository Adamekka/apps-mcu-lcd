#ifndef LCD_LIB_HPP
#define LCD_LIB_HPP

#include "graph_class.hpp"
#include <opencv2/opencv.hpp>

#define LCD_WIDTH 320
#define LCD_HEIGHT 320
#define LCD_NAME "Virtual LCD"

extern cv::Mat lcd_canvas;

void lcd_init();

void lcd_draw_pixel(int32_t x, int32_t y, RGB565 rgb_565);

#endif
