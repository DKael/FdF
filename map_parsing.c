/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 19:35:35 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/26 20:02:06 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_map	map_parsing1(void)
{
	t_map	map;
	char	*buffer;

	map_init(&map);
	buffer = T_NULL;
	map.fd = open(g_file_name, O_RDONLY);
	if (map.fd == -1)
		err_msg(g_file_name, 1, TRUE);
	while (1)
	{
		buffer = get_next_line(map.fd);
		if (buffer == T_NULL || buffer[0] == '\n')
			break ;
		map.row++;
		free(buffer);
	}
	close(map.fd);
	if (map.row == 0)
		err_msg("No line exist!", 1, FALSE);
	map.map = (t_point **)ft_calloc(map.row + 1, sizeof(t_point *));
	if (map.map == T_NULL)
		err_msg("malloc error!", 1, FALSE);
	map_parsing2(&map);
	close(map.fd);
	return (map);
}

void	map_parsing2(t_map *map)
{
	int		map_r_idx;
	char	**split_result;
	char	*buffer;

	map->fd = open(g_file_name, O_RDONLY);
	if (map->fd == -1)
	{
		free(map->map);
		err_msg(g_file_name, 1, TRUE);
	}
	map_r_idx = -1;
	while (1)
	{
		buffer = get_next_line(map->fd);
		if (buffer == T_NULL)
			break ;
		split_result = ft_split(buffer, ' ');
		free(buffer);
		if (split_result == T_NULL)
		{
			map_parsing_on_error(map, split_result);
			err_msg("malloc error!", 1, FALSE);
		}
		map_parsing3(map, split_result, &map_r_idx);
	}
}

void	map_parsing3(t_map *map, char **split_result, int *r_idx)
{
	int	s_idx;

	s_idx = 0;
	while (split_result[s_idx] != T_NULL && split_result[s_idx][0] != '\n')
		s_idx++;
	if (map->col != 0 && map->col <= s_idx)
		mp_make_row(map, r_idx, s_idx, split_result);
	else if (map->col != 0 && map->col > s_idx)
	{
		map_parsing_on_error(map, split_result);
		err_msg("Found wrong line length!\n", 1, FALSE);
	}
	else if (map->col == 0)
	{
		if (s_idx != 0)
		{
			map->col = s_idx;
			mp_make_row(map, r_idx, s_idx, split_result);
		}
		else
		{
			map_parsing_on_error(map, split_result);
			err_msg("Empty liine!", 1, FALSE);
		}
	}
}

void	mp_make_row(t_map *map, int *r_idx, int s_idx, char **split_result)
{
	map->map[++(*r_idx)] = (t_point *)malloc(sizeof(t_point) * s_idx);
	if (map->map[*r_idx] == T_NULL)
	{
		map_parsing_on_error(map, split_result);
		err_msg("malloc error!", 1, FALSE);
	}
	s_idx = -1;
	while (split_result[++s_idx] != T_NULL && split_result[s_idx][0] != '\n')
	{
		if (ft_strstr(split_result[s_idx], ",") != T_NULL)
			mp_make_row_color(map, r_idx, s_idx, split_result);
		else
		{
			map->map[*r_idx][s_idx].z = ft_atoi_int(split_result[s_idx]);
			if (map->map[*r_idx][s_idx].z == 0 && split_result[s_idx][0] != '0')
			{
				map_parsing_on_error(map, split_result);
				err_msg("Wrong range of integer value!", 1, FALSE);
			}
			map->map[*r_idx][s_idx].color.color = 0xFFFFFF;
		}
	}
	free_2d_array((void **)split_result);
}

void	mp_make_row_color(t_map *map, int *r_idx, int s_idx, char **s_result)
{
	char	**split_color;

	split_color = ft_split(s_result[s_idx], ',');
	if (split_color == T_NULL)
	{
		map_parsing_on_error(map, s_result);
		err_msg("malloc error!", 1, FALSE);
	}
	map->map[*r_idx][s_idx].z = ft_atoi_int(split_color[0]);
	if (map->map[*r_idx][s_idx].z == 0 && split_color[0][0] != '0')
	{
		map_parsing_on_error(map, s_result);
		free_2d_array((void **)split_color);
		err_msg("Wrong range of integer value!", 1, FALSE);
	}
	map->map[*r_idx][s_idx].color.color = hex_str_to_uint(split_color[1]);
	free_2d_array((void **)split_color);
}
