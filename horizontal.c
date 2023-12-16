/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:20:47 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 17:30:14 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	get_horizontal_x(t_data *data, double *player_mini_x, double angle)
{
	if (*player_mini_x == data->player_x && data->checked_horizontal == 0)
	{
		data->checked_horizontal = 1;
		if (angle >= 0 && angle < 180)
			*player_mini_x = floor(data->player_x / SQUARE_SIZE)
				* SQUARE_SIZE;
		else
			*player_mini_x = floor(data->player_x / SQUARE_SIZE)
				* SQUARE_SIZE + SQUARE_SIZE;
	}
	if (angle >= 0 && angle < 180)
		*player_mini_x += SQUARE_SIZE;
	else
		*player_mini_x -= SQUARE_SIZE;
}

void	get_horizontal_y(t_data *data, double *player_mini_y,
	double *player_mini_x, double angle)
{
	double	step;

	if (*player_mini_y == data->player_y)
	{
		step = (*player_mini_x - data->player_x) / tan((angle) * PI / 180);
		*player_mini_y = data->player_y + step;
	}
	else
	{
		step = SQUARE_SIZE / tan((angle) * PI / 180);
		if (angle > 90 && angle < 270 && step > 0)
			*player_mini_y = *player_mini_y - step;
		else if ((angle < 90 || angle > 270) && step < 0)
			*player_mini_y = *player_mini_y - step;
		else if (((angle < 90 || angle > 270) && step > 0)
			|| (angle > 90 && angle < 270 && step < 0))
			*player_mini_y = *player_mini_y + step;
	}
}

void	get_horizontal_x_y(t_data *data, double *player_mini_x,
	double *player_mini_y, double angle)
{
	get_horizontal_x(data, player_mini_x, angle);
	get_horizontal_y(data, player_mini_y, player_mini_x, angle);
}

int	horizontal_line(t_data *data, double angle)
{
	double	player_mini_x;
	double	player_mini_y;
	double	horizontal_distance;

	player_mini_y = data->player_y;
	player_mini_x = data->player_x;
	horizontal_distance = 0;
	if (angle == 0)
	{
		while (is_horiz_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			player_mini_y += SQUARE_SIZE;
			horizontal_distance += SQUARE_SIZE;
		}
	}
	else if (angle == 180)
	{
		while (is_horiz_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			player_mini_y -= SQUARE_SIZE;
			horizontal_distance += SQUARE_SIZE;
		}
	}
	return (horizontal_distance);
}

int	get_horizontal_distance(t_data *data, double angle)
{
	double	player_mini_x;
	double	player_mini_y;
	double	horizontal_distance;
	double	x;
	double	y;

	player_mini_y = data->player_y;
	player_mini_x = data->player_x;
	data->checked_horizontal = 0;
	if (angle == 0 || angle == 180)
		return (horizontal_line(data, angle));
	while (is_horiz_wall(data, player_mini_x, player_mini_y, angle) == 0)
	{
		get_horizontal_x_y(data, &player_mini_x, &player_mini_y, angle);
		if (is_out_of_map(data, player_mini_x, player_mini_y) == 1)
			break ;
	}
	x = player_mini_x - data->player_x;
	y = player_mini_y - data->player_y;
	data->ray_hit_horz = player_mini_y;
	horizontal_distance = sqrt(pow(x, 2) + pow(y, 2));
	return (horizontal_distance);
}
