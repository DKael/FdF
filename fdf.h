/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/19 20:02:26 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"
# include "gnl/get_next_line.h"
# include "libft/libft.h"
# include "ft_printf/ft_printf.h"

# define WINDOW_SIZE_X 1280
# define WINDOW_SIZE_Y 1024
# define ISO_X 0.866025
# define ISO_Y 0.7
# if !defined(TRUE) && !defined(FALSE)
#  define TRUE 1
#  define FALSE 0
# endif
# ifndef T_NULL
#  define T_NULL (void *)0
# endif

static const char	*g_program_name;
static const char	*g_file_name;

typedef int t_bool;
typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	char	*img_addr;
	int		win_size_x;
	int		win_size_y;
	int		bpp;
	int		size_line;
	int		endian;
}	t_fdf;

typedef union u_color
{
	unsigned int	color;
	unsigned char	trgb[4];
}	t_color;

typedef struct s_point
{
	double		x;
	double		y;
	double 		z;
	int		rx_2d;
	int		ry_2d;
	double	x_2d;
	double	y_2d;
	t_color	color;
}	t_point;

typedef struct s_map
{
	t_point	**map;
	int		row;
	int		col;
	int		smallest_z;
	int		largest_z;
	int		midpoint_x_2d;
	int		midpoint_y_2d;
	double		largest_x_2d;
	double		largest_y_2d;
	double		smallest_x_2d;
	double		smallest_y_2d;
	double		len_x_2d;
	double		len_y_2d;
	double		basic_len;
	int		fd;
}	t_map;

void my_mlx_pixel_put(t_fdf *fdf, int x, int y, int color);
// unsigned int create_trgb(unsigned char t, unsigned char r, unsigned char g, unsigned char b);
// unsigned char get_t(int trgb);
// unsigned char get_r(int trgb);
// unsigned char get_g(int trgb);
// unsigned char get_b(int trgb);
void fdf_init(t_fdf *fdf);
void map_init(t_map *map);
void err_msg(const char *msg, int exit_code, t_bool use_perror);
void free_2d_array(void **array);
unsigned int hex_str_to_uint(char *str_color);
void fdf();
t_map map_parsing1();
void map_parsing2(t_map *map);
void map_parsing3(t_map *map, char **split_result, int *row_idx);
void map_parsing_on_error(t_map *map, char **split_result);
void map_parsing_make_row(t_map *map, int *row_idx, int split_idx, char **split_result);
void map_parsing_make_row_color(t_map *map, int *row_idx, int split_idx, char **split_result);
void draw_line(t_fdf *fdf, t_point p1, t_point p2);
void draw_vertical_line(t_fdf *fdf, t_point p1, t_point p2);
void draw_horizontal_line(t_fdf *fdf, t_point p1, t_point p2);
void draw_line_slope_abs1(t_fdf *fdf, t_point p1, t_point p2);
void draw_line_move_x(t_fdf *fdf, t_point p1, t_point p2);
void draw_line_move_y(t_fdf *fdf, t_point p1, t_point p2);
#endif