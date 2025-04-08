#include "graph_class.hpp"
// #include "font8x8.h"
#include "../fonts/font32x53_msb.h"
#include "lcd_lib.hpp"

auto RGB888::to_rgb565() const -> RGB565 {
    return (this->r >> 3) << 11 | (this->g >> 2) << 5 | (this->b >> 3);
}

GraphElement::GraphElement(RGB888 fg_color, RGB888 bg_color)
    : fg_color(fg_color), bg_color(bg_color) {}

auto GraphElement::draw_pixel(int32_t x, int32_t y) const -> void {
    if (x < 0 || x >= LCD_WIDTH || y < 0 || y >= LCD_HEIGHT)
        return;

    lcd_draw_pixel(x, y, this->fg_color.to_rgb565());
}

auto GraphElement::hide() -> void {
    this->swap_fg_bg_color();
    this->draw();
    this->swap_fg_bg_color();
}

auto GraphElement::swap_fg_bg_color() -> void {
    std::swap(this->fg_color, this->bg_color);
}

Pixel::Pixel(Point2D pos, RGB888 fg_color, RGB888 bg_color)
    : GraphElement(fg_color, bg_color), pos(pos) {}

auto Pixel::draw() -> void { this->draw_pixel(this->pos.x, this->pos.y); }

Circle::Circle(Point2D center, int32_t radius, RGB888 fg, RGB888 bg, bool fill)
    : GraphElement(fg, bg), center(center), radius(radius), fill(fill) {}

auto Circle::draw() -> void {
    const int32_t x_center = this->center.x;
    const int32_t y_center = this->center.y;
    const int32_t radius = this->radius;

    if (this->fill) {
        for (int32_t x = -radius; x <= radius; x++)
            for (int32_t y = -radius; y <= radius; y++)
                if (x * x + y * y <= radius * radius)
                    this->draw_pixel(x_center + x, y_center + y);
    } else {
        for (int32_t x = -radius; x <= radius; x++)
            for (int32_t y = -radius; y <= radius; y++)
                if (x * x + y * y <= radius * radius
                    && x * x + y * y >= (radius - 1) * (radius - 1))
                    this->draw_pixel(x_center + x, y_center + y);
    }
}

Character::Character(Point2D pos, char character, RGB888 fg, RGB888 bg)
    : GraphElement(fg, bg), pos(pos), character(character) {}

#define FONT_WIDTH 32
#define FONT_HEIGHT 53
#define FONT_WIDTH_TYPE uint32_t
#define MSB true

auto Character::draw() -> void {
    const auto* const font_pixels = font[static_cast<FONT_WIDTH_TYPE>(
        static_cast<unsigned char>(this->character)
    )];

    for (int32_t i = 0; i < FONT_HEIGHT; i++) {
        const auto row = font_pixels[i];
        for (int32_t j = 0; j < FONT_WIDTH; j++) {
            bool is_set = MSB ? static_cast<bool>(
                                    row >> (FONT_WIDTH - 1 - j) & 0x00000001
                                )
                              : static_cast<bool>(row >> j & 0x00000001);

            if (is_set)
                this->draw_pixel(this->pos.x + j, this->pos.y + i);
        }
    }
}

Line::Line(Point2D pos1, Point2D pos2, RGB888 fg, RGB888 bg)
    : GraphElement(fg, bg), pos1(pos1), pos2(pos2) {}

auto Line::draw() -> void {
    int32_t x1 = this->pos1.x;
    int32_t x2 = this->pos2.x;
    int32_t y1 = this->pos1.y;
    int32_t y2 = this->pos2.y;

    const bool steep = std::abs(y2 - y1) > std::abs(x2 - x1);
    if (steep) {
        std::swap(x1, y1);
        std::swap(x2, y2);
    }

    if (x1 > x2) {
        std::swap(x1, x2);
        std::swap(y1, y2);
    }

    const int32_t dx = x2 - x1;
    const int32_t dy = std::abs(y2 - y1);
    int32_t error = dx / 2;
    const int32_t ystep = (y1 < y2) ? 1 : -1;
    int32_t y = y1;

    for (int32_t x = x1; x <= x2; x++) {
        if (steep)
            this->draw_pixel(y, x);
        else
            this->draw_pixel(x, y);

        error -= dy;
        if (error < 0) {
            y += ystep;
            error += dx;
        }
    }
}
