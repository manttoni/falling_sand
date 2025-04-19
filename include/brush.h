#ifndef BRUSH_H
#define BRUSH_H

#include "../include/pixel.h"

typedef struct s_brush
{
    int         size;
    pixel_type  type;
}   t_brush;

void paint(int *pixels, t_brush *brush, int mouse_x, int mouse_y);
void select_next_type(t_brush *brush);
void select_previous_type(t_brush *brush);

#endif