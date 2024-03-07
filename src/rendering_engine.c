#include "../include/fdf.h"


void draw_pixel(void *img_ptr, int bits_per_pixel, int size_line, int x, int y, int color )
{
    // Calculate the index of the pixel (x, y) in the image data
    int index = (y * size_line) + (x * (bits_per_pixel / 8));
    //ft_printf("%d\n" , index) ; 
    // Set the pixel color at the calculated index
    char *img_data = (char *)img_ptr;


    // Extracting color components without bitwise operators
    if (index >= 0 && index < (size_line * 1000)) // Assuming HEIGHT is the height of the image in pixels
    {
        // Set the pixel color at the calculated index
        char *img_data = (char *)img_ptr;

        // Extracting color components without bitwise operators
        int red = color / 65536;           // Extract red component
        int green = (color % 65536) / 256; // Extract green component
        int blue = color % 256;  
          // Extract blue component

        // Assign color components to the image data with consideration for endianness
        img_data[index] = blue;        // Blue component
        img_data[index+1] = green;   // Green component
        img_data[index+2] = red;     // Red component
    }
}

static void isometric_projection(Point3D *point  ,int map_width , int map_lenght )
{
    int prev_x;
    int scal; 

    scal =  1000/(map_lenght + map_width);

    prev_x = point->x;

    point->x =   450 + (prev_x*scal - point->y*scal)*cos(degrees_to_radians(30));

    point->y =  450   + (prev_x*scal+ point->y*scal)*sin( degrees_to_radians(30)) - point->z*scal;
}

void draw_last (int number_of_lines , int array_lenght , )

static void draw_line(void *mlx_ptr, void *win_ptr, Point3D *node, Point3D *next , void *img_ptr ,  int bits_per_pixel,   int size_line )
{
    int x0 ; 
    int y0 ;
    int x1 ;
    int y1;
    int color; 

    x0 = node->x  ; 
    y0 = node->y ;
    x1 = next->x; 
    y1  = next->y ; 
    color = node->color; 

    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int e2;
    int i ;
    i = 0;

    while (1)
    {
        draw_pixel(img_ptr, bits_per_pixel, size_line,  x0,  y0, color );

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

void draw_right_side(Point3D *head , int array_lenght , void *mlx_ptr , void *win_ptr , int number_of_lines , void *img_ptr , int bits_per_pixel , int size_line)
{
    Point3D *node ;
    Point3D *below;
    int lines ;

    node = head ; 
    node =  jump_to_node(node , array_lenght*2  -2);
    below = jump_to_node(node , array_lenght*2  -1);
    draw_line(mlx_ptr, win_ptr, node, below , img_ptr ,  bits_per_pixel,  size_line );
    lines = 0;
   
    while (lines < number_of_lines - 3)
    {
        node = below ; 
        below = jump_to_node(node , array_lenght*2  -1);
          draw_line(mlx_ptr, win_ptr, node, below , img_ptr ,  bits_per_pixel,  size_line );
        lines++;
    }
}

void project(Point3D *head , int array_lenght , int number_of_lines , void *mlx_ptr , char *img_ptr , int bits_per_pixel, int size_line , int endian)
{
    Point3D *node;

    node = head ;
    while (node)
    {
        isometric_projection(node , array_lenght , number_of_lines);
        draw_pixel(img_ptr, bits_per_pixel,  size_line, node->x, node-> y, node->color);
        node = node -> next; 
    }
}

void pointes_renderer(Point3D *head , void *mlx_ptr , void *win_ptr , int array_lenght , int number_of_lines )
{
    Point3D *node;
    int links;
    int lines; 
    void *img_ptr ;
    int bits_per_pixel;
    int size_line;
    int endian;

    img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);

    char *img_data = mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);


    links = 0; 
    lines = 0; 
    node = head;
    project(head ,array_lenght , number_of_lines , mlx_ptr , img_data , bits_per_pixel,  size_line , endian);
    while (lines != number_of_lines -1)
    {
       while(links != array_lenght -1 )
       {
           draw_line(mlx_ptr, win_ptr, node, node->next , img_data ,   bits_per_pixel,   size_line );
           draw_line(mlx_ptr, win_ptr, node, node->next->next , img_data ,   bits_per_pixel,   size_line );
           node = node->next->next;
           links++;
        } 
        node = node->next; 
        links =0 ;
        lines++; 
    }
    draw_right_side(head , array_lenght , mlx_ptr , win_ptr , number_of_lines , img_data ,  bits_per_pixel ,  size_line) ;
     mlx_put_image_to_window(mlx_ptr, win_ptr, img_ptr, 0, 0);
    clear_list(head );
}