#include "lcd_lib.hpp"
#include <opencv2/opencv.hpp>

cv::Mat lcd_canvas(cv::Size(LCD_WIDTH, LCD_HEIGHT), CV_8UC3);

void lcd_init() {
    cv::namedWindow(LCD_NAME, 0);
    cv::Vec3b black(0, 0, 0);
    lcd_canvas.setTo(black);

    cv::waitKey(1);
}

void lcd_draw_pixel(int32_t t_x, int32_t t_y, uint16_t t_rgb_565) {
    cv::Vec3b rgb_888(
        (t_rgb_565 & 0x1F) << 3,
        ((t_rgb_565 >> 5) & 0x3F) << 2,
        ((t_rgb_565 >> 11) & 0x1F) << 3
    );
    lcd_canvas.at<cv::Vec3b>(t_y, t_x) = rgb_888; // Draw pixel
}
