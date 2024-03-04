
#include "../include/fdf.h"


static Point3D *store_in_node( int x , int y , int z , int color )
{

    Point3D *node ;

    node = malloc(sizeof(Point3D)) ;
    node->x =  x;
    node->y  = y;
    node->z =  z;
    node->color = color ;
    node->next = NULL; 
    return node;
}

static Point3D *points_placer(int number_of_lines , int array_lenght , int **map)
{
    int i;
    int j;
    Point3D *point;
    Point3D *head;

    i = 0;
    j = 0;
    head = store_in_node(map[i][j] , map[i][j+1] , map[i][j+2] ,map[i][j+3] );  
    point = head;
    point -> next = store_in_node( map[i+1][j] ,map[i+1][j+1] ,map[i+1][j+2] , map[i+1][j+3]);   
    j += 4;
    point -> next -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2] , map[i][j+3]);
    point = point -> next -> next;
    while (i < number_of_lines -1)
    {
        while( j < array_lenght*4 -4 )
        {
            point -> next = store_in_node( map  [i+1][j] ,map[i+1][j+1] ,map[i+1][j+2]  ,map[i+1][j+3]);
            j += 4; 
            point -> next -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2] , map[i][j+3]);
            point = point -> next -> next;
        }
    j = 0;
    i++;
    point -> next = store_in_node(map[i][j] ,map[i][j+1] ,map[i][j+2] , map[i][j+3]); 
    point = point-> next ;  
    }
      return head;
}
   
void fdf(int fd  , void *mlx_ptr , void **win_ptr)
{
    int **map;
    int array_lenght;
    int number_of_lines;
    Point3D *head;


    map = map_parser(fd , &array_lenght , &number_of_lines);    
    
    head = points_placer(number_of_lines ,array_lenght , map);
    
    *win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
    
    pointes_renderer(head , mlx_ptr , *win_ptr , array_lenght , number_of_lines);
}

int main(int argc , char **argv)
{
    void *mlx_ptr;
    void *win_ptr;
    int fd;
    char *path;

    if (argc > 1)  
            path = 	ft_strjoin( "../tests/maps/test_maps/",argv[1]);
    else 
    {
        perror("please provide fdf file");
    }

    fd = open(path  , O_RDONLY) ;
    if (fd<0)
    {
        perror("cannot open file , it's either non existent or the file name is wrong , either way please use fdf maps");
        return 1;
    }
    mlx_ptr =  mlx_init() ;
    fdf( fd  , mlx_ptr , &win_ptr );
    
    mlx_loop(mlx_ptr);
    return 0;
}
