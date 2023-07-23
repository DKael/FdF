/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:47:42 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/23 17:46:36 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	image_move(int keycode, t_fdf *fdf);
static void	image_rotate(int keycode, t_fdf *fdf);
static void	move_speed(int keycode, t_fdf *fdf);

int	press_cross_on_window_frame(t_fdf *fdf)
{
	free_2d_array((void *)fdf->map_ptr->map);
	free(fdf->contour_color);
	mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
	exit(0);
}

int	key_event(int key, t_fdf *fdf)
{
	if(key == LEFT_KEY || key == RIGHT_KEY || key == DOWN_KEY || key == UP_KEY)
		image_move(key, fdf);
	else if (key == A_KEY || key == S_KEY || key == D_KEY || key == W_KEY)
		image_rotate(key, fdf);
	else if (key == PL_KEY || key == MN_KEY || key == SBO_KEY || key == SBC_KEY)
		move_speed(key, fdf);
	else if (key == T_KEY)
	{
		fdf->projection = 1 - 1 * fdf->projection;
		fdf->flag |= PROJ_FLAG;
	}
	else if (key == C_KEY)
	{
		fdf->color_mode = 1 - 1 * fdf->color_mode;
		fdf->flag |= COLOR_FLAG;
	}
	else if (key == ESC_KEY)
	{
		free_2d_array((void *)fdf->map_ptr->map);
		free(fdf->contour_color);
		mlx_destroy_window(fdf->mlx_ptr, fdf->win_ptr);
		exit(0);
	}
	return (0);
}

static void	image_move(int keycode, t_fdf *fdf)
{
	if(keycode == LEFT_KEY)
		fdf->x2d_move += fdf->move_speed;
	else if(keycode == RIGHT_KEY)
		fdf->x2d_move -= fdf->move_speed;
	if(keycode == UP_KEY)
		fdf->y2d_move += fdf->move_speed;
	else if(keycode == DOWN_KEY)
		fdf->y2d_move -= fdf->move_speed;
	fdf->flag |= MOVE_FLAG;
}

static void	move_speed(int keycode, t_fdf *fdf)
{
	if (keycode == PL_KEY && fdf->move_speed < 100)
		fdf->move_speed += 1;
	else if (keycode == MN_KEY && fdf->move_speed > 0)
		fdf->move_speed -= 1;
	else if (keycode == SBC_KEY && fdf->rot_speed < 180)
		fdf->rot_speed += 1;
	else if (keycode == SBO_KEY && fdf->rot_speed > 1)
		fdf->rot_speed -= 1;
}

static void image_rotate(int keycode, t_fdf *fdf)
{
	if (keycode == S_KEY)
	{
		fdf->dtheta += fdf->rot_speed;
		if (fdf->dtheta >= 360)
			fdf->dtheta -= 360;
	}
	else if (keycode == W_KEY)
	{
		fdf->dtheta -= fdf->rot_speed;
		if (fdf->dtheta < 0)
			fdf->dtheta += 360;
	}
	if (keycode == D_KEY)
	{
		fdf->dphi += fdf->rot_speed;
		if (fdf->dphi >= 360)
			fdf->dphi -= 360;
	}
	else if (keycode == A_KEY)
	{
		fdf->dphi -= fdf->rot_speed;
		if (fdf->dphi < 0)
			fdf->dphi += 360;
	}
	fdf->flag |= ROTATE_FLAG;
}

int mouse_click(int button, int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (button == BUT1_KEY)
		{
			fdf->l_mouse_clk = TRUE;
			fdf->old_x = x;
			fdf->old_y = y;
		}
		else if (button == BUT2_KEY)
		{
			fdf->r_mouse_clk = TRUE;
			fdf->old_x = x;
			fdf->old_y = y;
		}
		if (button == SCROLLUP_KEY && fdf->map_ptr->basic_len_index < 100)
		{
			fdf->map_ptr->basic_len_index += 1;
			fdf->map_ptr->basic_len = fdf->map_ptr->basic_len * ZOOM_VALUE;
			fdf->flag |= ZOOM_FLAG;
		}
		else if (button == SCROLLDOWN_KEY && fdf->map_ptr->basic_len_index > -10)
		{
	
			fdf->map_ptr->basic_len_index -= 1;
			fdf->map_ptr->basic_len = fdf->map_ptr->basic_len / ZOOM_VALUE;
			fdf->flag |= ZOOM_FLAG;
		}
	}
	return (0);
}

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	x = x + y;
	if (button == BUT1_KEY)
		fdf->l_mouse_clk = FALSE;
	if (button == BUT2_KEY)
		fdf->r_mouse_clk = FALSE;
	return (0);
}

int	mouse_move(int x, int y, t_fdf *fdf)
{
	int	dx;
	int	dy;
	
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		if (fdf->l_mouse_clk)
		{
			dx = x - fdf->old_x;
			dy = y - fdf->old_y;
			if (dx != 0)
			{
				fdf->x2d_move += dx;
				fdf->flag |= MOVE_FLAG;
			}
			if (dy != 0)
			{
				fdf->y2d_move += dy;
				fdf->flag |= MOVE_FLAG;
			}
			fdf->old_x = x;
			fdf->old_y = y;
		}
		else if (fdf->r_mouse_clk)
		{
			dx = x - fdf->old_x;
			dy = y - fdf->old_y;
			if (dy > 0)
				image_rotate(S_KEY,fdf);
			else if (dy < 0)
				image_rotate(W_KEY,fdf);
			if (225 < fdf->dtheta || fdf->dtheta <= 45)
			{	
				if (dx > 0)
					image_rotate(A_KEY,fdf);
				else if (dx < 0)
					image_rotate(D_KEY,fdf);
			}
			else
			{
				if (dx > 0)
					image_rotate(D_KEY,fdf);
				else if (dx < 0)
					image_rotate(A_KEY,fdf);	
			}
			fdf->old_x = x;
			fdf->old_y = y;
		}
	}
	return (0);
}
