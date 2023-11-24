/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   horizontal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/23 16:20:47 by hnait             #+#    #+#             */
/*   Updated: 2023/11/24 15:51:55 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"


int	is_horizontal_wall(t_data *data, double player_mini_x, double player_mini_y, double fov)
{
	if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
		return (1);
	if (fov >= 0 && fov < 180)
	{
		if (is_wall(data, (player_mini_x) / SQUARE_SIZE, (player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	if (fov >= 180)
	{
		if (is_wall(data, (player_mini_x - 1) / SQUARE_SIZE, (player_mini_y) / SQUARE_SIZE) == 1)
			return (1);
	}
	return (0);
}

void	get_horizontal_x(t_data *data, double *player_mini_x, double angle)
{
	
	if (*player_mini_x == data->player_x && data->checked_horizontal == 0)
	{
		data->checked_horizontal = 1;
		if (angle >= 0 && angle < 180)
			*player_mini_x = floor(data->player_x / SQUARE_SIZE) * SQUARE_SIZE;
		else
			*player_mini_x = floor(data->player_x / SQUARE_SIZE) * SQUARE_SIZE + SQUARE_SIZE;
	}
	if (angle >= 0 && angle < 180)
		*player_mini_x += SQUARE_SIZE;
	else
		*player_mini_x -= SQUARE_SIZE;
}

void	get_horizontal_y(t_data *data, double *player_mini_y, double *player_mini_x, double angle)
{
	if (*player_mini_y == data->player_y)
		*player_mini_y = data->player_y + (*player_mini_x - data->player_x) / tan((angle) * PI / 180);
	else
	{
		if (angle > 90 && angle < 270 && (SQUARE_SIZE / tan((angle) * PI / 180)) > 0)
			*player_mini_y = *player_mini_y - (SQUARE_SIZE / tan((angle) * PI / 180));
		else if ((angle < 90 || angle > 270) && (SQUARE_SIZE / tan((angle) * PI / 180)) < 0)
			*player_mini_y = *player_mini_y - (SQUARE_SIZE / tan((angle) * PI / 180));
		else if (((angle < 90 || angle > 270) && (SQUARE_SIZE / tan((angle) * PI / 180)) > 0) ||
			(angle > 90 && angle < 270 && (SQUARE_SIZE / tan((angle) * PI / 180)) < 0))
			*player_mini_y = *player_mini_y + (SQUARE_SIZE / tan((angle) * PI / 180));
	}
}

void	get_horizontal_x_y(t_data *data, double *player_mini_x, double *player_mini_y, double angle)
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
		while (is_horizontal_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
			player_mini_y += SQUARE_SIZE;
			horizontal_distance += SQUARE_SIZE;
		}
	}
	else if (angle == 180)
	{
		while (is_horizontal_wall(data, player_mini_x, player_mini_y, angle) == 0)
		{
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
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
	{
		horizontal_distance = horizontal_line(data, angle);
		return (horizontal_distance);
	}
	while (is_horizontal_wall(data, player_mini_x, player_mini_y, angle) == 0)
	{
		get_horizontal_x_y(data, &player_mini_x, &player_mini_y, angle);
		if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
			break ;
		mlx_put_pixel(data->img, player_mini_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, player_mini_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, get_rgba(255, 0, 0));
	}
	x = player_mini_x - data->player_x;
	y = player_mini_y - data->player_y;
	data->ray_hit_horz = player_mini_y;
	// printf("ray_hit_horz = %f\n", player_mini_x);
	
	horizontal_distance = sqrt(pow(x, 2) + pow(y, 2));
	return (horizontal_distance);
}
