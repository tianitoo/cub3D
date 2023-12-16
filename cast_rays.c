/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cast_rays.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:04:23 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 16:09:04 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	get_distance(t_data *data, t_ray *ray, double ray_angle)
{
	double	horizontal_distance;
	double	vertical_distance;

	data->ray_hit_vert = 0;
	data->ray_hit_horz = 0;
	horizontal_distance = get_horizontal_distance(data, ray_angle);
	vertical_distance = get_vertical_distance(data, ray_angle);
	if (horizontal_distance < vertical_distance)
	{
		ray->hit = data->ray_hit_horz;
		ray->distance = horizontal_distance;
		set_ray_direction(ray, ray_angle, HORIZONTAL);
	}
	else if (horizontal_distance > vertical_distance)
	{
		ray->hit = data->ray_hit_vert;
		ray->distance = vertical_distance;
		set_ray_direction(ray, ray_angle, VERTICAL);
	}
	else
	{
		ray->hit = data->ray_hit_horz;
		ray->distance = horizontal_distance;
		set_ray_direction(ray, ray_angle, EQUAL);
	}
}

void	cast_rays(t_data *data)
{
	double		angle;
	double		ray_angle;
	t_ray		*ray;

	ray = data->rays;
	angle = -FOV / 2;
	while (ray)
	{
		ray_angle = data->player_angle + angle;
		if (ray_angle >= 360)
			ray_angle -= 360;
		else if (ray_angle < 0)
			ray_angle += 360;
		get_distance(data, ray, ray_angle);
		ray->distance = ray->distance
			* cos((data->player_angle - ray_angle) * PI / 180);
		ray = ray->next;
		angle += (double)FOV / (double)WIN_WIDTH;
	}
}
