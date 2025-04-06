#ifndef GRAPH_CLASS_HPP
#define GRAPH_CLASS_HPP

#include <cstdint>

class Point2D {
  public:
    int32_t x, y;
};

using RGB565 = uint16_t;

class RGB888 {
  public:
    uint8_t r, g, b;

    [[nodiscard]] auto to_rgb565() const -> RGB565;
};

class GraphElement {
  public:
    RGB888 fg_color, bg_color;

    GraphElement(RGB888 fg_color, RGB888 bg_color);
    GraphElement(const GraphElement&) = default;
    GraphElement(GraphElement&&) noexcept = delete;

    virtual ~GraphElement() = default;

    auto operator=(const GraphElement&) -> GraphElement& = default;
    auto operator=(GraphElement&&) noexcept -> GraphElement& = delete;

    // ONLY ONE INTERFACE WITH LCD HARDWARE!!!
    auto draw_pixel(int32_t x, int32_t y) const -> void;

    virtual auto draw() -> void = 0;
    auto hide() -> void;

  private:
    auto swap_fg_bg_color() -> void;
};

class Pixel : public GraphElement {
  public:
    Point2D pos;

    Pixel(Point2D pos, RGB888 fg_color, RGB888 bg_color);

    auto draw() -> void final;
};

class Circle : public GraphElement {
  public:
    Point2D center;
    int32_t radius;

    Circle(Point2D center, int32_t radius, RGB888 fg, RGB888 bg);

    auto draw() -> void final;
};

class Character : public GraphElement {
  public:
    Point2D pos;
    char character;

    Character(Point2D pos, char character, RGB888 fg, RGB888 bg);

    auto draw() -> void final;
};

class Line : public GraphElement {
  public:
    Point2D pos1, pos2;

    Line(Point2D pos1, Point2D pos2, RGB888 fg, RGB888 bg);

    auto draw() -> void final;
};

#endif
