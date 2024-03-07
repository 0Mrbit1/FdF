/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:27:44 by acharik          #+#    #+#             */
/*   Updated: 2024/03/07 06:27:44 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_pixel(image_data img_data, char *img_cordinates, img_pxl pixel)
{
	int	index;

	index = (pixel.y * img_data.size_line) + (pixel.x * (img_data.bits_per_pixel
				/ 8));
	if (index < 0)
	{
		return ;
	}
	img_cordinates[index] = pixel.color % 256;
	img_cordinates[index + 1] = (pixel.color % 65536) / 256;
	img_cordinates[index + 2] = pixel.color / 65536;
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

static void draw_line(Point3D *node, Point3D *next, char *img_coordinates, image_data img_data) {
 
    int coord_data[10]; // Array to store x0, y0, x1, y1, color, dx, dy, sx, sy, err
    img_pxl pixel;

    // Storing coordinates and color in coord_data array
    coord_data[0] = node->x;
    coord_data[1] = node->y;
    coord_data[2] = next->x;
    coord_data[3] = next->y;
    coord_data[4] = node->color;

    // Calculating delta (dx, dy)
    coord_data[5] = abs(coord_data[2] - coord_data[0]);
    coord_data[6] = abs(coord_data[3] - coord_data[1]);

    // Calculating steps (sx, sy)
    coord_data[7] = coord_data[0] < coord_data[2] ? 1 : -1;
    coord_data[8] = coord_data[1] < coord_data[3] ? 1 : -1;

    // Calculating err
    coord_data[9] = coord_data[5] - coord_data[6];

    while (1) {
        // Extracting x, y, color from coord_data and drawing pixel
        pixel.x = coord_data[0];
        pixel.y = coord_data[1];
        pixel.color = coord_data[4];
        draw_pixel(img_data, img_coordinates, pixel);

        if (coord_data[0] == coord_data[2] && coord_data[1] == coord_data[3])
            break;

        int e2 = 2 * coord_data[9];
        if (e2 > -coord_data[6]) {
            coord_data[9] -= coord_data[6];
            coord_data[0] += coord_data[7];
        }
        if (e2 < coord_data[5]) {
            coord_data[9] += coord_data[5];
            coord_data[1] += coord_data[8];
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
	Point3D	*node;
	Point3D	*node;
	img_pxl	pixel;

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
void	project(Point3D *head, int *map_data, image_data img_data,
		char *img_cordinates)
{
	Point3D *node;
	img_pxl pixel ; 
	node = head;
	while (node)
	{
		isometric_projection(node, map_data[0], map_data[1]);
		pixel.x = node->x;
		pixel.y = node->y;
		pixel.color = node->color;
		draw_pixel(img_data, img_cordinates, pixel);
		node = node->next;
	}
}

void	pointes_renderer(Point3D *head, image_data img_data,
		char *img_cordinates, int *map_data)
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