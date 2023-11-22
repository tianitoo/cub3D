/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:43 by hnait             #+#    #+#             */
/*   Updated: 2023/11/22 15:52:22 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "ft_printf/ft_printf.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
// # define WIN_WIDTH 920
// # define WIN_HEIGHT 780
# define SQUARE_SIZE 200
# define MINIMAP_SQUARE_SIZE 10
# define MAP_WIDTH 1920 / 3
# define MAP_HEIGHT 1080 / 3
# define FOV 60
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define ESC 53
# define HORIZONTAL 0
# define VERTICAL 1

# define PI 3.14159265359

typedef struct s_ray
{
	double			distance;
	double			direction;
	struct s_ray	*next;
	struct s_ray	*prev;
}	t_ray;

typedef struct s_data
{
	mlx_t		*mlx_ptr;
	void		*mlx_win;
	mlx_image_t	*img;
	char		**map;
	int			map_width;
	int			map_height;
	double		player_x;
	double		player_y;
	double		player_angle;
	int			player_dir;
	int			player_walk_direction;
	int			player_turn_direction;
	int			checked_horizontal;
	int			checked_vertical;
	t_ray		*rays;
}	t_data;

int	get_horizontal_distance(t_data *data, double fov);
int	get_vertical_distance(t_data *data, double fov);
int	is_vertical_wall(t_data *data, double player_mini_x, double player_mini_y, double fov);
int	is_horizontal_wall(t_data *data, double player_mini_x, double player_mini_y, double fov);
int	is_wall(t_data *data, int x, int y);
int	get_rgba(int r, int g, int b);

#endif