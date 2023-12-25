/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 13:35:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 17:10:15 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

void	hook(void *tmp)
{
	t_data	*data;
	t_ray	*ray;
	int		i;

	data = (t_data *)tmp;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
	{
		mlx_delete_texture(data->textures[NORTH]);
		mlx_delete_texture(data->textures[WEST]);
		mlx_delete_texture(data->textures[EAST]);
		mlx_delete_texture(data->textures[SOUTH]);
		exit(0);
	}
	rotate_player(data);
	move_player(data);
	cast_rays(data);
	ray = data->rays;
	i = 0;
	while (ray)
	{
		draw_ray(data, ray, i);
		i++;
		ray = ray->next;
	}
}

void	init_window(t_data *data)
{
	mlx_image_t	*img;

	data->mlx_ptr = mlx_init(WIN_WIDTH,
			WIN_HEIGHT, "cub3D", 0);
	img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img || mlx_image_to_window(data->mlx_ptr, img, 0, 0) < 0)
	{
		printf("Error\n");
		return ;
	}
	data->img = img;
	mlx_loop_hook(data->mlx_ptr, &hook, data);
	mlx_loop(data->mlx_ptr);
}

int	import_textures(t_data *data)
{
	data->textures = malloc (sizeof(mlx_texture_t *) * 4);
	if (!data->textures)
		return (0);
	data->textures[NORTH] = mlx_load_png(data->n_texture);
	data->textures[SOUTH] = mlx_load_png(data->s_texture);
	data->textures[EAST] = mlx_load_png(data->e_texture);
	data->textures[WEST] = mlx_load_png(data->w_texture);
	if (!data->textures[NORTH] || !data->textures[SOUTH]
		|| !data->textures[EAST] || !data->textures[WEST])
	{
		if (data->textures[NORTH])
			mlx_delete_texture(data->textures[NORTH]);
		if (data->textures[SOUTH])
			mlx_delete_texture(data->textures[SOUTH]);
		if (data->textures[EAST])
			mlx_delete_texture(data->textures[EAST]);
		if (data->textures[WEST])
			mlx_delete_texture(data->textures[WEST]);
		free(data->textures);
		return (0);
	}
	return (1);
}

int	check_args(int ac, char **av, t_data *data)
{
	char	**str;
	int		j;

	if (ac < 2)
		return (printf("Error\nwrong input\n"), 0);
	if (!count_the_lines(av[1]))
		return (free(data), 0);
	j = count_the_lines(av[1]);
	str = fill_string(j, av[1]);
	if (!str)
		return (free(data), 0);
	if (!the_minimalist(str, j))
		return (free(data), free_two_d(str), 0);
	if (!inits_the_data(data, str))
	{
		free_the_data(data);
		return (free_two_d(str), free(data), 0);
	}
	if (!fail_the_inits(*data))
		return (free_the_data(data), free(data), free_two_d(str), 0);
	free_ss(str);
	free(str);
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!data)
		return (0);
	if (!check_args(ac, av, data))
		return (0);
	if (!import_textures(data))
		return (free_the_data(data), free(data), 0);
	data->player_walk_direction = 0;
	data->player_turn_direction = 0;
	if (data->player_dir == NORTH)
		data->player_angle = 270;
	else if (data->player_dir == SOUTH)
		data->player_angle = 90;
	else if (data->player_dir == EAST)
		data->player_angle = 0;
	else if (data->player_dir == WEST)
		data->player_angle = 180;
	if (!create_rays(data))
		return (0);
	init_window(data);
	return (0);
}
