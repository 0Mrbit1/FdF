
#include fdf.h

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1) {
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);
    int sx = x0 < x1 ? 1 : -1;
    int sy = y0 < y1 ? 1 : -1;
    int err = (dx > dy ? dx : -dy) / 2;
    int e2;

    while (1) {
        mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF); // Draw pixel at (x0, y0)

        if (x0 == x1 && y0 == y1) break;
        e2 = err;
        if (e2 > -dx) { err -= dy; x0 += sx; }
        if (e2 < dy) { err += dx; y0 += sy; }
    }
}

void map_renderer(int number_of_lines , int array_lenght int **map)
{
    int i;
    int j;
    Point3D point;
    Point3D right_point;
    Point3D below_point;

     while (i < number_of_lines)
    { 
        while (j < array_lenght*3)
        {
            point.x = map[i][j] ; 
            point.y = map[i][j+1] ;
            point.z = map[i][j+2] ;

            j   = j +3

            right_point.x = map[i][j];
            right_point.y = map[i][j+1];
            right_point.z = map[i][j+2];

            j = 0
            below_point.x = map[i+1][j];
            below_point.y = map[i+1][j+1] ;
            below_point.z = map[i+1][j+2];

            // draw a line between those points 
            // proceed to the bext points 
            j = j +3 ; 
        }
        i++;
    }
}

void fdf(int fd)
{
    int **map;
    int array_lenght;
    int number_of_lines;

    map = map_parser(fd , &array_lenght , &number_of_lines); 

    map_renderer(number_of_lines ,array_lenght , map);

}

