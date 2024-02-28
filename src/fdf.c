
#include "../include/fdf.h"

#define ANGLE30 

double degrees_to_radians(double angle_degrees ) {
    return angle_degrees * M_PI / 180;
}

void isometric_projection(Point3D *point)
{
    int prev_x;
    int scal; 

    scal =  20;

    prev_x = point->x;

    point->x =   500 + (prev_x*scal - point->y*scal)*cos( degrees_to_radians(30));

    point->y = 500  + (prev_x*scal+ point->y*scal)*sin( degrees_to_radians(30)) - point->z*scal;
}

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = dx - dy;
    int e2;

    while (1)
    {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);

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
    int i;
    int links ;
    int lines; 

    links = 0 ; 
    lines = 0 ; 

    node = head;
    while (node)
    {
        isometric_projection(node);
        mlx_pixel_put(mlx_ptr, win_ptr,  node->x , node-> y , 0xFFFFFF);
        node = node -> next ; 
    }

    node = head;

    while (lines != number_of_lines -1)
    {
       
       while(links != array_lenght -1 )
       {
           draw_line(mlx_ptr, win_ptr, node->x,  node->y ,  node->next->x, node->next->y);
           draw_line(mlx_ptr, win_ptr, node->x,  node->y ,  node->next->next->x, node->next->next->y);
           node = node->next->next;
           links++;
        } 
        node = node->next; 
        links =0 ;
        lines++; 
    }
    

}

Point3D *store_in_node( int x , int y , int z)
{

    Point3D *node ;

    node = malloc(sizeof(Point3D)) ;
    node->x =  x;
    node->y  = y;
    node->z =  z;
    node->next = NULL; 
    return node;
}

Point3D *points_placer(int number_of_lines , int array_lenght , int **map)
{
    int i;
    int j;
    Point3D *point;
    Point3D *head;

    i = 0;
    j = 0;

    head = store_in_node(map[i][j] , map[i][j+1] , map[i][j+2]);  
    point = head;
    point -> next = store_in_node( map[i+1][j] ,map[i+1][j+1] ,map[i+1][j+2]);   
    j += 3;
    point -> next -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2]);
    point = point -> next -> next;
    while (i < number_of_lines -1)
    {
        while( j < array_lenght*3 -3 )
        {
            point -> next = store_in_node( map  [i+1][j] ,map[i+1][j+1] ,map[i+1][j+2]);
            j += 3; 
            point -> next -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2]);
            point = point -> next -> next;
        }
    j = 0;
    i++;
    point -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2]); 
    point = point-> next ; 
        
    }
      return head;
}
   
void fdf(int fd  , void *mlx_ptr , void *win_ptr)
{
    int **map;
    int array_lenght;
    int number_of_lines;
    Point3D *head;

    map = map_parser(fd , &array_lenght , &number_of_lines);    
    
    head = points_placer(number_of_lines ,array_lenght , map);
    
    pointes_renderer(head , mlx_ptr , win_ptr , array_lenght , number_of_lines);
}
int main(int argc , char **argv)
{
    void *mlx_ptr;
    void *win_ptr;
    int fd;
    char *path= 	ft_strjoin( "../tests/maps/test_maps/",argv[1]);

    fd = open(path  , O_RDONLY) ;
    mlx_ptr =  mlx_init() ;
    win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF"); 
    fdf( fd  , mlx_ptr , win_ptr);
    mlx_loop(mlx_ptr);
}
