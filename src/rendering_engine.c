#include "../include/fdf.h"

static double degrees_to_radians(double angle_degrees ) {
    return angle_degrees * M_PI / 180;
}

static void isometric_projection(Point3D *point  ,int map_width , int map_lenght )
{
    int prev_x;
    int scal; 

    scal =  10;


    prev_x = point->x;

    point->x =   (map_width*20)/2 + (prev_x*scal - point->y*scal)*cos( degrees_to_radians(30));

    point->y =    (map_lenght*20)/2 + (prev_x*scal+ point->y*scal)*sin( degrees_to_radians(30)) - point->z*scal;
}

static void draw_line(void *mlx_ptr, void *win_ptr, Point3D *node, Point3D *next)
{
    int x0 ; 
    int y0 ;
    int x1 ;
    int y1;
    int color; 

    x0 = node->x ; 
    y0 = node->y;

    x1 = next->x; 
    y1  = next->y ; 
    color = node->color; 


    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, color);

        if (x0 == x1 && y0 == y1) break;

        e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y0 += sy;
        }
    }
}

void pointes_renderer(Point3D *head , void *mlx_ptr , void *win_ptr , int array_lenght , int number_of_lines )
{
    Point3D *node;
    int links;
    int lines; 

    links = 0; 
    lines = 0; 

    node = head;
    while (node)
    {
        isometric_projection(node , array_lenght , number_of_lines);
        mlx_pixel_put(mlx_ptr, win_ptr,  node->x , node-> y , node->color);
        node = node -> next; 
    }

    node = head;

    while (lines != number_of_lines -1)
    {
       
       while(links != array_lenght -1 )
       {
           draw_line(mlx_ptr, win_ptr, node ,  node->next);
           draw_line(mlx_ptr, win_ptr, node ,  node->next->next);
           node = node->next->next;
           links++;
        } 
        node = node->next; 
        links =0 ;
        lines++; 
    }
}