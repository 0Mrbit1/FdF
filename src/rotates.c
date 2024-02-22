/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotates.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yachtata <yachtata@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/25 04:16:46 by yachtata          #+#    #+#             */
/*   Updated: 2024/01/25 04:20:09 by yachtata         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/fdf.h"

void	rotate_z(int *x, int *y, int *z, float theta)
{
	int	new_x;
	int	new_y;

	(void)z;
	new_x = (*x * cos(theta) - *y * sin(theta));
	new_y = (*x * sin(theta) + *y * cos(theta));
	*x = new_x;
	*y = new_y;
}

void	rotate_x(int *x, int *y, int *z, float theta)
{
	int	new_y;
	int	new_z;

	(void)x;
	new_y = (*y * cos(theta) - *z * sin(theta));
	new_z = (*y * sin(theta) + *z * cos(theta));
	*y = new_y;
	*z = new_z;
}

void	rotate_y(int *x, int *y, int *z, float theta)
{
	int	new_x;
	int	new_z;

	(void)y;
	new_x = (*x * cos(theta) + *z * sin(theta));
	new_z = (-*x * sin(theta) + *z * cos(theta));
	*x = new_x;
	*z = new_z;
}

void	find_rotation(t_var *data, int *x, int *y, int *z)
{
	rotate_x(x, y, z, data->rotation_anglex);
	rotate_y(x, y, z, data->rotation_angley);
	rotate_z(x, y, z, data->rotation_anglez);
}

void	to_isometric(t_var *data, int *x, int *y, int *z)
{
	int	prev_x;
	int	map_ratio_mid;

	map_ratio_mid = (data->max_rows + data->max_columns - 2);
	prev_x = *x;
	*x += *y;
	*y = (*y / 2 - prev_x / 2) - *z;
	*x -= data->size_line * map_ratio_mid / 2;
}
