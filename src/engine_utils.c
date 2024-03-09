/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   engine_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 01:05:33 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/09 01:42:14 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

#define ANGLE 30

void	draw_pixel(image_data img_data, img_pxl pixel)
{
	int	index;

	index = (pixel.y * img_data.size_line) + (pixel.x * (img_data.bits_per_pixel
				/ 8));
	if (index < 0)
		return ;
	img_data.img_cordinates[index] = pixel.color % 256;
	img_data.img_cordinates[index + 1] = (pixel.color % 65536) / 256;
	img_data.img_cordinates[index + 2] = pixel.color / 65536;
}

void	isometric_projection(Point3D *point, int map_width, int map_lenght)
{
	int	prev_x;
	int	scal;
	int	prev_y;

	scal = 1000 / (map_lenght + map_width);
	prev_y = point->y;
	prev_x = point->x;
	point->x = 470 + (prev_x * scal - point->y * scal)
		* cos(degrees_to_radians(ANGLE));
	if (point->x < 0 || point->x > 1000)
	{
		point->x = 470 + (prev_x * scal / 2 - point->y * scal)
			* cos(degrees_to_radians(ANGLE));
	}
	point->y = 470 + (prev_x * scal + point->y * scal)
		* sin(degrees_to_radians(ANGLE)) - point->z * scal;
	if (point->y < 0 || point->y > 1000)
	{
		point->y = 470 + (prev_x * scal + prev_y * scal)
			* sin(degrees_to_radians(ANGLE)) - point->z * scal / 2;
	}
}

void	initialise_array(int *coord_data, Point3D *node, Point3D *next)
{
	coord_data[0] = node->x;
	coord_data[1] = node->y;
	coord_data[2] = next->x;
	coord_data[3] = next->y;
	coord_data[4] = node->color;
	coord_data[5] = abs(coord_data[2] - coord_data[0]);
	coord_data[6] = abs(coord_data[3] - coord_data[1]);
	if (coord_data[0] < coord_data[2])
		coord_data[7] = 1;
	else
		coord_data[7] = -1;
	if (coord_data[1] < coord_data[3])
		coord_data[8] = 1;
	else
		coord_data[8] = -1;
	coord_data[9] = coord_data[5] - coord_data[6];
}

void	draw_line(Point3D *node, Point3D *next, image_data img_data)
{
	int		coord_data[10];
	img_pxl	pixel;
	int		e2;

	initialise_array(coord_data, node, next);
	while (1)
	{
		pixel.x = coord_data[0];
		pixel.y = coord_data[1];
		pixel.color = coord_data[4];
		draw_pixel(img_data, pixel);
		if (coord_data[0] == coord_data[2] && coord_data[1] == coord_data[3])
			break ;
		e2 = 2 * coord_data[9];
		if (e2 > -coord_data[6])
		{
			coord_data[9] -= coord_data[6];
			coord_data[0] += coord_data[7];
		}
		if (e2 < coord_data[5])
		{
			coord_data[9] += coord_data[5];
			coord_data[1] += coord_data[8];
		}
	}
}

void	project(Point3D *head, int *map_data, image_data img_data)
{
	img_pxl	pixel;
	Point3D	*node;

	node = head;
	while (node)
	{
		isometric_projection(node, map_data[0], map_data[1]);
		pixel.x = node->x;
		pixel.y = node->y;
		pixel.color = node->color;
		draw_pixel(img_data, pixel);
		node = node->next;
	}
}
