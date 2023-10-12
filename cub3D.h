/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:43 by hnait             #+#    #+#             */
/*   Updated: 2023/10/12 17:29:25 by hnait            ###   ########.fr       */
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
# define SQUARE_SIZE 32
# define MINIMAP_SQUARE_SIZE 15
# define MAP_WIDTH 700
# define MAP_HEIGHT 500
# define FOV 60
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define ESC 53

# define PI 3.14159265359

typedef struct s_ray
{
	double			distance;
	struct s_ray	*next;
}	t_ray;

typedef struct s_data
{
	mlx_t		*mlx_ptr;
	void		*mlx_win;
	mlx_image_t *img;
	char		**map;
	int			map_width;
	int			map_height;
	double			player_x;
	double			player_y;
	int			player_angle;
	int			player_dir;
	int			player_walk_direction;
	int			player_turn_direction;
	t_ray		*rays;
}	t_data;




#endif