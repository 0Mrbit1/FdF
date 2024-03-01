#include "../include/libft.h"
#include "../include/get_next_line.h"
#include "../include/fdf.h"

static void free_array(int **hold , int y )
{
    int j;

    j =0 ;
    while(j < y)
        free(hold[j++]);

    free(hold);
}

static void free_array_char(char **hold , int y )
{
    int j;

    j =0 ;
    while(j < y)
        free(hold[j++]);

    free(hold);
}

static int _line_points(char **line)
{
    int i;

    i = 0;
    while(line[i])
        i++;
    return  (i);
}

static void    transfer_data(int **hold , int ***map , int y , int line_lenght)
{
    int at_y;
    int i;

    at_y = 0;
    while(at_y < y )
    {
        (*map)[at_y]  = malloc(sizeof(int)*line_lenght*4);
         i=0;
         while(i < line_lenght*4)
         {
            (*map)[at_y][i] = hold[at_y][i];
            i++;
            (*map)[at_y][i] = hold[at_y][i];
            i++;
            (*map)[at_y][i] = hold[at_y][i]; 
            i++; 
            (*map)[at_y][i] = hold[at_y][i]; 
            i++;
         }
         at_y++;
    }
    if(y)
        free_array(hold ,y);
}

static void store_points(char **splited_line , int ***map , int y , int line_lenght)
{
    int x;
    int **hold;
    int i;
    char *color ; 

    x=0;
    i=0;
    hold = *map;
    *map=malloc(sizeof(int*)*(y +1));
    transfer_data(hold ,map , y , line_lenght);
    (*map)[y] = malloc(sizeof(int)*line_lenght*4);
    while(x < line_lenght)
    {
        (*map)[y][i++] = x;
        (*map)[y][i++] = y;
        (*map)[y][i++] = ft_atoi(splited_line[x++]);
        color = ft_memchr(splited_line[x -1] , ',' , ft_strlen(splited_line[x-1]) ); 
        if (color)
        {
            color += sizeof(char);
            (*map)[y][i++] = convert_to_decimal(color); 
        }
        else
            (*map)[y][i++] = 0xFFFFFF; 

    }
}

int    **map_parser(int fd , int *l_array , int *number_of_lines )
{
    char    *line;
    char    **splited_line;
    int line_points;
    int y;
    int **map;

    y = 0;
    line = get_next_line(fd);
    splited_line = ft_split(line , ' ');
    line_points = _line_points(splited_line);
    *l_array =  line_points;
    while(line)
    {
        store_points(splited_line , &map , y , line_points);
        free(line);
        free_array_char(splited_line , line_points);
        line = get_next_line(fd);
        if(line)
            splited_line = ft_split(line,' ');
        line_points = _line_points(splited_line);
        y++;
    }
    *number_of_lines = y ; 
    return (map);
}
