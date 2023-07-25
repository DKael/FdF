/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:46:35 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_BONUS_H
# define FDF_BONUS_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "../minilibx/mlx.h"
# include "../minilibx/mlx_keycode.h"
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include "../ft_printf/ft_printf.h"

# define WINDOW_SIZE_X 1280
# define WINDOW_SIZE_Y 1024
# define ISO_X 0.866025403784439
# define ISO_Y 0.5
# define ROOT2 1.414213562373095
# define RROOT2 0.707106781186548
# define RADIAN 0.017453292519943
# define PI 3.141592653589793
# define EPSILON 0.0000000001
# define ZOOM_VALUE 1.054411903082687
# define ZOOM_LOG10 0.02301029995664
# define MOVE_FLAG 1
# define ZOOM_FLAG 2
# define ROTATE_FLAG 4
# define PROJ_FLAG 8
# define COLOR_FLAG 16
# if !defined(TRUE) && !defined(FALSE)
#  define TRUE 1
#  define FALSE 0
# endif
# ifndef T_NULL
#  define T_NULL (void *)0
# endif

typedef int	t_bool;

typedef union u_color
{
	unsigned int	color;
	unsigned char	trgb[4];
}	t_color;

typedef struct s_point
{
	double		x;
	double		y;
	double		z;
	double		tx;
	double		ty;
	double		tz;
	double		px;
	double		py;
	double		pz;
	int			rx2d;
	int			ry2d;
	double		x2d;
	double		y2d;
	t_color		color;
}	t_point;

typedef struct s_map
{
	t_point		**map;
	int			row;
	int			col;
	int			midpoint_x2d;
	int			midpoint_y2d;
	double		largest_x2d;
	double		largest_y2d;
	double		smallest_x2d;
	double		smallest_y2d;
	double		len_x2d;
	double		len_y2d;
	double		basic_len;
	int			basic_len_index;
	double		largest_z;
	double		smallest_z;
	int			fd;
	t_point		prj_ptr;
}	t_map;

typedef struct s_fdf
{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr[2];
	char	*img_addr[2];
	int		win_size_x;
	int		win_size_y;
	int		bpp[2];
	int		size_line[2];
	int		endian[2];
	t_map	*map_ptr;
	int		move_speed;
	int		x2d_move;
	int		y2d_move;
	int		rot_speed;
	int		dtheta;
	int		dphi;
	int		flag;
	t_bool	l_mouse_clk;
	t_bool	r_mouse_clk;
	int		old_x;
	int		old_y;
	int		cur_image;
	int		projection;
	int		color_mode;
	t_color	*contour_color;
}	t_fdf;

typedef struct s_angle
{
	double	sin;
	double	cos;
	double	tan;
}	t_angle;

// color_calc_bonus.c
void			make_contour_color(t_fdf *fdf, t_map *map);
t_color			*calc_color(t_color sp, t_color bp, int np);
// draw_diagonal1.c
void			draw_line_diagonal(t_fdf *fdf, t_map *map, int r, int c);
//draw1.c
void			draw(t_fdf *fdf, t_map *map);
//draw3.c
void			draw_line(t_fdf *fdf, t_point p1, t_point p2);
// error.c
void			err_init(char **argv);
void			err_msg(const char *msg, int exit_code, t_bool use_perror);
void			map_parsing_on_error(t_map *map, char **split_result);
// event1.c
int				press_cross_on_window_frame(t_fdf *fdf);
int				key_event(int key, t_fdf *fdf);
void			image_rotate(int keycode, t_fdf *fdf);
// event2.c
int				mouse_event(int button, int x, int y, t_fdf *fdf);
int				mouse_release(int button, int x, int y, t_fdf *fdf);
// event3.c
int				mouse_drag(int x, int y, t_fdf *fdf);
// fdf.c
void			fdf(char **argv);
// fdf_func_bonus.c
void			get_map_data(t_map *map);
t_bool			in_window(t_fdf *fdf, t_point p);
void			screen_clear(t_fdf *fdf, int image_num);
// map_parsing.c
t_map			map_parsing(char **argv);
// pixel_put_bonus.c
void			mlx_pixel_put_at_mem(t_fdf *fdf, int x, int y, int color);
void			mlx_pixels_put_at_mem(t_fdf *fdf,
					t_point *p_box, t_color *c_box, int num);
// point_calc_bonus.c
void			convert_point(t_map *map);
void			get_rotated_point(t_map *map, double dtheta, double dphi);
void			isometric_projection(t_map *map);
void			perspective_projection(t_map *map);
void			enlarge_image(t_map *map);
// util1.c
void			free_2d_array(void **array);
unsigned int	hex_str_to_uint(char *str_color);
t_bool			is_flat(t_point p1, t_point p2, t_point p3, t_point p4);
t_angle			calc_angle_func(int angle);
// util2.c
t_bool			should_draw_line(t_fdf *fdf, t_point p1, t_point p2);
void			fdf_init(t_fdf *fdf, t_map *map);
void			map_init(t_map *map);
void			fdf_free(t_fdf *fdf);

#endif