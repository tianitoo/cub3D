
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:47 by hnait             #+#    #+#             */
/*   Updated: 2023/11/27 12:39:20 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./cub3D.h"

int	is_out_of_map(t_data *data, double player_mini_x, double player_mini_y)
{
	if (player_mini_x <= 0 || player_mini_y <= 0
		|| player_mini_x >= data->map_height * SQUARE_SIZE
		|| player_mini_y >= data->map_width * SQUARE_SIZE)
		return (1);
	return (0);
}

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
	double	tile_x;
	int		texture_x;

	if (ray->direction == NORTH || ray->direction == SOUTH)
		tile_x = fmod(ray->hit, SQUARE_SIZE);
	else
		tile_x = fmod(ray->hit, SQUARE_SIZE);
	texture_x = tile_x * (data->textures[ray->direction]->width / SQUARE_SIZE);
	return (texture_x);
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
			if (i < ray->wall_top)
				mlx_put_pixel(data->img, win_x, i, get_rgba(100, 150, 255));
			if (i >= ray->wall_top + ray->wall_height)
				mlx_put_pixel(data->img, win_x, i, get_rgba(100, 200, 150));
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

/**
 * Draws the 3D map using the provided data.
 *
 * @param data The data structure containing the necessary information for drawing.
 */
void draw_3d_map(t_data *data)
{
	t_ray *ray;
	int i;

	ray = data->rays;
	i = 0;
	while (ray)
	{
		draw_ray(data, ray, i);
		i++;
		ray = ray->next;
	}
}

void	draw(t_data *data)
{
	cast_rays(data);
	draw_3d_map(data);
}

// rotate the player with the left and right arrows
void	rotate_player(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_RIGHT))
		data->player_turn_direction = 1;
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_LEFT))
		data->player_turn_direction = -1;
	else
		data->player_turn_direction = 0;
	data->player_angle += data->player_turn_direction * 4;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	else if (data->player_angle < 0)
		data->player_angle += 360;
}

// check if the new position of the player is in a wall or out of the map
int	is_valid_position(t_data *data, double new_player_x, double new_player_y)
{
	if (!is_wall(data, (new_player_x - SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y - SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x + SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y - SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x - SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y + SQUARE_SIZE / 10) / SQUARE_SIZE)
		&& !is_wall(data, (new_player_x + SQUARE_SIZE / 10) / SQUARE_SIZE,
			(new_player_y + SQUARE_SIZE / 10) / SQUARE_SIZE))
		return (1);
	return (0);
}

// get the direction the player is walking to
int	player_direction(t_data *data)
{
	if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_W))
		return (1);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_S))
		return (-1);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_D))
		return (2);
	else if (mlx_is_key_down(data->mlx_ptr, MLX_KEY_A))
		return (-2);
	return (0);
}

// move the player with the A, W, S, D keys
// the player can only move if the new position is not in a wall or out of the map
void	move_player(t_data *data)
{
	double	move_step;
	double	new_player_x;
	double	new_player_y;

	new_player_x = data->player_x;
	new_player_y = data->player_y;
	data->player_walk_direction = player_direction(data);
	if (data->player_walk_direction == 1 || data->player_walk_direction == -1)
	{
		move_step = data->player_walk_direction * 20;
		new_player_x += sin(data->player_angle * PI / 180) * move_step;
		new_player_y += cos(data->player_angle * PI / 180) * move_step;
	}
	else if (data->player_walk_direction == 2
		|| data->player_walk_direction == -2)
	{
		move_step = data->player_walk_direction * 10;
		new_player_x += cos(data->player_angle * PI / 180) * move_step;
		new_player_y -= sin(data->player_angle * PI / 180) * move_step;
	}
	if (is_valid_position(data, new_player_x, new_player_y) == 1)
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

// create mlx window
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

int	create_rays(t_data *data)
{
	double	fov;
	t_ray	*ray;
	t_ray	*tmp;

	tmp = NULL;
	fov = 0;
	while (fov < FOV)
	{
		ray = new_ray();
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
		fov += (double)FOV / (double)(WIN_WIDTH);
	}
	return (1);
}

int	main(int ac, char **av)
{
	// int		fd;
	// char	*line;
	// char	**map;
	int		i;
	t_data	*data;

	data = (t_data *)malloc(sizeof(t_data));
	i = 0;
	(void)ac;
	int j = count_the_lines(av[1]);
    char **str = fill_string(j, av[1]);
    if (!the_minimalist(str, j))
    {
        printf("NOT VALID1\n");
        while (str[i])
        {
            free(str[i]);
            i++;
        }
        free(str);
        return (0);
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
    else
    {
        printf("VALID\n");
        display_data(data);
        // while (str[i])
        // {
        //     free(str[i]);
        //     i++;
        // }
        // free(str);
        // free(data->n_texture);
        // free(data->e_texture);
        // free(data->w_texture);
        // free(data->s_texture);
        // free(data->c_tab);
        // free(data->f_tab);
	}
	// j = 0;
	// fd = open("maps/map.cub", O_RDONLY);
	// if (fd == -1)
	// {
	// 	ft_printf("Error\n");
	// 	return (0);
	// }
	// i = 0;
	// line = get_next_line(fd);
	// data->map_width = 0;
	// data->map_height = 0;
	// while (line)
	// {
	// 	data->map_height++;
	// 	if (line && line[ft_strlen(line) - 1] == '\n')
	// 		line[ft_strlen(line) - 1] = '\0';
	// 	if (line && line[0] == '1')
	// 	{
	// 		if (data->map_width < (int) ft_strlen(line))
	// 			data->map_width = ft_strlen(line);
	// 	}
	// 	map[i] = line;
	// 	line = get_next_line(fd);
	// 	i++;
	// }


	// map[i] = NULL;
	// data->map = map;
	// close(fd);
	i = 0;
	// while (map[i])
	// {
	// 	j = 0;
	// 	// while (map[i][j])
	// 	// {
			if (data->order == 'N')
				data->player_dir = NORTH;
			else if (data->order == 'S')
				data->player_dir = SOUTH;
			else if (data->order == 'E')
				data->player_dir = EAST;
			else if (data->order == 'W')
				data->player_dir = WEST;
			// j++;
	// 	}
	// 	if (data->player_dir != -1)
	// 		break ;
	// 	i++;
	// }
	data->textures = malloc (sizeof(mlx_texture_t *) * 4);
	if (!data->textures)
		return (0);
	data->textures[NORTH] = mlx_load_png("textures/N.png");
	data->textures[SOUTH] = mlx_load_png("textures/S.png");
	data->textures[EAST] = mlx_load_png("textures/E.png");
	data->textures[WEST] = mlx_load_png("textures/W.png");
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
        display_data(data);
        
	init_window(data);
	return (0);
}
