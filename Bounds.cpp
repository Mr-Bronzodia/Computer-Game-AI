#include "Bounds.h"
#include <iostream>
#include "raylib.h"

aipfg::Bounds::Bounds(Vector2& center_point, Vector2& extends) : centre {center_point}, extend {extends}
{
    set_bounding_centre(center_point);
}

bool aipfg::Bounds::is_inside(Vector2& point)
{
    bool is_below_top = point.x > top_point.x && point.y < top_point.y;
    bool is_above_bottom = point.x < botom_point.x && point.y > botom_point.y;

    return is_above_bottom && is_below_top;
}

bool aipfg::Bounds::do_overlap(Bounds* other)
{
    if (other->extend.x == 0 || other->extend.y == 0) return false;

    Bounds* smaller_rect{};
    Bounds* larger_rect{};

    if (other->get_area() > get_area()) {
        larger_rect = other;
        smaller_rect = this;
    }
    else {
        larger_rect = this;
        smaller_rect = other;
    }

    Vector2 NW{ smaller_rect->top_point };
    Vector2 SW{ smaller_rect->top_point.x, smaller_rect->top_point.y - smaller_rect->extend.y * 2 };
    Vector2 SE{ smaller_rect->botom_point };
    Vector2 NE{ smaller_rect->botom_point.x, smaller_rect->botom_point.y + smaller_rect->extend.y * 2 };

    return larger_rect->is_inside(NW) || larger_rect->is_inside(SW) || larger_rect->is_inside(SE) || larger_rect->is_inside(NE);
}

void aipfg::Bounds::debug_draw(bool is_collision_bounds)
{
    Vector2 NW{ top_point };
    Vector2 SW{ top_point.x, top_point.y - extend.y * 2 };
    Vector2 SE{ botom_point };
    Vector2 NE{ botom_point.x, botom_point.y + extend.y * 2 };

    if (is_collision_bounds) {
        DrawLineV(NW, NE, RED);
        DrawLineV(NE, SE, RED);
        DrawLineV(SE, SW, RED);
        DrawLineV(SW, NW, RED);
    }
    else
    {
        DrawLineV(NW, NE, GREEN);
        DrawLineV(NE, SE, GREEN);
        DrawLineV(SE, SW, GREEN);
        DrawLineV(SW, NW, GREEN);
    }
    
}

void aipfg::Bounds::set_bounding_centre(Vector2& center_point)
{
    top_point = Vector2{ center_point.x - extend.x, center_point.y + extend.y };
    botom_point = Vector2{ center_point.x + extend.x, center_point.y - extend.y };
    centre = center_point;
}


Vector2 aipfg::Bounds::get_bounding_centre()
{
    return centre;
}

float aipfg::Bounds::get_area()
{
    return (extend.x * 2) * (extend.y * 2);
}


