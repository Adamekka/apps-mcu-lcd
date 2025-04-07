#include "lcd_lib.hpp"

auto main() -> int32_t {
    lcd_init();

    Circle circle(
        Point2D{.x = LCD_WIDTH / 2, .y = LCD_HEIGHT / 2},
        50,
        RGB888{.r = 255, .g = 0, .b = 0},
        RGB888{.r = 0, .g = 0, .b = 0},
        false
    );
    circle.draw();

    Line line(
        Point2D{.x = 0, .y = 0},
        Point2D{.x = LCD_WIDTH / 2, .y = LCD_HEIGHT - 1},
        RGB888{.r = 0, .g = 0, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    line.draw();

    Character n(
        Point2D{.x = 0, .y = 20},
        'N',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    n.draw();
    Character i(
        Point2D{.x = 20, .y = 20},
        'I',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    i.draw();
    Character g1(
        Point2D{.x = 40, .y = 20},
        'G',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    g1.draw();
    Character g2(
        Point2D{.x = 60, .y = 20},
        'G',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    g2.draw();
    Character e(
        Point2D{.x = 80, .y = 20},
        'E',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    e.draw();
    Character r(
        Point2D{.x = 100, .y = 20},
        'R',
        RGB888{.r = 255, .g = 255, .b = 255},
        RGB888{.r = 0, .g = 0, .b = 0}
    );
    r.draw();

    cv::imshow(LCD_NAME, lcd_canvas);
    cv::waitKey(0);
}
