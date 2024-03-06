/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:00 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/06 02:51:03 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

Point3D	*store_in_node(int x, int y, int z, int color)
{
	Point3D	*node;

	node = malloc(sizeof(Point3D));
	node->x = x;
	node->y = y;
	node->z = z;
	node->color = color;
	node->next = NULL;
	return (node);
}

Point3D	*setup_first_node(Point3D **head, Point3D **point, int **map)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	*head = store_in_node(map[i][j], map[i][j + 1], map[i][j + 2], map[i][j
			+ 3]);
	*point = *head;
	(*point)->next = store_in_node(map[i + 1][j], map[i + 1][j + 1], map[i
			+ 1][j + 2], map[i + 1][j + 3]);
	j += 4;
	(*point)->next->next = store_in_node(map[i][j], map[i][j + 1], map[i][j
			+ 2], map[i][j + 3]);
	*point = (*point)->next->next;
	return (*head);
}

Point3D	*jump_to_node(Point3D *node, int skip)
{
	int	i;

	i = 0;
	while (i < skip)
	{
		node = node->next;
		i++;
	}
	return (node);
}

void	clear_list(Point3D *head)

{
	Point3D *to_free;
	Point3D *node;

	node = head;
	while (node)
	{
		to_free = node;
		node = node->next;
		free(to_free);
	}
}