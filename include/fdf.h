/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:26 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/06 03:26:26 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/libft.h"
#include "../include/get_next_line.h"
#include "../include/mlx.h"
#include <fcntl.h>
#include <math.h>

typedef struct coordinates
{
	int					x;
	int					y;
	int					z;
	long				color;

	struct coordinates	*next;
}						Point3D;

int						**map_parser(int fd, int *l_array,
							int *number_of_lines);
void					pointes_renderer(Point3D *head, void *mlx_ptr,
							void *win_ptr, int array_lenght,
							int number_of_lines);
int						convert_to_decimal(char *str);
void					free_array(int **hold, int y);
void					free_array_char(char **hold, int y);
int						_line_points(char **line);
Point3D					*setup_first_node(Point3D **head, Point3D **point,
							int **map);
Point3D					*store_in_node(int x, int y, int z, int color);
void					free_array(int **hold, int y);
double					degrees_to_radians(double angle_degrees);
void					clear_list(Point3D *head);
Point3D					*jump_to_node(Point3D *node, int skip);
double	degrees_to_radians(double angle_degrees);