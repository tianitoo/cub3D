/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertical.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:20:05 by hnait             #+#    #+#             */
/*   Updated: 2023/11/22 00:39:35 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"


int	is_vertical_wall(t_data *data, double player_mini_x, double player_mini_y, double fov)
{
	if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
		return (1);
	if (fov >= 0 && fov < 90)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE, (player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 90 && fov < 180)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE, (player_mini_y - 1) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 180 && fov < 270)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE, (player_mini_y - 1) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 270)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE, (player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	return (0);
}

void	get_vertical_y(t_data *data, double *player_mini_y, double angle)
{
	if (*player_mini_y == data->player_y && data->checked_vertical == 0)
	{
		data->checked_vertical = 1;
		if (angle >= 90 && angle < 270)
			*player_mini_y = floor(data->player_y / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
		else
			*player_mini_y = floor(data->player_y / SQUARE_SIZE) * SQUARE_SIZE;
	}
	if (angle >= 90 && angle < 270)
		*player_mini_y -= SQUARE_SIZE;
	else
		*player_mini_y += SQUARE_SIZE;
}

void	get_vertical_x(t_data *data, double *player_mini_x, double *player_mini_y, double angle)
{
	if (*player_mini_x == data->player_x)
		*player_mini_x = data->player_x + (*player_mini_y - data->player_y) * tan((angle) * PI / 180);
	else
	{
		if (angle >= 0 && angle < 180 && (SQUARE_SIZE * tan((angle) * PI / 180)) > 0)
			*player_mini_x = *player_mini_x + (SQUARE_SIZE * tan((angle) * PI / 180));
		else if (angle >= 180 && angle < 360 && (SQUARE_SIZE * tan((angle) * PI / 180)) < 0)
			*player_mini_x = *player_mini_x + (SQUARE_SIZE * tan((angle) * PI / 180));
		else if (((angle >= 0 && angle < 180) && (SQUARE_SIZE * tan((angle) * PI / 180)) < 0) ||
			((angle >= 180 && angle < 360) && (SQUARE_SIZE * tan((angle) * PI / 180)) > 0))
			*player_mini_x = *player_mini_x - (SQUARE_SIZE * tan((angle) * PI / 180));
	}
}

void	get_vertical_x_y(t_data *data, double *player_mini_x, double *player_mini_y, double angle)
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
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
			player_mini_x += SQUARE_SIZE;
			vertical_distance += SQUARE_SIZE;
		}
		
	} else if (angle == 270)
	{
		while (is_vertical_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
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
	// ft_printf("hi\n");
	data->checked_vertical = 0;
	if (angle == 90 || angle == 270)
	{
		vertical_distance = vertical_line(data, angle);
		return (vertical_distance);
	}
	while (is_vertical_wall(data, player_mini_x, player_mini_y, angle) == 0)
	{
		get_vertical_x_y(data, &player_mini_x, &player_mini_y, angle);
		if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
			break ;
		mlx_put_pixel(data->img, player_mini_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, player_mini_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, get_rgba(255, 0, 0));
	}
	x = player_mini_x - data->player_x;
	y = player_mini_y - data->player_y;
	vertical_distance = sqrt(pow(x, 2) + pow(y, 2));
	return (vertical_distance);
}