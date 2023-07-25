/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event2_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/25 15:51:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 19:13:45 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static void	mouse_click(int button, int x, int y, t_fdf *fdf);
static void	mouse_scroll(int button, int x, int y, t_fdf *fdf);

int	mouse_event(int button, int x, int y, t_fdf *fdf)
{
	if ((0 <= x && x < fdf->win_size_x) && (0 <= y && y < fdf->win_size_y))
	{
		mouse_click(button, x, y, fdf);
		mouse_scroll(button, x, y, fdf);
	}
	return (0);
}

static void	mouse_click(int button, int x, int y, t_fdf *fdf)
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
}

static void	mouse_scroll(int button, int x, int y, t_fdf *fdf)
{
	x = x + y;
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

int	mouse_release(int button, int x, int y, t_fdf *fdf)
{
	x = x + y;
	if (button == BUT1_KEY)
		fdf->l_mouse_clk = FALSE;
	if (button == BUT2_KEY)
		fdf->r_mouse_clk = FALSE;
	return (0);
}
