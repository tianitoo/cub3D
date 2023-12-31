/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 17:02:49 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 16:49:58 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	set_ray_direction(t_ray *ray, double ray_angle, int direction)
{
	if (direction == HORIZONTAL)
	{
		if (ray_angle >= 0 && ray_angle < 180)
			ray->direction = SOUTH;
		else
			ray->direction = NORTH;
	}
	else if (direction == VERTICAL)
	{
		if (ray_angle >= 90 && ray_angle < 270)
			ray->direction = WEST;
		else
			ray->direction = EAST;
	}
	else if (direction == EQUAL)
	{
		if (ray->prev)
			ray->direction = ray->prev->direction;
		else if (ray->next)
			ray->direction = ray->next->direction;
	}
}

t_ray	*new_ray(void)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->distance = 0;
	ray->direction = 0;
	ray->hit = 0;
	ray->next = NULL;
	ray->prev = NULL;
	return (ray);
}

int	free_rays(t_data *data)
{
	t_ray	*tmp;

	tmp = NULL;
	while (data->rays)
	{
		tmp = data->rays->next;
		free(data->rays);
		data->rays = tmp;
	}
	return (0);
}

void	add_ray(t_ray *tmp, t_ray *ray)
{
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = ray;
	ray->prev = tmp;
}

int	create_rays(t_data *data)
{
	int		win_width;
	t_ray	*ray;
	t_ray	*tmp;

	tmp = NULL;
	win_width = 0;
	while (win_width < WIN_WIDTH)
	{
		ray = new_ray();
		if (!ray)
			return (free_rays(data));
		if (!tmp)
		{
			data->rays = ray;
			tmp = ray;
		}
		else
			add_ray(tmp, ray);
		win_width++;
	}
	return (1);
}
