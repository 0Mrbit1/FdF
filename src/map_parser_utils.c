/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:22 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/06 02:51:23 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

void	free_array(int **hold, int y)
{
	int	j;

	j = 0;
	while (j < y)
		free(hold[j++]);
	free(hold);
}

void	free_array_char(char **hold, int y)
{
	int	j;

	j = 0;
	while (j < y)
		free(hold[j++]);
	free(hold);
}

int	_line_points(char **line)
{
	int	i;

	i = 0;
	while (line[i])
		i++;
	return (i);
}

double	degrees_to_radians(double angle_degrees)
{
	return (angle_degrees * M_PI / 180);
}