/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:20:05 by hnait             #+#    #+#             */
/*   Updated: 2023/12/02 17:01:34 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	get_vertical_y(t_data *data, double *player_mini_y, double angle)
{
	if (*player_mini_y == data->player_y && data->checked_vertical == 0)
	{
		data->checked_vertical = 1;
		if (angle >= 90 && angle < 270)
			*player_mini_y = floor(data->player_y / SQUARE_SIZE)
				* SQUARE_SIZE + SQUARE_SIZE;
		else
			*player_mini_y = floor(data->player_y / SQUARE_SIZE)
				* SQUARE_SIZE;
	}
	if (angle >= 90 && angle < 270)
		*player_mini_y -= SQUARE_SIZE;
	else
		*player_mini_y += SQUARE_SIZE;
}

void	get_vertical_x(t_data *data, double *player_mini_x,
	double *player_mini_y, double angle)
{
	double	step;

	step = SQUARE_SIZE * tan((angle) * PI / 180);
	if (*player_mini_x == data->player_x)
		*player_mini_x = data->player_x + (*player_mini_y - data->player_y)
			* tan((angle) * PI / 180);
	else
	{
		if (angle >= 0 && angle < 180 && step > 0)
			*player_mini_x = *player_mini_x + step;
		else if (angle >= 180 && angle < 360 && step < 0)
			*player_mini_x = *player_mini_x + step;
		else if (((angle >= 0 && angle < 180) && step < 0)
			|| ((angle >= 180 && angle < 360) && step > 0))
			*player_mini_x = *player_mini_x - step;
	}
}

void	get_vertical_x_y(t_data *data, double *player_mini_x,
	double *player_mini_y, double angle)
{
	get_vertical_y(data, player_mini_y, angle);
	get_vertical_x(data, player_mini_x, player_mini_y, angle);
}

int	vertical_line(t_data *data, double angle)
{
	double	player_mini_x;
	double	player_mini_y;
	double	vertical_distance;

	player_mini_y = data->player_y;
	player_mini_x = data->player_x;
	vertical_distance = 0;
	if (angle == 90)
	{
		while (is_vertical_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			player_mini_x += SQUARE_SIZE;
			vertical_distance += SQUARE_SIZE;
		}
	}
	else if (angle == 270)
	{
		while (is_vertical_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			player_mini_x -= SQUARE_SIZE;
			vertical_distance += SQUARE_SIZE;
		}
	}
	return (vertical_distance);
}

int	get_vertical_distance(t_data *data, double angle)
{
	double	player_mini_x;
	double	player_mini_y;
	double	vertical_distance;
	double	x;
	double	y;

	player_mini_y = data->player_y;
	player_mini_x = data->player_x;
	data->checked_vertical = 0;
	if (angle == 90 || angle == 270)
		return (vertical_line(data, angle));
	while (is_vertical_wall(data, player_mini_x, player_mini_y, angle) == 0)
	{
		get_vertical_x_y(data, &player_mini_x, &player_mini_y, angle);
		if (is_out_of_map(data, player_mini_x, player_mini_y) == 1)
			break ;
	}
	x = player_mini_x - data->player_x;
	y = player_mini_y - data->player_y;
	data->ray_hit_vert = player_mini_x;
	vertical_distance = sqrt(pow(x, 2) + pow(y, 2));
	return (vertical_distance);
}
