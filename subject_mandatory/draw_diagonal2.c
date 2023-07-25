/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:49:14 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 14:22:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_bool	draw_line_diagonal_con4(int z00, int z01, int z10, int z11)
{
	if ((z00 < z01 && z00 < z10 && z11 > z01 && z11 > z10)
		|| (z00 > z01 && z00 > z10 && z11 < z01 && z11 < z10))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con5(int z00, int z01, int z10, int z11)
{
	if ((z00 >= z01 && z01 >= z11 && z11 >= z10)
		|| (z00 >= z10 && z10 >= z11 && z11 >= z01)
		|| (z11 >= z10 && z10 >= z00 && z00 >= z01)
		|| (z11 >= z01 && z01 >= z00 && z00 >= z10))
		return (TRUE);
	else
		return (FALSE);
}

t_bool	draw_line_diagonal_con6(int z00, int z01, int z10, int z11)
{
	if ((z01 >= z11 && z11 >= z10 && z10 >= z00)
		|| (z01 >= z00 && z00 >= z10 && z10 >= z11)
		|| (z10 >= z00 && z00 >= z01 && z01 >= z11)
		|| (z10 >= z11 && z11 >= z01 && z01 >= z00))
		return (TRUE);
	else
		return (FALSE);
}
