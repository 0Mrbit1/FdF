#include "../include/fdf.h"

void	draw_pixel(image_data img_data, char *img_cordinates, int x, int y,
		int color)
{
	int	index;

	index = (y * img_data.size_line) + (x * (img_data.bits_per_pixel / 8));
	if (index < 0)
	{
		return;
	}
	img_cordinates[index] = color % 256;
	img_cordinates[index + 1] = (color % 65536) / 256;
	img_cordinates[index + 2] = color / 65536;
}

static void	isometric_projection(Point3D *point, int map_width, int map_lenght)
{
	int	prev_x;
	int	scal;

	scal = 1000 / (map_lenght + map_width);
	prev_x = point->x;
	point->x = 450 + (prev_x * scal - point->y * scal)
		* cos(degrees_to_radians(30));
	point->y = 450 + (prev_x * scal + point->y * scal)
		* sin(degrees_to_radians(30)) - point->z * scal;
}

static void	draw_line(Point3D *node, Point3D *next, char *img_cordinates,
		image_data img_data)
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
	int	color;
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	x0 = node->x;
	y0 = node->y;
	x1 = next->x;
	y1 = next->y;
	color = node->color;
	dx = abs(x1 - x0);
	dy = abs(y1 - y0);
	sx = x0 < x1 ? 1 : -1;
	sy = y0 < y1 ? 1 : -1;
	err = dx - dy;
	while (1)
	{
		draw_pixel(img_data, img_cordinates, x0, y0, color);
		
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			x0 += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

/*void	draw_right_side(Point3D *head, in map_data[0], int map_data[1],
		void *img_ptr, int bits_per_pixel, int size_line)
{
	Point3D	*node;
	Point3D	*below;
	int		lines;
	int		i;
	int		j;
	Point3D	*head;
	Point3D	*node;
	Point3D	*node;
	Point3D	*node;

	node = head;
	node = jump_to_node(node map_data[0] * 2 - 2);
	below = jump_to_node(node map_data[0] * 2 - 1);
	draw_line(node, below, img_ptr, bits_per_pixel, size_line);
	lines = 0;
	while (lines < map_data[1] - 3)
	{
		node = below;
		below = jump_to_node(node map_data[0] * 2 - 1);
		draw_line(node, below, img_ptr, bits_per_pixel, size_line);
		lines++;
	}
}*/
/*void	draw_below_side(in map_data[0], int map_data[1], void *img_ptr,
		int bits_per_pixel, int size_line, int **map)
{
	i = map_data[1] - 1;
	ft_printf("%d", i);
	j = 0;
	head = store_in_node(map[i][j], map[i][j + 1], map[i][j + 2], map[i][j
			+ 3]);
	node = head;
	j += 4;
	while (j  map_data[0] * 4)
	{
		node->next = store_in_node(map[i][j], map[i][j + 1], map[i][j + 2],
				map[i][j + 3]);
		node = node->next;
		j += 4;
	}
	node = head;
	while (node)
	{
		isometric_projection(node map_data[0], map_data[1]);
		node = node->next;
	}
	node = head;
	while (node && node->next)
	{
		draw_line(node, node->next, img_ptr, bits_per_pixel, size_line);
		node = node->next;
	}
}*/
void	project(Point3D *head, int *map_data, image_data img_data,char *img_cordinates)
{
	Point3D *node ; 
	node = head;
	while (node)
	{
		isometric_projection(node, map_data[0], map_data[1]);
		draw_pixel(img_data, img_cordinates, node->x, node->y, node->color);
		node = node->next;
	}
}

void	pointes_renderer(Point3D *head, image_data img_data,  char *img_cordinates, int *map_data)
{
	Point3D	*node;
	int		links;
	int		lines;

	links = 0;
	lines = 0;
	node = head;
	project(head, map_data, img_data, img_cordinates);
	
	while (lines != map_data[1] - 1)
	{
		while (links != map_data[0] - 1)
		{
			draw_line(node, node->next, img_cordinates, img_data);
			draw_line(node, node->next->next, img_cordinates, img_data);
			node = node->next->next;
			links++;
		}
		node = node->next;
		links = 0;
		lines++;
	}
}

void	rendering_engine(Point3D *head, int array_lenght, int number_of_lines,
		void *mlx_ptr)
{
	image_data img_data;
	char *img_cordinates;
	void *win_ptr;
	int map_data[2];

	img_data.img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);

	img_cordinates = mlx_get_data_addr(img_data.img_ptr,
			&(img_data.bits_per_pixel), &(img_data.size_line),
			&(img_data.endian));

	map_data[0] = array_lenght;
	map_data[1] = number_of_lines;
	pointes_renderer(head, img_data, img_cordinates, map_data);

	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");

	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img_ptr, 0, 0);

	mlx_loop(mlx_ptr);
}