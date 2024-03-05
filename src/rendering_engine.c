#include "../include/fdf.h"

static double degrees_to_radians(double angle_degrees ) {
    return angle_degrees * M_PI / 180;
}

static void isometric_projection(Point3D *point  ,int map_width , int map_lenght )
{
    int prev_x;
    int scal; 

    scal =  1000/(map_lenght + map_width);

    prev_x = point->x;

    point->x =   500 + (prev_x*scal - point->y*scal)*cos(degrees_to_radians(30));


    point->y =  500   + (prev_x*scal+ point->y*scal)*sin( degrees_to_radians(30)) - point->z*scal;
}


Point3D *jump_to_node(Point3D *node , int skip)
{
    int i;
    
    i = 0;

    while (i < skip  )
    {
        node = node->next;
        i++;
    }
    return node; 
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


void clear_list(Point3D *head ) 

{
    Point3D *to_free ;
    Point3D *node ; 

    node = head ; 
    
    while (node)
    {
        to_free = node ;  
        node = node -> next ; 
        free(to_free); 
    }
 
}

void draw_right_side(Point3D *head , int array_lenght , void *mlx_ptr , void *win_ptr , int number_of_lines)
{
    Point3D *node ;
    Point3D *below;
    int lines ;

    node = head ; 

    node =  jump_to_node(node , array_lenght*2  -2);
    below = jump_to_node(node , array_lenght*2  -1);
    draw_line(mlx_ptr, win_ptr, node ,  below);
    lines = 0;
   
    while (lines < number_of_lines - 3)
    {
        node = below ; 
        below = jump_to_node(node , array_lenght*2  -1);
        draw_line(mlx_ptr, win_ptr, node ,  below);
        lines++;
    }
}

void project(Point3D *head , int array_lenght , int number_of_lines , void *mlx_ptr , void * win_ptr)
{
    Point3D *node;

    node = head ;
    while (node)
    {
        isometric_projection(node , array_lenght , number_of_lines);
        mlx_pixel_put(mlx_ptr, win_ptr,  node->x , node-> y , node->color);
        node = node -> next; 
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
    project(head ,array_lenght , number_of_lines , mlx_ptr , win_ptr);
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
    draw_right_side(head , array_lenght , mlx_ptr , win_ptr , number_of_lines);  
    clear_list(head ); 
}