/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:41 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/06 03:20:32 by abdellah         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/fdf.h"

static Point3D	*points_placer(int number_of_lines, int array_lenght, int **map)
{
	int		i;
	int		j;
	Point3D	*point;
	Point3D	*head;

	i = 0;
	head = setup_first_node(&head, &point, map);
	j = 4;
	while (i < number_of_lines - 1)
	{
		while (j < array_lenght * 4 - 4)
		{
			point->next = store_in_node(map[i + 1][j], map[i + 1][j + 1], map[i
					+ 1][j + 2], map[i + 1][j + 3]);
			j += 4;
			point->next->next = store_in_node(map[i][j], map[i][j + 1], map[i][j
					+ 2], map[i][j + 3]);
			point = point->next->next;
		}
		j = 0;
		i++;
		point->next = store_in_node(map[i][j], map[i][j + 1], map[i][j + 2],
				map[i][j + 3]);
		point = point->next;
	}
	return (head);
}

static void	fdf(int fd, void *mlx_ptr, void **win_ptr)
{
	int		**map;
	int		array_lenght;
	int		number_of_lines;
	Point3D	*head;

	map = map_parser(fd, &array_lenght, &number_of_lines);
	head = points_placer(number_of_lines, array_lenght, map);
	free_array(map, number_of_lines);
	*win_ptr = mlx_new_window(mlx_ptr, 1000, 1000, "FDF");
	pointes_renderer(head, mlx_ptr, *win_ptr, array_lenght, number_of_lines);
}

int	main(int argc, char **argv)
{
	void	*mlx_ptr;
	void	*win_ptr;
	int		fd;
	char	*path;

	if (argc > 1)
		path = ft_strjoin("../tests/maps/test_maps/", argv[1]);
	else
	{
		perror("please provide fdf file");
		return (0);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		perror("cannot open file ,it's either non existent or the file name is wrong ,either way please use fdf maps");
		free(path);
		return (1);
	}
	free(path);
	mlx_ptr = mlx_init();
	fdf(fd, mlx_ptr, &win_ptr);
	mlx_loop(mlx_ptr);
	mlx_destroy_window(mlx_ptr, win_ptr);
	mlx_destroy_display(mlx_ptr);
	free(mlx_ptr);
	close(fd);
	return (0);
}
