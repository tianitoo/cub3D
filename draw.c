/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:34:34 by hnait             #+#    #+#             */
/*   Updated: 2023/12/15 17:37:55 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y)
{
	int	pixel_color;
	int	i;

	if (x >= 0 && x < texture->width && y >= 0 && y < texture->height)
	{
		i = (y * texture->width + x) * texture->bytes_per_pixel;
		pixel_color = get_rgba(texture->pixels[i], texture->pixels[i
				+ 1], texture->pixels[i + 2]);
		return (pixel_color);
	}
	return (0);
}

double	get_texture_x(t_ray *ray, t_data *data)
{
	double	pixel_x;
	int		texture_x;

	pixel_x = fmod(ray->hit, SQUARE_SIZE);
	texture_x = pixel_x * (data->textures[ray->direction]->width / SQUARE_SIZE);
	return (texture_x);
}

void	draw_background(t_data *data, int win_x, int i, t_ray *ray)
{
	if (i < ray->wall_top)
		mlx_put_pixel(data->img, win_x, i, get_rgba(data->c_tab[0],
				data->c_tab[1], data->c_tab[2]));
	if (i >= ray->wall_top + ray->wall_height)
		mlx_put_pixel(data->img, win_x, i, get_rgba(data->f_tab[0],
				data->f_tab[1], data->f_tab[2]));
}

void	draw_column(t_data *data, t_ray *ray, int win_x, int i)
{
	int	texture_x;
	int	texture_y;

	texture_x = get_texture_x(ray, data);
	while (i < WIN_HEIGHT)
	{
		if (win_x >= 0 && win_x < WIN_WIDTH && i >= 0 && i < WIN_HEIGHT)
		{
			if (i < (WIN_HEIGHT / 2) + (ray->wall_height / 2))
			{
				texture_y = (i - ray->wall_top)
					* (data->textures[ray->direction]->height
						/ ray->wall_height);
				mlx_put_pixel(data->img, win_x, i,
					get_pixel_color(data->textures[ray->direction],
						texture_x, texture_y));
			}
			draw_background(data, win_x, i, ray);
		}
		i++;
	}
}

void	draw_ray(t_data *data, t_ray *ray, int win_x)
{
	double	i;

	i = 0;
	if (win_x >= WIN_WIDTH || win_x < 0)
		return ;
	data->projected_distance = (WIN_WIDTH * 4) / tan(FOV / 2);
	if (data->projected_distance < 0)
		data->projected_distance *= -1;
	ray->wall_height = (SQUARE_SIZE / ray->distance) * data->projected_distance;
	ray->wall_top = (WIN_HEIGHT / 2) - (ray->wall_height / 2);
	draw_column(data, ray, win_x, i);
}
