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


void gp_draw_point(gp_image_t *image, gp_point_t point, gp_pixels_t color);
void gp_draw_line(gp_image_t *image, gp_line_t line);
void gp_draw_rectangle(gp_image_t *image, gp_rectangle_t rectangle);
void gp_draw_shape(gp_image_t *image, gp_shape_t *shape);

#endif
