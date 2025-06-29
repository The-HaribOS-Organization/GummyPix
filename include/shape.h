#ifndef _SHAPE_H
#define _SHAPE_H


#include <stdint.h>
#include <stdbool.h>
#include "utils.h"
#include "image.h"


typedef struct {
    
    gp_point_t start;
    gp_point_t end;
    gp_pixels_t color;
} gp_line_t;

typedef struct {

    gp_point_t position;
    gp_point_t dimension;
    bool filled;
    gp_pixels_t color;
    uint32_t thickness;
} gp_rectangle_t;

typedef struct {
    uint32_t radius;
    gp_point_t position;
    bool filled;
} gp_circle_t;

typedef struct {
    gp_point_t *points;
    gp_pixels_t color;
    uint32_t nb_points;
} gp_shape_t;


__attribute__((always_inline)) inline gp_point_t gp_compute_bezier_curve(gp_point_t first_point, gp_point_t second_point, gp_point_t reference_point, float t, uint32_t radius) {

    return (gp_point_t){
        ((1 - t) * (1 - t) * reference_point.x + 2 * (1 - t) * (second_point.x + radius) * t + t * t * (first_point.x + radius)),
        ((1 - t) * (1 - t) * (reference_point.y + radius) + 2 * (1 - t) * (second_point.y - radius) * t + t * t * first_point.y)};
}

void gp_draw_point(gp_image_t *image, gp_point_t point, gp_pixels_t color);
void gp_draw_line(gp_image_t *image, gp_line_t line);
void gp_draw_rectangle(gp_image_t *image, gp_rectangle_t rectangle);
void gp_draw_shape(gp_image_t *image, gp_shape_t *shape);

#endif
