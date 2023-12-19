/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:53:29 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/19 14:22:17 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <stdio.h>
# include <stdbool.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>
# include "./MLX42/include/MLX42/MLX42.h"
# include "gnl/get_next_line.h"

# define WIN_WIDTH 1920
# define WIN_HEIGHT 1080
# define SQUARE_SIZE 200
# define MINIMAP_SQUARE_SIZE 10
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
	double				distance;
	int					direction;
	int					hit;
	double				wall_height;
	int					wall_top;
	struct s_ray		*next;
	struct s_ray		*prev;
}	t_ray;

typedef struct s_data
{
	mlx_t				*mlx_ptr;
	void				*mlx_win;
	mlx_image_t			*img;
	char				**map;
	int					map_width;
	int					map_height;
	double				player_x;
	double				player_y;
	double				player_angle;
	double				projected_distance;
	int					player_dir;
	int					player_walk_direction;
	double				player_turn_direction;
	double				ray_hit_horz;
	double				ray_hit_vert;
	int					checked_horizontal;
	int					checked_vertical;
	int					order;
	char				*n_texture;
	char				*s_texture;
	char				*w_texture;
	char				*e_texture;
	int					*c_tab;
	int					*f_tab;
	mlx_texture_t		**textures;
	t_ray				*rays;
	int					count;
}	t_data;

/**
 * Checks if the player is out of the map boundaries.
 *
 * @param data The data structure containing the map and player information.
 * @param player_mini_x The x-coordinate of the player.
 * @param player_mini_y The y-coordinate of the player.
 * @return 1 if the player is out of the map, 0 otherwise.
 */
int		is_out_of_map(t_data *data, double player_mini_x, double player_mini_y);

/**
 * Converts the RGB values to a single integer representing the RGBA color.
 *
 * @param r The red component value (0-255).
 * @param g The green component value (0-255).
 * @param b The blue component value (0-255).
 * @return The RGBA color as an integer.
 */
int		get_rgba(int r, int g, int b);

/**
 * Checks if the given coordinates represent a wall in the map.
 *
 * @param data The data structure containing the map information.
 * @param x The x-coordinate to check.
 * @param y The y-coordinate to check.
 * @return 1 if the coordinates represent a wall, 0 otherwise.
 */
int		is_wall(t_data *data, int x, int y);

/**
 * Sets the direction of the ray based on the ray angle and direction type.
 *
 * @param ray The ray structure to update.
 * @param ray_angle The angle of the ray.
 * @param direction The direction type (HORIZONTAL, VERTICAL, or EQUAL).
 */
void	set_ray_direction(t_ray *ray, double ray_angle, int direction);

/**
 * Calculates the distance of the ray from the player to the wall
 * and determines the ray direction.
 *
 * @param data The data structure containing
 * the map and ray information.
 * @param ray The ray structure to update.
 * @param ray_angle The angle of the ray.
 */
void	get_distance(t_data *data, t_ray *ray, double ray_angle);

/**
 * Casts rays from the player to create the 3D projection of the map.
 *
 * @param data The data structure containing the map and ray information.
 */
void	cast_rays(t_data *data);

/**
 * Retrieves the color of a pixel from a texture at the specified coordinates.
 *
 * @param texture The texture to retrieve the pixel color from.
 * @param x The x-coordinate of the pixel.
 * @param y The y-coordinate of the pixel.
 * @return The color of the pixel as an integer.
 */
int		get_pixel_color(mlx_texture_t *texture, uint32_t x, uint32_t y);

/**
 * Calculates the x-coordinate of the texture based on
 * the ray hit position and direction.
 *
 * @param ray The ray structure containing the hit position and direction.
 * @param data The data structure containing the texture information.
 * @return The x-coordinate of the texture.
 */
double	get_texture_x(t_ray *ray, t_data *data);

/**
 * Draws a column on the screen based on
 * the given ray and window position.
 *
 * @param data   A pointer to the data structure containing game information.
 * @param ray    A pointer to the ray structure containing
 * raycasting information.
 * @param win_x  The x-coordinate of the window position.
 * @param i      The index of the column to be drawn.
 */
void	draw_column(t_data *data, t_ray *ray, int win_x, int i);

/**
 * Draws a single ray on the screen.
 *
 * @param data The data structure containing the map and ray information.
 * @param ray The ray structure to draw.
 * @param win_x The x-coordinate of the window.
 */
void	draw_ray(t_data *data, t_ray *ray, int win_x);

/**
 * Draws the 3D map using the provided data.
 *
 * @param data The data structure containing the map and ray information.
 */
void	draw_3d_map(t_data *data);

/**
 * Rotates the player based on the left and right arrow keys.
 *
 * @param data The data structure containing the player information.
 */
void	rotate_player(t_data *data);

/**
 * Determines if there is a horizontal wall at the given position and angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The x-coordinate of the player's position.
 * @param player_mini_y The y-coordinate of the player's position.
 * @param fov The field of view angle.
 * @return 1 if there is a horizontal wall, 0 otherwise.
 */
int		is_horiz_wall(t_data *data, double player_mini_x,
			double player_mini_y, double fov);

/**
 * Updates the x-coordinate of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_horizontal_x(t_data *data, double *player_mini_x, double angle);

/**
 * Updates the y-coordinate of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_horizontal_y(t_data *data, double *player_mini_y,
			double *player_mini_x, double angle);

/**
 * Updates the x and y coordinates of the player's position based on the angle.
 * 
 * @param data The data structure containing the game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_horizontal_x_y(t_data *data, double *player_mini_x,
			double *player_mini_y, double angle);

/**
 * Calculates the distance to the nearest horizontal
 * wall from the player's position.
 * 
 * @param data The data structure containing the game information.
 * @param angle The angle of the player's view.
 * @return The distance to the nearest horizontal wall.
 */
int		horizontal_line(t_data *data, double angle);

/**
 * Calculates the distance to the nearest horizontal wall from
 * the player's position.
 * 
 * @param data The data structure containing the game information.
 * @param angle The angle of the player's view.
 * @return The distance to the nearest horizontal wall.
 */
int		get_horizontal_distance(t_data *data, double angle);

/**
 * Checks if there is a vertical wall at the given position and angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The x-coordinate of the player's position.
 * @param player_mini_y The y-coordinate of the player's position.
 * @param fov The field of view angle.
 * @return 1 if there is a vertical wall, 0 otherwise.
 */
int		is_vertical_wall(t_data *data, double player_mini_x,
			double player_mini_y, double fov);

/**
 * Checks if the new player position is valid.
 * A position is considered valid if the player does not collide with any walls.
 *
 * @param data The data structure containing game information.
 * @param new_player_x The x-coordinate of the new player position.
 * @param new_player_y The y-coordinate of the new player position.
 * @return 1 if the position is valid, 0 otherwise.
 */

int		is_valid_position(t_data *data,
			double new_player_x, double new_player_y);
/**
 * Creates rays for raycasting based on the given data.
 *
 * @param data The data structure containing necessary information.
 * @return 1 if the rays are successfully created, 0 otherwise.
 */
int		create_rays(t_data *data);

/**
 * Adjusts the y-coordinate of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_vertical_y(t_data *data, double *player_mini_y, double angle);

/**
 * Moves the player in the game world on the player's walk direction and angle.
 * 
 * @param data A pointer to the game data structure.
 */
void	move_player(t_data *data);

/**
 * Adjusts the x-coordinate of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_vertical_x(t_data *data, double *player_mini_x,
			double	*player_mini_y, double angle);

/**
 * Adjusts the x and y coordinates of the player's position based on the angle.
 *
 * @param data The data structure containing game information.
 * @param player_mini_x The pointer to the x-coordinate of the player's position.
 * @param player_mini_y The pointer to the y-coordinate of the player's position.
 * @param angle The angle of the player's view.
 */
void	get_vertical_x_y(t_data *data, double *player_mini_x,
			double	*player_mini_y, double angle);

/**
 * Calculates the vertical distance to the nearest wall in the player's view.
 *
 * @param data The data structure containing game information.
 * @param angle The angle of the player's view.
 * @return The vertical distance to the nearest wall.
 */
int		vertical_line(t_data *data, double angle);

/**
 * Calculates the vertical distance to the nearest wall in the player's view.
 * Handles special cases when the angle is 90 or 270 degrees.
 *
 * @param data The data structure containing game information.
 * @param angle The angle of the player's view.
 * @return The vertical distance to the nearest wall.
 */
int		get_vertical_distance(t_data *data, double angle);

/**
 * @brief Checks if a character is a whitespace character.
 * 
 * @param c The character to check.
 * @return int Returns 1 if the character is a whitespace character, 0 otherwise.
 */
int		ft_isspace(char c);

/**
 * @brief Checks if a map string is valid.
 * 
 * @param str The map string to check.
 * @return int Returns 1 if the map string is valid, 0 otherwise.
 */
int		check_the_map(char **str, int i);

/**
 * @brief Checks if the map is valid.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if the map is valid, 0 otherwise.
 */
int		check_the_map_is_valid(char **str, int x, int i);

/**
 * @brief Checks if there is only one player in the map.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param c The player character to check.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if there is only one player, 0 otherwise.
 */
int		check_is_one_player(char **str, int x, char c, int i);

/**
 * @brief Checks if there is only one order (N, W, E, S) in the map.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param c The order character to check.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if there is only one order, 0 otherwise.
 */
int		check_is_only_one_order(char **str, int x, char c, int i);

/**
 * @brief Checks if an element in the map is valid.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param c The element character to check.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if the element is valid, 0 otherwise.
 */
int		check_element_is_valid(char **str, int x, char c, int i);

/**
 * @brief Checks if the player elements in the map are valid.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if the player elements are valid, 0 otherwise.
 */
int		check_the_player_is_valid(char **str, int x, int i);

/**
 * @brief Checks if the map is valid.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if the map is valid, 0 otherwise.
 */
int		the_map(char **str, int x, int i);

/**
 * @brief Checks if the first line of the map is valid.
 * 
 * @param str The map array.
 * @param i The starting index of the map in the array.
 * @return int Returns 1 if the first line of the map is valid, 0 otherwise.
 */
int		check_the_first_of_map(char **str, int i);

/**
 * @brief Fills a string with characters to check for uniqueness.
 * 
 * @param str The input string.
 * @return char* Returns the filled string.
 */
char	*fill_the_str_to_check(char *str);

/**
 * @brief Compares two strings.
 * 
 * @param s1 The first string.
 * @param s2 The second string.
 * @return int Returns 0 if the strings are equal,
 * a positive value if s1 is greater than s2,
 * and a negative value if s1 is less than s2.
 */
int		ft_strcmp(char *s1, char *s2);

/**
 * @brief Checks if the orders in the map are valid and unique.
 * 
 * @param str The map array.
 * @return int Returns 1 if the orders are valid and unique, 0 otherwise.
 */
int		check_the_orders_is_valid(char **str);

/**
 * @brief Checks if the minimalist requirements for the map are met.
 * 
 * @param str The map array.
 * @param x The number of rows in the map.
 * @return int Returns 1 if the minimalist requirements are met, 0 otherwise.
 */
int		the_minimalist(char **str, int x);

/**
 * @brief Checks and skips leading spaces in a string.
 * 
 * @param str The input string.
 * @return int Returns the index of the first non-space character.
 */
int		check_and_skip_spaces(char *str);

/**
 * @brief Checks if a character is a whitespace character.
 *
 * @param c The character to check.
 * @return 1 if the character is a whitespace character, 0 otherwise.
 */
int		ft_isspace(char c);

/**
 * @brief Checks if a string represents a valid map.
 *
 * @param str The string to check.
 * @return 1 if the string represents a valid map, 0 otherwise.
 */
int		check_the_map(char **str, int i);

/**
 * @brief Checks if the map is valid.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return 1 if the map is valid, 0 otherwise.
 */
int		check_the_map_is_valid(char **str, int x, int i);

/**
 * @brief Checks if there is only one player in the map.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param c The player character to check.
 * @param i The starting index of the map in the array.
 * @return 1 if there is only one player, 0 otherwise.
 */
int		check_is_one_player(char **str, int x, char c, int i);

/**
 * @brief Checks if there is only one order (N, W, E, S) in the map.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param c The order character to check.
 * @param i The starting index of the map in the array.
 * @return 1 if there is only one order, 0 otherwise.
 */
int		check_is_only_one_order(char **str, int x, char c, int i);

/**
 * @brief Checks if an element in the map is valid.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param c The element character to check.
 * @param i The starting index of the map in the array.
 * @return 1 if the element is valid, 0 otherwise.
 */
int		check_element_is_valid(char **str, int x, char c, int i);

/**
 * @brief Checks if the player in the map is valid.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return 1 if the player is valid, 0 otherwise.
 */
int		check_the_player_is_valid(char **str, int x, int i);

/**
 * @brief Checks if the map is valid.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @param i The starting index of the map in the array.
 * @return 1 if the map is valid, 0 otherwise.
 */
int		the_map(char **str, int x, int i);

/**
 * @brief Checks if the first line of the map is valid.
 *
 * @param str The map as an array of strings.
 * @param i The starting index of the map in the array.
 * @return 1 if the first line of the map is valid, 0 otherwise.
 */
int		check_the_first_of_map(char **str, int i);

/**
 * @brief Fills a string with characters to check for uniqueness.
 *
 * @param str The string to fill.
 * @return The filled string.
 */
char	*fill_the_str_to_check(char *str);

/**
 * @brief Compares two strings.
 *
 * @param s1 The first string.
 * @param s2 The second string.
 * @return 0 if the strings are equal, a positive or negative value otherwise.
 */
int		ft_strcmp(char *s1, char *s2);

/**
 * @brief Checks if the orders in the map are valid and unique.
 *
 * @param str The map as an array of strings.
 * @return 1 if the orders are valid and unique, 0 otherwise.
 */
int		check_the_orders_is_valid(char **str);

/**
 * @brief Checks if the map is valid according to the minimalist rules.
 *
 * @param str The map as an array of strings.
 * @param x The number of rows in the map.
 * @return 1 if the map is valid, 0 otherwise.
 */
int		the_minimalist(char **str, int x);

/**
 * @brief Checks and skips leading spaces in a string.
 *
 * @param str The string to check.
 * @return The index of the first non-space character.
 */
int		check_and_skip_spaces(char *str);
char	**fill_string(int i, char *path);
int		count_the_lines(char *path, t_data *data);
int		inits_the_data(t_data *data, char **str);
int		fail_the_inits(t_data data);
void	display_data(t_data *data);
void	free_two_d(char **str);
int		is_empty(char *str);

int		check_the_order_and_path(char *str);
int		file_exist(char *str);
char	*return_the_path(char *str, int i);
int		check_the_order(char *str);
int		skips_spaces(char *str);
int		check_floor_sky(char *str);
int		check_the_color(char *str);
int		find_the_comma(char *str, int i);
int		ft_isspace(char c);
char	*delete_last_spaces(char *s);

//parcing
int		check_the_map_is_valid(char **str, int x, int i);
int		check_each_element(char **str, int x, int i);
int		check_the_map(char **str, int i);
int		ft_isspace(char c);
void	free_two_d(char **str);
int		the_map(char **str, int x, int i);
int		check_the_player_is_valid(char **str, int x, int i);
int		check_element_is_valid(char **str, int x, char c, int i);
int		check_is_only_one_order(char **str, int x, char c, int i);
int		check_is_one_player(char **str, int x, char c, int i);
int		check_the_orders_is_valid(char **str);
int		part_two_of_check_order(char **str, int j, char *s);
int		ft_strcmp(char *s1, char *s2);
char	*fill_the_str_to_check(char *str);
int		check_the_first_of_map(char **str, int i);
int		check_point_cube(char *st);
int		find_point_cube(char *str, char *to_find);
int		check_and_skip_spaces(char *str);
int		the_minimalist(char **str, int x);
char	**resize_the_map(char **str);
char	**cont_fill_the_map(char **str, size_t max, char *tmp, char *tmp2);
void	fill_order_and_path(t_data *data, char *str);
int		*return_color(char *str, int i);
char	**fill_string(int i, char *path);
char	**allocate_for_d_str(char **str, int i);
char	**fill_the_map(char **str, int i);
char	set_player_direction(char c, t_data *data);
int		cor_of_player(t_data *data);
void	init_data(t_data *data);
void	free_the_data(t_data *data);
int		complete_check_the_new_line(char **strs, int i);
int		check_the_new_line(char **strs);
int		check_map_is_there_is_there_new_line(int i, char *path, t_data *data);
int		count_the_lines_one(char *path);
int		check_the_file_is_empty(char **strs);
void	ft_mouse(t_data *data);

#endif