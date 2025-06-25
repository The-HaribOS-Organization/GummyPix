#ifndef _SHAPE_H
#define _SHAPE_H


#include <stdint.h>
#include <stdbool.h>
#include "utils.h"
#include "image.h"


typedef struct {
    
    point_t start;
    point_t end;
    pixels_t color;
} line_t;

typedef struct {

    point_t position;
    point_t dimension;
    bool filled;
    pixels_t color;
    uint32_t thickness;
} rectangle_t;

typedef struct {
    uint32_t radius;
    point_t position;
    bool filled;
} circle_t;

typedef struct {
    point_t *points;
    pixels_t color;
    uint32_t nb_points;
} shape_t;


void draw_point(image_t *image, point_t point, pixels_t color);
void draw_line(image_t *image, line_t line);
void draw_rectangle(image_t *image, rectangle_t rectangle);
void draw_shape(image_t *image, shape_t *shape);

#endif
