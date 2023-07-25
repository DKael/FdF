/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:08 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/25 17:38:11 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

int	main(int argc, char **argv)
{
	if (argc != 2)
	{
		ft_printf("Usage : %s <filename>\n", argv[0]);
		return (1);
	}
	err_init(argv);
	fdf(argv);
	return (0);
}
