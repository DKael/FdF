/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:08 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/05 17:42:27 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int main(int argc, char **argv)
{
	if (argc == 2 && argv != NULL)
	{
		t_fdf fdf;

		fdf.mlx_ptr = mlx_init();
		fdf.win_ptr = mlx_new_window(fdf.mlx_ptr, 1280, 702, "test");
		mlx_loop(fdf.mlx_ptr);
	}
}
