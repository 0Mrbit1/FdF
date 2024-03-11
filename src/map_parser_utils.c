/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:51:22 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/09 06:22:25 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

//
void	free_array(int **hold, int y)
{
	int	j;

	j = 0;
	while (j < y)
		free(hold[j++]);
	free(hold);
}

void	free_array_char(char **hold)
{
	int	j;

	j = 0;
	while (hold[j])
		free(hold[j++]);
	free(hold);
}

int	_line_points(char **line)
{
	int	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
		i++;
	return (i);
}

int	check_for_chars(char **str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (!ft_isdigit(str[i][0]))
			return (1);
		i++;
	}
	return (0);
}
