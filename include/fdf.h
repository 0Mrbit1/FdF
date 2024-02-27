#include <math.h>
#include "../include/mlx.h"
#include "../include/libft.h"
#include "../include/get_next_line.h"
#include "../include/ft_printf.h"
#include <fcntl.h>

typedef struct coordinates
{
    int x;
    int y;
    int z;
    
    struct coordinates *next;
}Point3D;

int    **map_parser(int fd , int *l_array , int *number_of_lines ); 

//void to_isometric(int *x , int *y , int *z );