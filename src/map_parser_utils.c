#include "../include/fdf.h"


void free_array(int **hold , int y )
{
    int j;

    j =0 ;
    while(j < y)
        free(hold[j++]);

    free(hold);
}

 void free_array_char(char **hold , int y )
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