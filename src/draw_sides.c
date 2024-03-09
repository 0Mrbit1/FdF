/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sides.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/09 01:36:14 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/09 01:37:43 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	draw_last_point(Point3D *below, int *map_data, image_data img_data,
		int **map)
{
	Point3D	*node;

	node = store_in_node(map, map_data[1] - 1, map_data[0] * 4 - 4);
	isometric_projection(node, map_data[0], map_data[1]);
	draw_line(below, node, img_data);
	clear_list(node);
}

void	draw_right_side(Point3D *head, int *map_data, image_data img_data,
		int **map)
{
	Point3D	*node;
	Point3D	*below;
	int		lines;

	node = head;
	node = jump_to_node(node, map_data[0] * 2 - 2);
	below = jump_to_node(node, map_data[0] * 2 - 1);
	draw_line(node, below, img_data);
	lines = 0;
	while (lines < map_data[1] - 3)
	{
		node = below;
		below = jump_to_node(node, map_data[0] * 2 - 1);
		draw_line(node, below, img_data);
		lines++;
	}
	draw_last_point(below, map_data, img_data, map);
}

void	draw_below_side(int *map_data, image_data img_data, int **map)
{
	Point3D	*node;
	Point3D	*head;

	head = setup_nodes(map_data, map);
	node = head;
	while (node && node->next)
	{
		draw_line(node, node->next, img_data);
		node = node->next;
	}
	clear_list(head);
}
