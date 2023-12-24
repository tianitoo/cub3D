/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouvements.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:09:50 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 15:54:25 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	rotate_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->player_turn_direction = 1;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->player_turn_direction = -1;
	else
		data->player_turn_direction = 0;
	data->player_angle += data->player_turn_direction * 4;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	else if (data->player_angle < 0)
		data->player_angle += 360;
}

int	player_direction(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		return (1);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		return (-1);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		return (2);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		return (-2);
	return (0);
}

void	move_player(t_data *data)
{
	double	move_step;
	double	new_player_x;
	double	new_player_y;

	new_player_x = data->player_x;
	new_player_y = data->player_y;
	data->player_walk_direction = player_direction(data);
	if (data->player_walk_direction == 1 || data->player_walk_direction == -1)
	{
		move_step = data->player_walk_direction * 20;
		new_player_x += sin(data->player_angle * PI / 180) * move_step;
		new_player_y += cos(data->player_angle * PI / 180) * move_step;
	}
	else if (data->player_walk_direction == 2
		|| data->player_walk_direction == -2)
	{
		move_step = data->player_walk_direction * 10;
		new_player_x += cos(data->player_angle * PI / 180) * move_step;
		new_player_y -= sin(data->player_angle * PI / 180) * move_step;
	}
	if (is_valid_position(data, new_player_x, new_player_y) == 1)
	{
		data->player_x = new_player_x;
		data->player_y = new_player_y;
	}
}

int	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}
