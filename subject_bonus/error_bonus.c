/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:35:27 by hyungdki          #+#    #+#             */
/*   Updated: 2023/07/02 15:59:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf_bonus.h"

static const char	*g_program_name;

void	err_init(char **argv)
{
	g_program_name = argv[0];
}

void	err_msg(const char *msg, int exit_code, t_bool use_perror)
{
	if (msg != T_NULL && use_perror == TRUE)
	{
		ft_fprintf(2, "%s: ", g_program_name);
		perror(msg);
	}
	else if (msg == T_NULL && use_perror == TRUE)
		perror(g_program_name);
	else if (msg != T_NULL && use_perror == FALSE)
		ft_fprintf(2, "%s: %s\n", g_program_name, msg);
	exit(exit_code);
}

void	map_parsing_on_error(t_map *map, char **split_result)
{
	if (map->fd != -1)
		close(map->fd);
	free_2d_array((void **)map->map);
	free_2d_array((void **)split_result);
}
