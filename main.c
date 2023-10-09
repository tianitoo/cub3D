/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:47 by hnait             #+#    #+#             */
/*   Updated: 2023/10/09 15:54:31 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	get_rgba(int r, int g, int b)
{
	return (r << 24 | g << 16 | b << 8 | 255);
}

int	get_wall_height(int distance_from_wall)
{
	int		wall_height;

	wall_height = distance_from_wall * 300 / 500;
	return (wall_height);
}

int	get_distance_from_wall(t_data *data)
{
	int	player_x;
	int	player_y;
	int	i;

	player_y = data->player_y;
	player_x = data->player_x;
	i = 0;
	while (data->map[player_x / SQUARE_SIZE][player_y / SQUARE_SIZE]
		!= '1')
	{
		if (data->player_dir == NORTH)
			player_x = player_x - 1;
		i++;
	}
	return (i);
}

void	mlx_draw_line(t_data *data)
{
	int		j;
	int		color;
	int		wall_height;
	int		distance_from_wall;

	distance_from_wall = get_distance_from_wall(data);
	j = 1;
	color = get_rgba(255, 0, 0);
	wall_height = get_wall_height(distance_from_wall);
	while (j < WIN_HEIGHT / 2)
	{
		if (j > wall_height)
		{
			mlx_put_pixel(data->img, WIN_WIDTH / 2, j, color);
			mlx_put_pixel(data->img, WIN_WIDTH / 2, WIN_HEIGHT - j, color);
		}
		else
		{
			mlx_put_pixel(data->img, WIN_WIDTH / 2, j, get_rgba(0, 0, 0));
			mlx_put_pixel(data->img, WIN_WIDTH / 2, WIN_HEIGHT - j, get_rgba(0, 0, 0));
		}
		j++;
	}
}

int	get_distance_from_wall_angle(t_data *data, int angle)
{
	int	player_x;
	int	player_y;
	int	i;

	player_y = data->player_y;
	player_x = data->player_x;
	i = 0;
	while (data->map[player_x / SQUARE_SIZE][player_y / SQUARE_SIZE]
		!= '1')
	{
		if (data->player_dir == NORTH)
		{
			player_x = player_x - 1;
			player_y = data->player_y - tan((angle) * PI / 180) * (player_x - data->player_x);
			// ft_printf("player_y = %d\n", player_y);
			if (player_y < 0)
				player_y = 0;
			else if (player_y > WIN_HEIGHT)
				player_y = WIN_HEIGHT;
		}
		i++;
	}
	return (i);
}

int	get_wall_height_angle(t_data *data, int angle)
{
	int		wall_height;
	int		distance_from_wall;

	distance_from_wall = get_distance_from_wall_angle(data, angle);
	wall_height = get_wall_height(distance_from_wall);
	return (wall_height);
}

void	mlx_draw_line_angle(t_data *data, int angle)
{
	int		j;
	int		color;
	int		wall_height;

	color = get_rgba(255, 0, 0);
	wall_height = get_wall_height_angle(data, angle);
	int i = 0;
	while (i < 30)
	{
		j = 1;
		while (j <= WIN_HEIGHT / 2)
		{
			if (j > wall_height)
			{
				mlx_put_pixel(data->img, WIN_WIDTH / 2 + angle * 30 + i, j, color);
				mlx_put_pixel(data->img, WIN_WIDTH / 2 + angle * 30 + i, WIN_HEIGHT - j, color);
			}
			else
			{
				mlx_put_pixel(data->img, WIN_WIDTH / 2 + angle * 30 + i, j, get_rgba(0, 0, 0));
				mlx_put_pixel(data->img, WIN_WIDTH / 2 + angle * 30 + i, WIN_HEIGHT - j, get_rgba(0, 0, 0));
			}
			j++;
		}
		i++;
	}
}

void	draw_rays_on_map(t_data *data, int player_x, int player_y)
{
	int		i;
	int		j;
	// int		k;
	int		player_pos_mini_x;
	int		player_pos_mini_y;
	i = -30;
	// while (i < 30)
	// {
		player_pos_mini_x = player_x * MINIMAP_SQUARE_SIZE / SQUARE_SIZE;
		player_pos_mini_y = player_y * MINIMAP_SQUARE_SIZE / SQUARE_SIZE;
		j = player_pos_mini_y;
		while (data->map[player_pos_mini_x / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE] != '1')
		{
			mlx_put_pixel(data->img, j, player_pos_mini_x, get_rgba(255, 0, 0));
			j = j - 1;
			player_pos_mini_x = player_pos_mini_x - tan((i + 90) * PI / 180) * (player_pos_mini_y - j);
			// ft_printf("player_pos_mini_x = %d\n", player_pos_mini_x);
			if (player_pos_mini_x < 0)
				player_pos_mini_x = 0;
			else if (player_pos_mini_x > WIN_HEIGHT)
				player_pos_mini_x = WIN_HEIGHT;
		}
		// i++;
	// }
	// draw_rays_on_map(data, player_x, player_y);
}

void	draw_2d_map(t_data *data, int player_x, int player_y)
{
	int		i;
	int		j;
	int		color;
	int		player_pos_mini_x;
	int		player_pos_mini_y;

	i = 0;
	player_pos_mini_x = player_x * MINIMAP_SQUARE_SIZE / SQUARE_SIZE;
	player_pos_mini_y = player_y * MINIMAP_SQUARE_SIZE / SQUARE_SIZE;
	while (data->map[i / MINIMAP_SQUARE_SIZE])
	{
		j = 0;
		while (data->map[i / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE])
		{
			if (i > player_pos_mini_x - 2 && i < player_pos_mini_x + 2
				&& j > player_pos_mini_y - 2 && j < player_pos_mini_y + 2)
				color = get_rgba(255, 0, 0);
			else if (data->map[i / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE] == '1')
				color = get_rgba(255, 255, 255);
			else if (data->map[i / MINIMAP_SQUARE_SIZE][j / MINIMAP_SQUARE_SIZE] == '0')
				color = get_rgba(0, 0, 0);
			mlx_put_pixel(data->img, j, i , color);
			j++;
		}
		i++;
	}
	draw_rays_on_map(data, player_x, player_y);
}

void	draw(t_data *data)
{
	int		i;

	i = -30;
	mlx_draw_line(data);
	while (i < 30)
	{
		mlx_draw_line_angle(data, i + data->player_angle);
		i++;
	}
	draw_2d_map(data, data->player_x, data->player_y);
}

void	hook(void *tmp)
{
	t_data	*data;

	data = (t_data *)tmp;
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_ESCAPE))
		exit(0);
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
	{
		data->player_x -= 1;
		if (data->map[data->player_x / SQUARE_SIZE][data->player_y / SQUARE_SIZE]
			== '1')
			data->player_x += 1;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
	{
		data->player_x += 1;
		if (data->map[data->player_x / SQUARE_SIZE][data->player_y / SQUARE_SIZE]
			== '1')
			data->player_x -= 1;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
	{
		data->player_y -= 1;
		if (data->map[data->player_x / SQUARE_SIZE][data->player_y / SQUARE_SIZE]
			== '1')
			data->player_y += 1;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
	{
		data->player_y += 1;
		if (data->map[data->player_x / SQUARE_SIZE][data->player_y / SQUARE_SIZE]
			== '1')
			data->player_y -= 1;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
	{
		data->player_angle -= 1;
		if (data->player_angle < 0)
			data->player_angle = 360;
	}
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
	{
		data->player_angle += 1;
		if (data->player_angle > 360)
			data->player_angle = 0;
	}
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
	while (line)
	{
		if (line && line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
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
	data->player_angle = 0;
	// sleep(2);
	init_window(data);
	return (0);
}
