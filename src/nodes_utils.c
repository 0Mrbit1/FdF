/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nodes_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo1 <abdo1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:00 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/12 06:03:14 by abdo1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

t_Point3D	*store_in_node(int **map, int i, int j)
{
	t_Point3D	*node;

	node = malloc(sizeof(t_Point3D));
	node->x = map[i][j];
	node->y = map[i][j + 1];
	node->z = map[i][j + 2];
	node->color = map[i][j + 3];
	node->next = NULL;
	return (node);
}

t_Point3D	*setup_first_node(t_Point3D **head, t_Point3D **point, int **map)
{
	int	j;
	int	i;

	i = 0;
	j = 0;
	*head = store_in_node(map, i, j);
	*point = *head;
	(*point)->next = store_in_node(map, i + 1, j);
	j += 4;
	(*point)->next->next = store_in_node(map, i, j);
	*point = (*point)->next->next;
	return (*head);
}

t_Point3D	*jump_to_node(t_Point3D *node, int skip)
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

void	clear_list(t_Point3D *head)
{
	t_Point3D	*to_free;
	t_Point3D	*node;

	node = head;
	while (node)
	{
		to_free = node;
		node = node->next;
		free(to_free);
	}
}

t_Point3D	*setup_nodes(int *map_data, int **map, int *origin_scal)
{
	int			j;
	t_Point3D	*head;
	t_Point3D	*node;

	j = 0;
	head = store_in_node(map, map_data[1] - 1, j);
	node = head;
	j += 4;
	while (j < map_data[0] * 4)
	{
		node->next = store_in_node(map, map_data[1] - 1, j);
		node = node->next;
		j += 4;
	}
	node = head;
	while (node)
	{
		isometric_projection(node, origin_scal);
		node = node->next;
	}
	return (head);
}
