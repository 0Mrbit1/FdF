/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdo1 <abdo1@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:26 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/12 05:57:28 by abdo1            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/ft_printf.h"
#include "../include/get_next_line.h"
#include "../include/libft.h"
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
}						t_Point3D;

typedef struct t_image_data
{
	int					bits_per_pixel;
	int					size_line;
	int					endian;
	void				*img_ptr;
	char				*img_cordinates;
}						t_image_data;

typedef struct image_pixel
{
	int					x;
	int					y;
	int					color;
}						t_img_pxl;

typedef struct tools
{
	void				*mlx_ptr;
	void				*img_ptr;
	void				*win_ptr;
}						t_free_tools;

int						**map_parser(int fd, int *l_array,
							int *number_of_lines);
void					rendering_engine(t_Point3D *head, int *map_data,
							void *mlx_ptr, int **map);
long					convert_to_decimal(char *str);
void					free_array(int **hold, int y);
void					free_array_char(char **hold);
int						_line_points(char **line);
t_Point3D				*setup_first_node(t_Point3D **head, t_Point3D **point,
							int **map);
t_Point3D				*store_in_node(int **map, int i, int j);
void					free_array(int **hold, int y);
double					degrees_to_radians(double angle_degrees);
void					clear_list(t_Point3D *head);
t_Point3D				*jump_to_node(t_Point3D *node, int skip);
void					draw_pixel(t_image_data img_data, t_img_pxl pixel);
void					isometric_projection(t_Point3D *point,
							int *origin_scal);
void					initialise_array(int *coord_data, t_Point3D *node,
							t_Point3D *next);
void					draw_line(t_Point3D *node, t_Point3D *next,
							t_image_data img_data);
void					project(t_Point3D *head, t_image_data img_data,
							int *origin_scal);

t_Point3D				*setup_nodes(int *map_data, int **map,
							int *origin_scal);

void					draw_below_side(int *map_data, t_image_data img_data,
							int **map, int *origin_scal);
void					draw_right_side(t_Point3D *head, int **map_data,
							t_image_data img_data, int **map);
int						check_for_chars(char **str);

int						*define_origine_scal(int **map, int *map_data);

int						*define_origine_scal(int **map, int *map_data);