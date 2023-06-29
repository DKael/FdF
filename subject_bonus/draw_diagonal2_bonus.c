/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_diagonal2_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:49:14 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/28 09:51:24 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

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
