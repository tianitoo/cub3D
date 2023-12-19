/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendring_mouse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/19 12:08:36 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/19 12:13:04 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	ft_mouse(t_data *data)
{
	int			x;
	int			y;
	static int	x_prv;

	mlx_get_mouse_pos(data->mlx_ptr, &x, &y);
	if (x_prv != x)
		data->player_angle = (double)x / 50;
	mlx_set_cursor_mode(data->mlx_ptr, MLX_MOUSE_DISABLED);
	x_prv = x;
}

void	free_the_data(t_data *data)
{
	free_two_d(data->map);
	free(data->n_texture);
	free(data->e_texture);
	free(data->w_texture);
	free(data->s_texture);
	free(data->c_tab);
	free(data->f_tab);
}
