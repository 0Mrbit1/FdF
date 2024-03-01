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
    long color;
    
    struct coordinates *next;
}Point3D;

int    **map_parser(int fd , int *l_array , int *number_of_lines );
void pointes_renderer(Point3D *head , void *mlx_ptr , void *win_ptr , int array_lenght , int number_of_lines );
int convert_to_decimal(char *str);