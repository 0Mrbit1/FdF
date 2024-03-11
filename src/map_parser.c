/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:52 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/10 00:15:25 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"
#include "../include/get_next_line.h"
#include "../include/libft.h"

static void	transfer_data(int **hold, int ***map, int y, int line_lenght)
{
	int	at_y;

	at_y = 0;
	while (at_y < y)
	{
		(*map)[at_y] = malloc(sizeof(int) * line_lenght * 4);
		ft_memmove((*map)[at_y], hold[at_y], sizeof(int) * line_lenght * 4);
		at_y++;
	}
	if (y)
		free_array(hold, y);
}

static void	setup_color(int *i, char *splited_line, int ***map, int y)
{
	char	*color;

	color = ft_memchr(splited_line, ',', ft_strlen(splited_line));
	if (color)
	{
		color += sizeof(char);
		(*map)[y][(*i)++] = convert_to_decimal(color);
	}
	else
		(*map)[y][(*i)++] = 0xFFFFFF;
}

static void	store_points(char **splited_line, int ***map, int y,
		int line_lenght)
{
	int	x;
	int	**hold;
	int	i;

	x = 0;
	i = 0;
	hold = *map;
	*map = malloc(sizeof(int *) * (y + 1));
	transfer_data(hold, map, y, line_lenght);
	(*map)[y] = malloc(sizeof(int) * line_lenght * 4);
	while (x < line_lenght)
	{
		(*map)[y][i++] = x;
		(*map)[y][i++] = y;
		(*map)[y][i++] = ft_atoi(splited_line[x++]);
		setup_color(&i, splited_line[x - 1], map, y);
	}

}


int	**map_parser(int fd, int *array_lenght, int *number_of_lines)
{
	char	*line;
	char	**splited_line;
	int		**map;

	map = NULL;
	*number_of_lines = 0;
	line = get_next_line(fd);
	splited_line = ft_split(line, ' ');
	*array_lenght = _line_points(splited_line);
	while (line)
	{
		store_points(splited_line, &map, *number_of_lines, *array_lenght);
		free(line);
		free_array_char(splited_line, *array_lenght);
		line = get_next_line(fd);
		if (line)
			splited_line = ft_split(line, ' ');
		(*number_of_lines)++;
	}
	return (map);
}
