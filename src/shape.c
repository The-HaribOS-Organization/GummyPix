#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "shape.h"


void draw_point(image_t *image, point_t point, pixels_t color) {

    if (point.x < 0 || point.x >= image->width || point.y < 0 || point.y >= image->height) return;
    image->data[point.y * image->width + point.x] = color;
}

void draw_line(image_t *image, line_t line) {

    int32_t dx = abs(line.end.x - line.start.x), dy = -abs(line.end.y - line.start.y);
    int32_t sx = (line.start.x < line.end.x) ? 1 : -1, sy = (line.start.y < line.end.y) ? 1 : -1;
    int32_t error = dx + dy;

    while (true) {

        draw_point(image, line.start, line.color);
        int32_t e2 = 2 * error;
        if (e2 >= dy) {

            if (line.start.x == line.end.x) break;
            error += dy;
            line.start.x += sx;
        }

        if (e2 <= dx) {

            if (line.start.y == line.end.y) break;
            error += dx;
            line.start.y += sy;
        }
    }

    return;
}

void draw_rectangle(image_t *image, rectangle_t rectangle) {

    if (!rectangle.filled) {

        for (uint32_t i = 0; i < rectangle.thickness; i++) {

            uint32_t dx = rectangle.dimension.x - rectangle.position.x, dy = rectangle.dimension.y - rectangle.position.y;

            draw_line(image, (line_t){(point_t){rectangle.position.x - i, rectangle.position.y - i}, (point_t){rectangle.position.x + dx - i, rectangle.position.y - i}, rectangle.color});
            draw_line(image, (line_t){(point_t){rectangle.position.x - i, rectangle.position.y + dy - i}, (point_t){rectangle.position.x + dx - i, rectangle.position.y + dy - i}, rectangle.color});
            draw_line(image, (line_t){(point_t){rectangle.position.x - i, rectangle.position.y - i}, (point_t){rectangle.position.x - i, rectangle.position.y + dy - i}, rectangle.color});
            draw_line(image, (line_t){(point_t){rectangle.position.x + dx - i, rectangle.position.y - i}, (point_t){rectangle.position.x + dx - i, rectangle.position.y + dy - i}, rectangle.color});
        }

    } else {

        for (uint32_t y = rectangle.position.y; y < rectangle.dimension.y; y++) {
            for (uint32_t x = rectangle.position.x; x < rectangle.dimension.x; x++) draw_point(image, (point_t){x, y}, rectangle.color);
        }
    }

    return;
}

void draw_shape(image_t *image, shape_t *shape) {

    for (uint32_t i = 0; i < shape->nb_points; i++) {

        if (i == shape->nb_points - 1) draw_line(image, (line_t){shape->points[i], shape->points[0], shape->color});
        draw_line(image, (line_t){shape->points[i], shape->points[i+1], shape->color});
    }

    return;
}
