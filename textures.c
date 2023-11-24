/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/22 17:34:34 by hnait             #+#    #+#             */
/*   Updated: 2023/11/23 21:33:48 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int texture_pixel(t_data *data, t_ray *ray, int i, double wall_height)
{
	int pixel_x;
	int pixel_y;
	int color;
	int red;
	int green;
	int blue;

	// printf("ray_hit_vert = %f\n", data->ray_hit_vert);

	// if (data->ray_hit_vert)
		pixel_y = fmod(ray->hit, SQUARE_SIZE) * data->textures[EAST]->width / SQUARE_SIZE;
	// else
	// 	pixel_y = ((int)ray->hit % SQUARE_SIZE) * data->textures[WEST]->width / SQUARE_SIZE;
	// ft_printf("0 = %d\n", 0);
	pixel_x = (int)(i * data->textures[WEST]->height / wall_height);
	// printf("pixel_x = %d\n", pixel_y);
	red = data->textures[WEST]->pixels[pixel_x * data->textures[WEST]->width * 4 + pixel_y];
	green = data->textures[WEST]->pixels[pixel_x * data->textures[WEST]->width * 4 + pixel_y + 1];
	blue = data->textures[WEST]->pixels[pixel_x * data->textures[WEST]->width * 4 + pixel_y + 2];

	color = get_rgba(red, green, blue);
	// ft_printf("color = %d\n", color);
	return (color);
}
