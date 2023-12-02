/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:47 by hnait             #+#    #+#             */
/*   Updated: 2023/12/02 17:58:34 by hnait            ###   ########.fr       */
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
		exit(0);
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
			WIN_HEIGHT, "cub3D", 1);
	img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (!img || mlx_image_to_window(data->mlx_ptr, img, 0, 0) < 0)
	{
		ft_printf("Error\n");
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
	data->textures[NORTH] = mlx_load_png("textures/N.png");
	data->textures[SOUTH] = mlx_load_png("textures/S.png");
	data->textures[EAST] = mlx_load_png("textures/E.png");
	data->textures[WEST] = mlx_load_png("textures/W.png");
	return (1);
}

int	check_args(int ac, char **av, t_data *data)
{
	char	**str;
	int		j;

	if (ac != 2 || !count_the_lines(av[1]))
		return (printf("NOT VALID1\n"), 0);
	j = count_the_lines(av[1]);
	str = fill_string(j, av[1]);
	if (!the_minimalist(str, j))
	{
		printf("NOT VALID\n");
		return (free_two_d(str), 0);
	}
	if (!inits_the_data(data, str))
	{
		printf("NOT VALID2\n");
		return (0);
	}
	if (!fail_the_inits(*data))
	{
		printf("NOT VALID3\n");
		return (0);
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	if (!check_args(ac, av, data))
		return (0);
	printf("VALID\n");
	if (!import_textures(data))
		return (0);
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
