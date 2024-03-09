/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_engine.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acharik <acharik@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 06:27:44 by acharik          #+#    #+#             */
/*   Updated: 2024/03/07 06:27:44 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"



void	pointes_renderer(Point3D *head, image_data img_data, int *map_data)
{
	int		links;
	int		lines;
	Point3D	*node;

	links = 0;
	lines = 0;
	node = head;
	project(head, map_data, img_data);
	while (lines != map_data[1] - 1)
	{
		while (links != map_data[0] - 1)
		{
			draw_line(node, node->next, img_data);
			draw_line(node, node->next->next, img_data);
			node = node->next->next;
			links++;
		}
		node = node->next;
		links = 0;
		lines++;
	}
}

int	close_window_event(int keycode, free_tools *mlx_free)
{
	if (keycode == 65307)
	{
		mlx_destroy_image(mlx_free->mlx_ptr, mlx_free->img_ptr);
		mlx_destroy_window(mlx_free->mlx_ptr, mlx_free->win_ptr);
		mlx_loop_end(mlx_free->mlx_ptr);
		return (0);
	}
	return (1);
}

void	rendering_engine(Point3D *head, int *map_data, void *mlx_ptr, int **map)
{
	image_data	img_data;
	void		*win_ptr;
	free_tools	tools_free;

	img_data.img_ptr = mlx_new_image(mlx_ptr, 1000, 1000);
	img_data.img_cordinates = mlx_get_data_addr(img_data.img_ptr,
			&(img_data.bits_per_pixel), &(img_data.size_line),
			&(img_data.endian));
	pointes_renderer(head, img_data, map_data);
	draw_right_side(head, map_data, img_data, map);
	draw_below_side(map_data, img_data, map);
	win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
	tools_free.mlx_ptr = mlx_ptr;
	tools_free.win_ptr = win_ptr;
	tools_free.img_ptr = img_data.img_ptr;
	mlx_put_image_to_window(mlx_ptr, win_ptr, img_data.img_ptr, 0, 0);
	mlx_key_hook(win_ptr, &close_window_event, &tools_free);
	mlx_loop(mlx_ptr);
}
