#include "../include/data.h"
#include "../include/settings.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void update_image(mlx_image_t *image, uint32_t *pixels)
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

void trickle_effect(uint32_t *pixels, int i)
{
    int trickle;
    if (i + 1 >= X * Y || row(i) != row(i + 1))
        trickle = -1;
    else if (i - 1 < 0 || row(i) != row(i - 1))
        trickle = 1;
    else
        trickle = rand() % 2 == 0 ? 1 : -1;

    if (i + trickle + X < X * Y && is_flowing(pixels[i + trickle + X]))
        change_X_velocity(&pixels[i], trickle);
}

void flow_effect(uint32_t *pixels, int i)
{
    int vx = get_X_velocity(pixels[i]);

    if (vx == 0)
        vx = (rand() % 2 == 0 ? 1 : -1);

    change_X_velocity(&pixels[i], vx / abs(vx));
}
// Decide where pixels[i] pixel will move based on its velocity and type and density
int move(uint32_t *pixels, int i)
{
    if (get_pixel_type(pixels[i]) == VOID)
        return i;
    uint32_t *pixel = &pixels[i];
    int mass = get_mass(*pixel);

    // if there is something more or equally massive underneath, apply random horizontal velocity
    if (i + X < X * Y && get_mass(pixels[i + X]) >= mass)
    {
        // liquids get flow effect, other trickle down slopes
        if (is_liquid(pixels[i]))
            flow_effect(pixels, i);
        else
            trickle_effect(pixels, i);
    }

    // everything gets some velocity
    change_Y_velocity(pixel, GRAVITY);

    int vx = get_X_velocity(*pixel);
    int vy = get_Y_velocity(*pixel);

    // friction
    change_X_velocity(pixel, -vx * 0.9);
    change_Y_velocity(pixel, -vy * 0.1);

    vx = get_X_velocity(*pixel);
    vy = get_Y_velocity(*pixel);

    int x = 0, y = 0; // how much pixel has moved
    int dx = vx == 0 ? 0 : vx / abs(vx); // x movement direction
    int dy = vy == 0 ? 0 : vy / abs(vy); // y movement direction
    while(x != vx || y != vy)
    {
        bool moved = false;
        int mass_diff;

        // horizontal
        if (x != vx // dont move if already moved enough
            && i + dx >= 0 && i + dx < X * Y) // bounds
        {
            mass_diff = get_mass(pixels[i + dx]) - mass;
            if (mass_diff < 0 // can displace only lighter materials
                && row(i) == row(i + dx)) // on the same row
            {
                i += dx; // update index
                pixel = &pixels[i];
                x += dx; // update movement in X
                change_X_velocity(pixel, dx * mass_diff); // decrease velocity
                moved = true;
            }
        }

        // vertical
        if (y != vy && i + dy * X >= 0 && i + dy * X < X * Y)
        {
            mass_diff = get_mass(pixels[i + dy * X]) - mass;
            if (mass_diff < 0)
            {
                i += dy * X;
                pixel = &pixels[i];
                y += dy;
                change_Y_velocity(pixel, dy * mass_diff);
                moved = true;
            }
        }
        if (!moved)
        {
            *pixel = new_pixel(get_density(*pixel), 0, 0, get_pixel_type(*pixel));
            break;
        }
    }

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
        uint32_t next[X * Y];
        bool moved[X * Y];
        memcpy(next, data->pixels, X * Y * sizeof(uint32_t));
        memset(moved, false, X * Y * sizeof(bool));

        for (int i = X * Y - 1; i >= 0; --i)
        {
            int from = indices[i];
            //printf("Moving pixel: %d", data->pixels[from]);
            if (moved[from] == true)
                continue;
            int to = move(data->pixels, from);
            if (moved[to] == true)
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