/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 11:45:43 by hnait             #+#    #+#             */
/*   Updated: 2023/11/27 13:34:52 by hnait            ###   ########.fr       */
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
# define SQUARE_SIZE 200
# define MINIMAP_SQUARE_SIZE 10
# define MAP_WIDTH WIN_WIDTH / 3
# define MAP_HEIGHT WIN_HEIGHT / 3
# define FOV 60
# define NORTH 0
# define SOUTH 1
# define EAST 2
# define WEST 3
# define ESC 53
# define HORIZONTAL 0
# define VERTICAL 1
# define EQUAL 2

# define PI 3.14159265359

typedef struct s_ray
{
	double			distance;
	int				direction;
	int				hit;
	double			wall_height;
	int				wall_top;
	struct s_ray	*next;
	struct s_ray	*prev;
}	t_ray;

typedef struct s_data
{
	mlx_t			*mlx_ptr;
	void			*mlx_win;
	mlx_image_t		*img;
	char			**map;
	int				map_width;
	int				map_height;
	double			player_x;
	double			player_y;
	double			player_angle;
	double			projected_distance;
	int				player_dir;
	int				player_walk_direction;
	double			player_turn_direction;
	double			ray_hit_horz;
	double			ray_hit_vert;
	int				checked_horizontal;
	int				checked_vertical;
	mlx_texture_t	**textures;
	t_ray			*rays;
}	t_data;

/**
 * Checks if the player is out of the map boundaries.
 *
 * @param data The data structure containing the map and player information.
 * @param player_mini_x The x-coordinate of the player.
 * @param player_mini_y The y-coordinate of the player.
 * @return 1 if the player is out of the map, 0 otherwise.
 */
int is_out_of_map(t_data *data, double player_mini_x, double player_mini_y);

/**
 * Converts the RGB values to a single integer representing the RGBA color.
 *
 * @param r The red component value (0-255).
 * @param g The green component value (0-255).
 * @param b The blue component value (0-255).
 * @return The RGBA color as an integer.
 */
int get_rgba(int r, int g, int b);

/**
 * Checks if the given coordinates represent a wall in the map.
 *
 * @param data The data structure containing the map information.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return 1 if the coordinates represent a wall, 0 otherwise.
 */
int is_wall(t_data *data, int x, int y);

/**
 * Sets the direction of the ray based on the ray angle and direction type.
 *
 * @param ray The ray structure to update.
 * @param ray_angle The angle of the ray.
 * @param direction The direction type (HORIZONTAL, VERTICAL, or EQUAL).
 */
void set_ray_direction(t_ray *ray, double ray_angle, int direction);

/**
 * Calculates the distance of the ray from the player to the wall and determines the ray direction.
 *
 * @param data The data structure containing the map and ray information.
 * @param ray The ray structure to update.
 * @param ray_angle The angle of the ray.
 */
void get_distance(t_data *data, t_ray *ray, double ray_angle);

/**
 * Casts rays from the player to create the 3D projection of the map.
 *
 * @param data The data structure containing the map and ray information.
 */
void cast_rays(t_data *data);

/**
 * Retrieves the color of a pixel from a texture at the specified coordinates.
 *
 * @param texture The texture to retrieve the pixel color from.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The color of the pixel as an integer.
 */
int get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);

/**
 * Calculates the x-coordinate of the texture based on the ray hit position and direction.
 *
 * @param ray The ray structure containing the hit position and direction.
 * @param data The data structure containing the texture information.
 * @return The x-coordinate of the texture.
 */
double get_texture_x(t_ray *ray, t_data *data);

/**
 * Draws a column on the screen based on the given ray and window position.
 *
 * @param data   A pointer to the data structure containing game information.
 * @param ray    A pointer to the ray structure containing raycasting information.
 * @param win_x  The x-coordinate of the window position.
 * @param i      The index of the column to be drawn.
 */
void draw_column(t_data *data, t_ray *ray, int win_x, int i);

/**
 * Draws a single ray on the screen.
 *
 * @param data The data structure containing the map and ray information.
 * @param ray The ray structure to draw.
 * @param win_x The x-coordinate of the window.
 */
void draw_ray(t_data *data, t_ray *ray, int win_x);

/**
 * Draws the 3D map using the provided data.
 *
 * @param data The data structure containing the map and ray information.
 */
void draw_3d_map(t_data *data);

/**
 * Draws the entire scene using the provided data.
 *
 * @param data The data structure containing the map and ray information.
 */
void draw(t_data *data);

/**
 * Rotates the player based on the left and right arrow keys.
 *
 * @param data The data structure containing the player information.
 */
void rotate_player(t_data *data);

/**
 * Determines if there is a horizontal wall at the given position and angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The x-coordinate of the player's position.
 * @param player_mini_y The y-coordinate of the player's position.
 * @param fov The field of view angle.
 * @return 1 if there is a horizontal wall, 0 otherwise.
 */
int is_horiz_wall(t_data *data, double player_mini_x, double player_mini_y, double fov);

/**
 * Updates the x-coordinate of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_horizontal_x(t_data *data, double *player_mini_x, double angle);

/**
 * Updates the y-coordinate of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_horizontal_y(t_data *data, double *player_mini_y, double *player_mini_x, double angle);

/**
 * Updates the x and y coordinates of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_horizontal_x_y(t_data *data, double *player_mini_x, double *player_mini_y, double angle);

/**
 * Calculates the distance to the nearest horizontal wall from the player's position.
 * 
 * @param data The data structure containing the game information.
 * @param angle The angle of the player's view.
 * @return The distance to the nearest horizontal wall.
 */
int horizontal_line(t_data *data, double angle);

/**
 * Calculates the distance to the nearest horizontal wall from the player's position.
 * 
 * @param data The data structure containing the game information.
 * @param angle The angle of the player's view.
 * @return The distance to the nearest horizontal wall.
 */
int get_horizontal_distance(t_data *data, double angle);

/**
 * Checks if there is a vertical wall at the given position and angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The x-coordinate of the player's position.
 * @param player_mini_y The y-coordinate of the player's position.
 * @param fov The field of view angle.
 * @return 1 if there is a vertical wall, 0 otherwise.
 */
int is_vertical_wall(t_data *data, double player_mini_x,
					 double player_mini_y, double fov);

/**
 * Adjusts the y-coordinate of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_vertical_y(t_data *data, double *player_mini_y, double angle);

/**
 * Adjusts the x-coordinate of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_vertical_x(t_data *data, double *player_mini_x,
					double *player_mini_y, double angle);

/**
 * Adjusts the x and y coordinates of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void get_vertical_x_y(t_data *data, double *player_mini_x,
					  double *player_mini_y, double angle);

/**
 * Calculates the vertical distance to the nearest wall in the player's view.
 *
 * @param data The data structure containing game information.
 * @param angle The angle of the player's view.
 * @return The vertical distance to the nearest wall.
 */
int vertical_line(t_data *data, double angle);

/**
 * Calculates the vertical distance to the nearest wall in the player's view.
 * Handles special cases when the angle is 90 or 270 degrees.
 *
 * @param data The data structure containing game information.
 * @param angle The angle of the player's view.
 * @return The vertical distance to the nearest wall.
 */
int get_vertical_distance(t_data *data, double angle);

#endif