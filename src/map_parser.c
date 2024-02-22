#include "../include/get_next_line.h"
#include "../include/libft.h"
#include "../include/ft_printf.h"
#include <fcntl.h>


void free_array(int **hold , int line_lenght , int y )
{
    int j;

    j =0 ;
    while(j < y)
        free(hold[j++]);

    free(hold);
}


int _line_points(char **line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return  (i);
}

void    transfer_data(int **hold , int ***map , int y , int line_lenght)
{
    int at_y;
    int i;

    at_y = 0;
    i =0;
    while(at_y < y )
    {
        (*map)[at_y]  = malloc(sizeof(int)*line_lenght*3);
         
         while(i < line_lenght*3)
         {
            (*map)[at_y][i] = hold[at_y][i];
            i++;
            (*map)[at_y][i] = hold[at_y][i];
            i++;
            (*map)[at_y][i] = hold[at_y][i];   
            i++;
         }
         at_y++;
         i=0;
    }
    if(y)
        free_array(hold ,line_lenght ,y);
}

void store_points(char **splited_line , int ***map , int y , int line_lenght)
{
    int x;
    int **hold;
    int *points;
    int i;

    x=0;
    i=0;
    hold = *map;
    *map=malloc(sizeof(int*)*y--);
    transfer_data(hold ,map , y , line_lenght);
    (*map)[y] = malloc(sizeof(int)*line_lenght*3);
    points = (*map)[y];
    while(x < line_lenght)
    {
        points[i++] = x;
        points[i++] = y;
        points[i++] = ft_atoi(splited_line[x++]);
    }
}

int    **map_parser(int fd)
{
    char    *line;
    char    **splited_line;
    int line_points;
    int y;
    int **map;

    y = 1;
    line = get_next_line(fd);
    splited_line = ft_split(line , ' ');
    line_points = _line_points(splited_line);
    while(line)
    {
        store_points(splited_line , &map , y , line_points);
        free(line);
        free(splited_line);
        line = get_next_line(fd);
        if(line)
            splited_line = ft_split(line,' ');
        line_points = _line_points(splited_line);
        y++;
    }
    return (map);
}

int main()
{

    int fd ; 
    int i;
    int j;
    
    fd = open("/home/abdellah/Desktop/project/fdf/tests/test_maps/42.fdf", O_RDONLY);

   int **map; 

   map = map_parser(fd) ;
   ft_printf("%d" , map[2][8]);

    j =0 ;
    while(j < 11)
        free(map[j++]);

    free(map);




}