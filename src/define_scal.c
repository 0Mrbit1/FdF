/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   define_scal.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo1 <abdo1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 07:12:51 by abdo1             #+#    #+#             */
/*   Updated: 2024/03/11 07:14:45 by abdo1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

int	*resizer_helper(int **map, int *map_data, int *origin_scal, int *index)
{
	Point3D	point;

	while (index[0] < map_data[1])
	{
		while (index[1] < map_data[0])
		{
			point.x = map[index[0]][index[1]];
			point.y = map[index[0]][index[1] + 1];
			point.z = map[index[0]][index[1] + 2];
			index[1] += 4;
			isometric_projection(&point, origin_scal);
			if (point.y < 0)
			{
				origin_scal[1] = 100 - point.y;
				origin_scal[2] = origin_scal[2] / 2;
				return (origin_scal);
			}
			index[1] += 4;
		}
		index[1] = 0;
		index[0]++;
	}
	return (origin_scal);
}

int	*define_origine_scal(int **map, int *map_data)
{
	int	*origin_scal;
	int	indexes[2];

	indexes[0] = 0;
	indexes[1] = 0;
	origin_scal = malloc(sizeof(int) * 3);
	origin_scal[0] = 480;
	origin_scal[1] = 490;
	origin_scal[2] = 1000 / (map_data[0] + map_data[1]);
	return (resizer_helper(map, map_data, origin_scal, indexes));
}
