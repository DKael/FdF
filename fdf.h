/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyungdki <hyungdki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 17:58:15 by hyungdki          #+#    #+#             */
/*   Updated: 2023/06/05 17:07:55 by hyungdki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include <unistd.h>
# include <fcntl.h>
# include <string.h>
# include <stdlib.h>
# include <stdio.h>
# include <math.h>
# include "minilibx/mlx.h"

# define T_NULL (void *)0 

typedef struct s_fdf{
	void	*mlx_ptr;
	void	*win_ptr;
	void	*img_ptr;
	int		size_x;
	int		size_y;

}	t_fdf;

#endif