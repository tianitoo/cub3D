/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:59:29 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 16:13:43 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	is_wall(t_data *data, int x, int y)
{
	if (data->map[x][y] == '1')
		return (1);
	return (0);
}

int	is_out_of_map(t_data *data, double player_mini_x, double player_mini_y)
{
	if (player_mini_x <= 0 || player_mini_y <= 0
		|| player_mini_x >= data->map_height * SQUARE_SIZE
		|| player_mini_y >= data->map_width * SQUARE_SIZE)
		return (1);
	return (0);
}


int	is_valid_position(t_data *data, double new_player_x, double new_player_y)
{
	if (!is_wall(data, (new_player_x - SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y - SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x + SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y - SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x - SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y + SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x + SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y + SQUARE_SIZE / 10) / SQUARE_SIZE))
		return (1);
	return (0);
}

int	is_horiz_wall(t_data *data, double player_mini_x,
	double player_mini_y, double fov)
{
	if (is_out_of_map(data, player_mini_x, player_mini_y) == 1)
		return (1);
	if (fov >= 0 && fov < 180)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE,
				(player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 180)
	{
		if (is_wall(data, (player_mini_x - 1) / SQUARE_SIZE,
				(player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	return (0);
}

int	is_vertical_wall(t_data *data, double player_mini_x,
	double player_mini_y, double fov)
{
	if (is_out_of_map(data, player_mini_x, player_mini_y) == 1)
		return (1);
	if ((fov >= 0 && fov < 90) || fov >= 270)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE,
				(player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 90 && fov < 270)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE,
				(player_mini_y - 1) / SQUARE_SIZE) == 1)
			return (1);
	}
	return (0);
}
