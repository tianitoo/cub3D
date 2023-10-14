/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:47 by hnait             #+#    #+#             */
/*   Updated: 2023/10/14 11:48:19 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	is_wall(t_data *data, int x, int y)
{
	if (data->map[x][y] == '1')
		return (1);
	return (0);
}

void	get_next_horizontal_y(t_data *data, double *player_mini_y, double *player_mini_x, double fov)
{
	fov = fov + data->player_angle;
	if (fov >= 360)
		fov -= 360;
	else if (fov < 0)
		fov += 360;
	if (*player_mini_y == data->player_x)
		*player_mini_y = data->player_y + (*player_mini_x - data->player_x) / tan((fov) * PI / 180);
	else
	{
		if (fov >= 90 && fov < 270 && (SQUARE_SIZE / tan((fov) * PI / 180)) > 0)
			*player_mini_y = *player_mini_y - (SQUARE_SIZE / tan((fov) * PI / 180));
		else if ((fov < 90 || fov >= 270) && (SQUARE_SIZE / tan((fov) * PI / 180)) < 0)
			*player_mini_y = *player_mini_y - (SQUARE_SIZE / tan((fov) * PI / 180));
		else
			*player_mini_y = *player_mini_y + (SQUARE_SIZE / tan((fov) * PI / 180));
	}
}

void	get_next_horizontal_x(t_data *data, double *player_mini_x, double fov)
{
	fov = fov + data->player_angle;
	if (fov >= 360)
		fov -= 360;
	else if (fov < 0)
		fov += 360;
	*player_mini_x = floor(*player_mini_x / SQUARE_SIZE) * SQUARE_SIZE;
	if (fov >= 0 && fov < 180)
		*player_mini_x += SQUARE_SIZE;
	else
		*player_mini_x -= SQUARE_SIZE;
}

void	get_horizontal_x_y(t_data *data, double *player_mini_x, double *player_mini_y, double fov)
{
	get_next_horizontal_x(data, player_mini_x, fov);
	get_next_horizontal_y(data, player_mini_y, player_mini_x, fov);
}

void	get_next_vertical_x(t_data *data, double *player_mini_x, double *player_mini_y, double fov)
{
	fov = fov + data->player_angle;
	if (fov >= 360)
		fov -= 360;
	else if (fov < 0)
		fov += 360;
	if (*player_mini_x == data->player_y)
		*player_mini_x = data->player_x + (*player_mini_y - data->player_y) * tan((fov) * PI / 180);
	else
	{
		if (fov >= 0 && fov < 180 && (SQUARE_SIZE * tan((fov) * PI / 180)) > 0)
			*player_mini_x = *player_mini_x + (SQUARE_SIZE * tan((fov) * PI / 180));
		else if (fov >= 180 && fov < 360 && (SQUARE_SIZE * tan((fov) * PI / 180)) < 0)
			*player_mini_x = *player_mini_x + (SQUARE_SIZE * tan((fov) * PI / 180));
		else
			*player_mini_x = *player_mini_x - (SQUARE_SIZE * tan((fov) * PI / 180));
	}
}

void	get_next_vertical_y(t_data *data, double *player_mini_y, double fov)
{
	fov = fov + data->player_angle;
	if (fov >= 360)
		fov -= 360;
	else if (fov < 0)
		fov += 360;
	*player_mini_y = floor(*player_mini_y / SQUARE_SIZE) * SQUARE_SIZE;
	if (fov >= 90 && fov < 270)
		*player_mini_y -= SQUARE_SIZE;
	else
		*player_mini_y += SQUARE_SIZE;
}

void	get_vertical_x_y(t_data *data, double *player_mini_x, double *player_mini_y, double fov)
{
	get_next_vertical_y(data, player_mini_y, fov);
	get_next_vertical_x(data, player_mini_x, player_mini_y, fov);
}

void	draw_fov(t_data *data, double player_mini_x, double player_mini_y)
{
	// int		j;
	int		color;
	double		fov;
	t_ray		*ray;
	t_ray		*tmp;
	double		distance_horizontal;
	double		distance_vertical;

	data->rays = NULL;
	fov = -FOV / 2;
	color = get_rgba(255, 0, 0);
	while (fov < FOV / 2)
	{
		player_mini_y = data->player_y;
		player_mini_x = data->player_x;
		while (is_wall(data, player_mini_x / SQUARE_SIZE, player_mini_y / SQUARE_SIZE) == 0)
		{
			get_horizontal_x_y(data, &player_mini_x, &player_mini_y, fov);
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
			mlx_put_pixel(data->img, player_mini_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, player_mini_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, color);
		}
		distance_horizontal = 10000000000;//sqrt(pow(player_mini_x - data->player_x, 2) + pow(player_mini_y - data->player_y, 2));
		player_mini_x = data->player_x;
		player_mini_y = data->player_y;
		while (is_wall(data, player_mini_x / SQUARE_SIZE, player_mini_y / SQUARE_SIZE) == 0)
		{
			get_vertical_x_y(data, &player_mini_x, &player_mini_y, fov);
			if (player_mini_x <= 0 || player_mini_y <= 0 || player_mini_x >= data->map_height * SQUARE_SIZE || player_mini_y >= data->map_width * SQUARE_SIZE)
				break ;
			mlx_put_pixel(data->img, player_mini_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, player_mini_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE, color);
		}
		distance_vertical = sqrt(pow(player_mini_x - data->player_x, 2) + pow(player_mini_y - data->player_y, 2));
		ray = (t_ray *)malloc(sizeof(t_ray));
		if (distance_horizontal < distance_vertical)
			ray->distance = distance_horizontal;
		else
			ray->distance = distance_vertical;
		ray->next = NULL;
		tmp = data->rays;
		if (!tmp)
			data->rays = ray;
		else
		{
				while (tmp->next)
					tmp = tmp->next;
				tmp->next = ray;
		}
		fov += 0.1;
	}
}

void	draw_player(t_data *data)
{
	int		i;
	int		j;
	int		color;
	int		player_mini_x;
	int		player_mini_y;

	player_mini_x = data->player_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE - MINIMAP_SQUARE_SIZE / 2;
	player_mini_y = data->player_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE - MINIMAP_SQUARE_SIZE / 2;
	i = 0;
	while (i < MINIMAP_SQUARE_SIZE)
	{
		j = 0;
		while (j < MINIMAP_SQUARE_SIZE)
		{
			color = get_rgba(0, 255, 0);
			mlx_put_pixel(data->img, player_mini_y + j, player_mini_x + i, color);
			j++;
		}
		i++;
	}
}

void	draw_2d_map(t_data *data)
{
	int		i;
	int		j;
	int		color;
	int		player_x;
	int		player_y;
	double		player_mini_x;
	double		player_mini_y;

	player_x = data->player_x / SQUARE_SIZE * MINIMAP_SQUARE_SIZE;
	player_y = data->player_y / SQUARE_SIZE * MINIMAP_SQUARE_SIZE;
	i = 0;
	while (player_x + i < player_x + MAP_HEIGHT)
	{
		j = 0;
		while (player_y + j < player_y + MAP_WIDTH)
		{
			// ft_printf("i = %d, j = %d\n", i / MINIMAP_SQUARE_SIZE, j / MINIMAP_SQUARE_SIZE);
			if (i >= data->map_height * MINIMAP_SQUARE_SIZE || j >= data->map_width * MINIMAP_SQUARE_SIZE)
				color = get_rgba(0, 0, 0);
			else if (data->map[i / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE] == '1')
				color = get_rgba(255, 255, 255);
			else if (data->map[i / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE] == '0')
				color = get_rgba(0, 0, 0);
			// ft_printf("i = %d, j = %d\n", i, j);
			if (i == player_x / MINIMAP_SQUARE_SIZE && j == player_y / MINIMAP_SQUARE_SIZE)
			{
				player_mini_x = i;
				player_mini_y = j;
			}
			mlx_put_pixel(data->img, j, i, color);
			j++;
		}
		i++;
	}
	draw_player(data);
	draw_fov(data, player_mini_x, player_mini_y);
}

void	draw_ray(t_data *data, t_ray *ray, int win_x)
{
	int	color;
	double	i;
	double	projection_distance;
	double	wall_height;
	double	wall_top;

	i = 0;
	projection_distance = (WIN_WIDTH * 4) / tan(FOV / 2);
	if (projection_distance < 0)
		projection_distance *= -1;
	// printf("projection_distance = %f\n", projection_distance);
	wall_height = (SQUARE_SIZE / ray->distance) * projection_distance;
	// printf("wall_height = %f\n", wall_height);
	while (i < WIN_HEIGHT / 2)
	{
		// ft_printf("i = %d < %dd\n", i, (WIN_HEIGHT / 2) - (wall_height / 2));
		wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
		if (i < wall_top)
			color = get_rgba(0, 0, 0);
		else
			color = get_rgba(255, 0, 0);
		mlx_put_pixel(data->img, win_x + MAP_WIDTH, i, color);
		mlx_put_pixel(data->img, win_x + MAP_WIDTH, WIN_HEIGHT - i - 1, color);
		i = i + 1;
	}
}

void	draw_3d_map(t_data *data)
{
	t_ray	*ray;
	int		i;
	int		ii;

	ray = data->rays;
	i = 0;
	while (ray)
	{
		ii = i;
		while (i < ii + 2)
		{
			draw_ray(data, ray, i);
			i++;
		}
		ray = ray->next;
	}
	
}

void	draw(t_data *data)
{
	draw_2d_map(data);
	// print all rays
	// int i = 0;
	// t_ray	*ray;
	// ray = data->rays;
	// while (ray)
	// {
	// 	printf("ray id = %d, ray angle = %f, ray distance = %f\n", ray->id, ray->angle, ray->distance);
	// 	ray = ray->next;
	// }
	// exit(0);
	draw_3d_map(data);
}

void	rotate_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->player_turn_direction = 3;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->player_turn_direction = -3;
	else
		data->player_turn_direction = 0;
	data->player_angle += data->player_turn_direction;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	else if (data->player_angle < 0)
		data->player_angle += 360;
}


void	move_player(t_data *data)
{
	double	move_step;
	double	new_player_x;
	double	new_player_y;

	new_player_x = data->player_x;
	new_player_y = data->player_y;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		data->player_walk_direction = 1;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		data->player_walk_direction = -1;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		data->player_walk_direction = 2;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		data->player_walk_direction = -2;
	else
		data->player_walk_direction = 0;
	move_step = data->player_walk_direction * 5;
	if (data->player_walk_direction == 1 || data->player_walk_direction == -1)
	{
		new_player_x += sin(data->player_angle * PI / 180) * move_step * 2;
		new_player_y += cos(data->player_angle * PI / 180) * move_step * 2;
	}
	else if (data->player_walk_direction == 2 || data->player_walk_direction == -2)
	{
		new_player_x += cos(data->player_angle * PI / 180) * move_step;
		new_player_y -= sin(data->player_angle * PI / 180) * move_step;
	}
	else
		return ;
	if (!is_wall(data, (new_player_x - SQUARE_SIZE / 2) / SQUARE_SIZE, (new_player_y - SQUARE_SIZE / 2) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x + SQUARE_SIZE / 2) / SQUARE_SIZE, (new_player_y - SQUARE_SIZE / 2) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x - SQUARE_SIZE / 2) / SQUARE_SIZE, (new_player_y + SQUARE_SIZE / 2) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x + SQUARE_SIZE / 2) / SQUARE_SIZE, (new_player_y + SQUARE_SIZE / 2) / SQUARE_SIZE)
	)
	{
		data->player_x = new_player_x;
		data->player_y = new_player_y;
	}
}

void	hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		exit(0);
	rotate_player(data);
	move_player(data);
	draw(data);
	
}

void	init_window(t_data *data)
{
	mlx_image_t	*img;
	
	data->mlx_ptr = mlx_init(WIN_WIDTH,
			WIN_HEIGHT, "cub3D", 1);
	img = mlx_new_image(data->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	
	if (!img || mlx_image_to_window(data->mlx_ptr, img, 0, 0) < 0)
	{
		ft_printf("Errord\n");
		return ;
	}
	data->img = img;
	mlx_loop_hook(data->mlx_ptr, &hook, data);
	mlx_loop(data->mlx_ptr);
}

int	main(void)
{
	int		fd;
	char	*line;
	char	**map;
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	map = (char **)malloc(sizeof(char *) * 110);
	fd = open("maps/map.cub", O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error\n");
		return (0);
	}
	i = 0;
	line = get_next_line(fd);
	// exit(0);
	data->map_width = 0;
	data->map_height = 0;
	while (line)
	{
		data->map_height++;
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (line && line[0] == '1')
		{
			if (data->map_width < (int) ft_strlen(line))
				data->map_width = ft_strlen(line);
		}
		map[i] = line;
		line = get_next_line(fd);
		i++;
	}
	map[i] = NULL;
	data->map = map;
	close(fd);
	int j = 0;
	i = 0;
	data->player_dir = -1;
	while (map[i])
	{
		j = 0;
		while (map[i][j])
		{
			if (map[i][j] == 'N')
				data->player_dir = NORTH;
			else if (map[i][j] == 'S')
				data->player_dir = SOUTH;
			else if (map[i][j] == 'E')
				data->player_dir = EAST;
			else if (map[i][j] == 'W')
				data->player_dir = WEST;
			if (data->player_dir != -1)
				break ;
			j++;
		}
		if (data->player_dir != -1)
			break ;
		i++;
	}
	data->player_x = i * SQUARE_SIZE + SQUARE_SIZE / 2;
	data->player_y = j * SQUARE_SIZE + SQUARE_SIZE / 2;
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
	// sleep(2);
	init_window(data);
	return (0);
}
