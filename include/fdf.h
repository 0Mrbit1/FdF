/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abdellah <abdellah@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 02:50:26 by abdellah          #+#    #+#             */
/*   Updated: 2024/03/08 02:30:23 by abdellah         ###   ########.fr       */
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

typedef struct image_data
{
	int bits_per_pixel;
	int size_line;
	int endian;
	void *img_ptr;
} image_data ; 

typedef struct image_pixel
{
	int x;
	int y ; 
	int color ; 
} img_pxl ; 

typedef struct tools
{
	void *mlx_ptr; 
	void *img_ptr;
	void *win_ptr;
} free_tools ; 



int						**map_parser(int fd, int *l_array,
							int *number_of_lines);
void rendering_engine(Point3D *head , int array_lenght , int number_of_lines , void *mlx_ptr) ; 
int						convert_to_decimal(char *str);
void					free_array(int **hold, int y);
void					free_array_char(char **hold, int y);
int						_line_points(char **line);
Point3D					*setup_first_node(Point3D **head, Point3D **point,
							int **map);
Point3D					*store_in_node(int **map , int i , int j);
void					free_array(int **hold, int y);
double					degrees_to_radians(double angle_degrees);
void					clear_list(Point3D *head);
Point3D					*jump_to_node(Point3D *node, int skip);
void	draw_pixel(image_data img_data, char *img_cordinates, img_pxl pixel);
 void	isometric_projection(Point3D *point, int map_width, int map_lenght);
 void	initialise_array(int *coord_data, Point3D *node, Point3D *next);
 void	draw_line(Point3D *node, Point3D *next, char *img_coordinates,
		image_data img_data);
void	project(Point3D *head, int *map_data, image_data img_data,
		char *img_cordinates);