#include "../include/brush.h"
#include "../include/settings.h"
#include "../include/pixel.h"
#include <math.h>

void paint(int *pixels, t_brush *brush, int mouse_x, int mouse_y)
{
    for(int y = mouse_y - brush->size; y <= mouse_y + brush->size; ++y)
    {
        if (y < 0 || y >= Y)
            continue;

        for(int x = mouse_x - brush->size; x <= mouse_x + brush->size; ++x)
        {
            if (x < 0 || x >= X)
                continue;

            if (hypot(mouse_y - y, mouse_x - x) <= brush->size)
            {
                int *pixel = get_pixel(pixels, x, y);
                *pixel = brush->type;
            }
        }
    }
}

void select_next_type(t_brush *brush)
{
    if (brush->type >= END - 1)
        brush->type = VOID;
    else
        brush->type++;
}

void select_previous_type(t_brush *brush)
{
    if (brush->type <= VOID)
        brush->type = END - 1;
    else
        brush->type--;
}