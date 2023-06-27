/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/27 22:11:41 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

void	image_move(int keycode, t_fdf *fdf);
void image_rotate(int keycode, t_fdf *fdf);

int	press_cross_on_window_frame(t_fdf *fdf)
{
	free_2d_array((void *)fdf->map_ptr->map);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

int	key_event(int keycode, t_fdf *fdf)
{
	if(keycode == 123 || keycode == 124 || keycode == 125
		|| keycode == 126 || keycode == 24 || keycode == 27)
		image_move(keycode, fdf);
	else if (keycode == 0 || keycode == 1 || keycode == 2
		|| keycode == 13)
		image_rotate(keycode, fdf);
	else if (keycode == 53)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	return (0);
}

void	image_move(int keycode, t_fdf *fdf)
{
	if(keycode == 124)
	{
		fdf->x2d_move -= fdf->move_value;
		fdf->loc_change = TRUE;
	}
	else if(keycode == 126)
	{
		fdf->y2d_move += fdf->move_value;
		fdf->loc_change = TRUE;
	}
	else if(keycode == 123)
	{
		fdf->x2d_move += fdf->move_value;
		fdf->loc_change = TRUE;
	}
	else if(keycode == 125)
	{
		fdf->y2d_move -= fdf->move_value;
		fdf->loc_change = TRUE;
	}
	else if (keycode == 24 && fdf->move_value < 100)
		fdf->move_value += 1;
	else if (keycode == 27 && fdf->move_value > 0)
		fdf->move_value -= 1;
}

void image_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == 13)
	{
		fdf->alpha -= 1.0;
		fdf->rotate_change = TRUE;
	}
	else if (keycode == 0)
	{
		fdf->beta += 1.0;
		fdf->rotate_change = TRUE;
	}
	else if (keycode == 1)
	{
		fdf->alpha += 1.0;
		fdf->rotate_change = TRUE;
	}
	else if (keycode == 2)
	{
		fdf->beta -= 1.0;
		fdf->rotate_change = TRUE;
	}
}

int mouse_event(int button, int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (button == 4 && fdf->map_ptr->basic_len < 200.0)
		{
			fdf->map_ptr->basic_len += 0.5;
			if (fdf->map_ptr->basic_len > 200.0)
				fdf->map_ptr->basic_len = 200.0;
			fdf->zoom_change = TRUE;
		}
		else if (button == 5 && fdf->map_ptr->basic_len > 0.0)
		{
			fdf->map_ptr->basic_len -= 0.5;
			if (fdf->map_ptr->basic_len <= 0.0)
				fdf->map_ptr->basic_len = 0.1;
			fdf->zoom_change = TRUE;
		}
	}
	return (0);
}
