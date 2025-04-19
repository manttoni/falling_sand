#include "../include/data.h"
#include "../include/settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void update_image(mlx_image_t *image, int *pixels)
{
    for (int i = 0; i < X * Y; ++i)
    {
        mlx_put_pixel(image, i % X, i / X, get_pixel_color(pixels[i]));
    }
}

int max(int a, int b)
{
    if (a > b)
        return a;
    return b;
}

int flow(int *pixels, int i)
{
    if (is_flowing(pixels[i]) && i - X >= 0)
        if (pixels[i] < pixels[i - X])
            return i - X;

    int one = rand() % 2 == 0 ? 1 : -1;

    if (i % Y == X - 1)
        one = -1;
    else if (i % Y == 0)
        one = 1;

    if (is_flowing(pixels[i]) && i - X + one >= 0 && i - X + one < X * Y)
        if (pixels[i] < pixels[i - X + one])
            return i - X + one;

    if (i + one >= 0 && i + one < X * Y)
        if (is_flowing(pixels[i + one]) && pixels[i] < pixels[i + one])
            return i + one;

    return i;
}

void simulate(void *param)
{
    t_data *data = (t_data *)param;

    int indices[X * Y];
    for (int i = 0; i < X * Y; ++i)
        indices[i] = i;
    for (int i = X * Y - 1; i > 0; --i)
    {
        int j = rand() % (i + 1);
        int tmp = indices[i];
        indices[i] = indices[j];
        indices[j] = tmp;
    }

    for (int j = 0; j < data->speed; ++j)
    {
        int next[X * Y];
        bool moved[X * Y];
        memcpy(next, data->pixels, X * Y * sizeof(int));
        memset(moved, false, X * Y * sizeof(bool));

        for (int i = X * Y - 1; i >= 0; --i)
        {
            int to = indices[i];
            if (moved[to] == true)
                continue;
            int from = flow(data->pixels, to);
            if (moved[from] == true)
                continue;

            next[to] = data->pixels[from];
            next[from] = data->pixels[to];
            moved[from] = moved[to] = true;
        }
        memcpy(data->pixels, next, X * Y * sizeof(int));
    }

    update_image(data->image, data->pixels);
    mlx_image_to_window(data->mlx, data->image, 0, 0);
}