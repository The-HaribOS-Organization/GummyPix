#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "utils.h"
#include "shape.h"
#include "image.h"


void gp_draw_point(gp_image_t *image, gp_point_t point, gp_pixels_t color) {

    if (point.x < 0 || point.x >= image->dimension.x || point.y < 0 || point.y >= image->dimension.y) return;
    image->data[point.y * image->dimension.x + point.x] = color;
}

void gp_draw_line(gp_image_t *image, gp_line_t line) {

    int32_t dx = abs(line.end.x - line.start.x), dy = -abs(line.end.y - line.start.y);
    int32_t sx = (line.start.x < line.end.x) ? 1 : -1, sy = (line.start.y < line.end.y) ? 1 : -1;
    int32_t error = dx + dy;

    while (true) {

        gp_draw_point(image, line.start, line.color);
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

void gp_draw_rectangle(gp_image_t *image, gp_rectangle_t rectangle) {

    if (!rectangle.filled) {

        for (uint32_t i = 0; i < rectangle.thickness; i++) {

            uint32_t dx = rectangle.dimension.x - rectangle.position.x, dy = rectangle.dimension.y - rectangle.position.y;

            gp_draw_line(image, (gp_line_t){(gp_point_t){rectangle.position.x - i, rectangle.position.y - i}, (gp_point_t){rectangle.position.x + dx - i, rectangle.position.y - i}, rectangle.color});
            gp_draw_line(image, (gp_line_t){(gp_point_t){rectangle.position.x - i, rectangle.position.y + dy - i}, (gp_point_t){rectangle.position.x + dx - i, rectangle.position.y + dy - i}, rectangle.color});
            gp_draw_line(image, (gp_line_t){(gp_point_t){rectangle.position.x - i, rectangle.position.y - i}, (gp_point_t){rectangle.position.x - i, rectangle.position.y + dy - i}, rectangle.color});
            gp_draw_line(image, (gp_line_t){(gp_point_t){rectangle.position.x + dx - i, rectangle.position.y - i}, (gp_point_t){rectangle.position.x + dx - i, rectangle.position.y + dy - i}, rectangle.color});
        }

    } else {

        for (uint32_t y = rectangle.position.y; y < rectangle.dimension.y; y++) {
            for (uint32_t x = rectangle.position.x; x < rectangle.dimension.x; x++) gp_draw_point(image, (gp_point_t){x, y}, rectangle.color);
        }
    }

    return;
}

void gp_draw_shape(gp_image_t *image, gp_shape_t *shape) {

    for (uint32_t i = 0; i < shape->nb_points; i++) {

        if (i == shape->nb_points - 1) gp_draw_line(image, (gp_line_t){shape->points[i], shape->points[0], shape->color});
        gp_draw_line(image, (gp_line_t){shape->points[i], shape->points[i+1], shape->color});
    }

    return;
}
