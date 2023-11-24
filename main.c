/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:47 by hnait             #+#    #+#             */
/*   Updated: 2023/11/24 15:13:28 by hnait            ###   ########.fr       */
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

void	draw_fov(t_data *data)
{
	int		color;
	double		angle;
	double		ray_angle;
	t_ray		*ray;
	double		horizontal_distance;
	double		vertical_distance;

	ray = data->rays;
	angle = -FOV / 2;
	
	color = get_rgba(255, 0, 0);
	while (ray)
	{
		ray_angle = data->player_angle + angle;
		if (ray_angle >= 360)
			ray_angle -= 360;
		else if (ray_angle < 0)
			ray_angle += 360;
		horizontal_distance = get_horizontal_distance(data, ray_angle);
		vertical_distance =  get_vertical_distance(data, ray_angle);
		if (horizontal_distance < vertical_distance)
		{
			data->ray_hit_vert = 0;
			ray->hit = data->ray_hit_horz;
			// printf("ray_hit_horz = %f\n", data->ray_hit_horz);
			ray->distance = horizontal_distance;
			if (ray_angle >= 0 && ray_angle < 180)
				ray->direction = SOUTH;
			else
				ray->direction = NORTH;
		}
		else if (horizontal_distance > vertical_distance)
		{
			data->ray_hit_horz = 0;
			ray->hit = data->ray_hit_vert;
			ray->distance = vertical_distance;
			if (ray_angle >= 90 && ray_angle < 270)
				ray->direction = WEST;
			else
				ray->direction = EAST;
		}
		else
		{
			data->ray_hit_vert = 0;
			ray->hit = data->ray_hit_horz;
			ray->distance = horizontal_distance;
			if (ray->prev)
				ray->direction = ray->prev->direction;
			else if (ray->next)
				ray->direction = ray->next->direction;
		}
		ray->distance = ray->distance * cos((data->player_angle - ray_angle) * PI / 180);
		ray = ray->next;
		angle += 0.0625;
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
			color = get_rgba(255, 255, 255);
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
	draw_fov(data);
}

int	get_pixel_color(mlx_texture_t *tex_data, uint32_t x, uint32_t y)
{
	int	pixel_color;
	int	index;

	if (x >= 0 && x < tex_data->width && y >= 0 && y < tex_data->height)
	{
		index = (y * tex_data->width + x) * tex_data->bytes_per_pixel;
		pixel_color = get_rgba(tex_data->pixels[index], tex_data->pixels[index
				+ 1], tex_data->pixels[index + 2]);
	}
	else
		pixel_color = get_rgba(0, 0, 0);
	return (pixel_color);
}

void	draw_ray(t_data *data, t_ray *ray, int win_x)
{
	// int	color;
	double	i;
	double	projection_distance;
	double	wall_height;
	double	wall_top;
	double	tile_x;
	double	tex_x;
	double	tex_y;
	
	i = 0;
	if (win_x >= WIN_WIDTH || win_x < 0)
		return ;
	projection_distance = (WIN_WIDTH * 4) / tan(FOV / 2);
	if (projection_distance < 0)
		projection_distance *= -1;
	// printf("projection_distance = %f\n", projection_distance);
	wall_height = (SQUARE_SIZE / ray->distance) * projection_distance;
	// printf("wall_height = %f\n", wall_height);
	wall_top = (WIN_HEIGHT / 2) - (wall_height / 2);
	if (ray->direction == NORTH || ray->direction == SOUTH)
		tile_x = fmod(ray->hit, SQUARE_SIZE);
	else
		tile_x = fmod(ray->hit, SQUARE_SIZE);
	tex_x = tile_x * (data->textures[ray->direction]->width / SQUARE_SIZE);
	while (i < WIN_HEIGHT)
	{
		if (win_x >= 0 && win_x < WIN_WIDTH && i >= 0 && i < WIN_HEIGHT)
		{
			if (i < wall_top)
				mlx_put_pixel(data->img, win_x, i, get_rgba(100, 150, 255));
			if (i >= wall_top + wall_height)
				mlx_put_pixel(data->img, win_x, i, get_rgba(100, 200, 150));
			if (i < (WIN_HEIGHT / 2) + (wall_height / 2))
			{
				tex_y = (i - wall_top) * (data->textures[ray->direction]->height / wall_height);
				mlx_put_pixel(data->img, win_x, i, get_pixel_color(data->textures[ray->direction], tex_x, tex_y));
			}
		}
		i++;
	}
}

// void	draw_line_texture(t_game_data *game, t_ray *ray, double height,
// 		int texture)
// {
// 	double	tile_x;
// 	double	tex_x;
// 	double	tex_y;
// 	double	y_start;
// 	double	y;

// 	y_start = (WINDOW_HEIGHT / 2) - (height / 2);
// 	if (texture == NORTH || texture == SOUTH)
// 		tile_x = fmod(ray->wall_hit_x, SQUARE_SIZE);
// 	else
// 		tile_x = fmod(ray->wall_hit_y, SQUARE_SIZE);
// 	tex_x = tile_x * (game->map->textures[texture]->width / SQUARE_SIZE);
// 	y = y_start;
// 	while (y < (WINDOW_HEIGHT / 2) + (height / 2))
// 	{
// 		if (ray->id >= 0 && ray->id < WINDOW_WIDTH && y >= 0
// 			&& y < WINDOW_HEIGHT)
// 		{
// 			tex_y = (y - y_start) * (game->map->textures[texture]->height
// 					/ height);
// 			mlx_put_pixel(game->img, ray->id, y,
// 				get_pixel_color(game->map->textures[texture], tex_x, tex_y));
// 		}
// 		y++;
// 	}
// }

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
	draw_3d_map(data);
	draw_2d_map(data);
}

void	rotate_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->player_turn_direction = 1;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->player_turn_direction = -1;
	else
		data->player_turn_direction = 0;
		
	data->player_angle += data->player_turn_direction * 5;
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
	move_step = data->player_walk_direction ;
	if (data->player_walk_direction == 1 || data->player_walk_direction == -1)
	{
		new_player_x += sin(data->player_angle * PI / 180) * move_step * 30;
		new_player_y += cos(data->player_angle * PI / 180) * move_step * 30;
	}
	else if (data->player_walk_direction == 2 || data->player_walk_direction == -2)
	{
		new_player_x += cos(data->player_angle * PI / 180) * move_step * 15;
		new_player_y -= sin(data->player_angle * PI / 180) * move_step * 15;
	}
	else
		return ;
	if (!is_wall(data, (new_player_x - SQUARE_SIZE / 3) / SQUARE_SIZE, (new_player_y - SQUARE_SIZE / 3) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x + SQUARE_SIZE / 3) / SQUARE_SIZE, (new_player_y - SQUARE_SIZE / 3) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x - SQUARE_SIZE / 3) / SQUARE_SIZE, (new_player_y + SQUARE_SIZE / 3) / SQUARE_SIZE) &&
		!is_wall(data, (new_player_x + SQUARE_SIZE / 3) / SQUARE_SIZE, (new_player_y + SQUARE_SIZE / 3) / SQUARE_SIZE)
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
	double	fov;
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
	data->textures = malloc (sizeof(mlx_texture_t *) * 4);
	if (!data->textures)
		return (0);
	data->textures[NORTH] = mlx_load_png("textures/N.png");
	data->textures[SOUTH] = mlx_load_png("textures/S.png");
	data->textures[EAST] = mlx_load_png("textures/E.png");
	data->textures[WEST] = mlx_load_png("textures/W.png");
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
	i = 0;
	t_ray	*ray;
	t_ray	*tmp;

	tmp = NULL;
	fov = 0;
	while (fov < FOV)
	{
		ray = (t_ray *)malloc(sizeof(t_ray));
		ray->prev = NULL;
		ray->next = NULL;
		if (!tmp)
		{
			data->rays = ray;
			tmp = ray;
		}
		else
		{
			while (tmp->next)
				tmp = tmp->next;
			tmp->next = ray;
			ray->prev = tmp;
		}
		fov += 0.0625;
	}
	init_window(data);
	return (0);
}
