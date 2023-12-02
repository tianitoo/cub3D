/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:52:49 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/02 15:53:18 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	the_minimalist(char **str, int x)
{
	int	i;

	i = 0;
	while (!check_the_first_of_map(str, i))
	{
		if (!str[i])
			return (0);
		if (!check_the_order_and_path(str[i]) && !check_floor_sky(str[i]))
			return (0);
		i++;
	}
	if (!check_the_orders_is_valid(str))
		return (0);
	if (!the_map(str, x, i))
		return (0);
	return (1);
}

int	check_and_skip_spaces(char *str)
{
	int	i;

	i = skips_spaces(str);
	if (str[i] == '\n' || str[i] != '\0')
		return (1);
	return (0);
}

int	find_point_cube(char *str, char *to_find)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		while (str[i + j] != '\0' && str[i + j] == to_find[j])
			j++;
		if (to_find[j] == '\0')
			return (i + j);
		j = 0;
		i++;
	}
	return (0);
}

int	check_point_cube(char *st)
{
	int	i;

	i = find_point_cube(st, ".cube");
	if (find_point_cube(st, ".cube") && st[i] == '\0')
		return (1);
	return (0);
}

int	count_the_lines(char *path)
{
	char	*str;
	int		i;
	int		fd;

	if (!check_point_cube(path))
		return (0);
	i = 0;
	fd = open(path, O_RDWR, 0666);
	if (fd == -1)
		return (0);
	str = get_next_line(fd);
	while (str)
	{
		if (check_and_skip_spaces(str))
			i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**fill_string(int i, char *path)
{
	char	*str;
	char	**strs;
	int		fd;

	fd = open(path, O_CREAT | O_RDWR, 0666);
	strs = (char **)malloc((i + 1) * sizeof(char *));
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		if (check_and_skip_spaces(str))
		{
			strs[i] = str;
			i++;
		}
		else
			free(str);
		str = get_next_line(fd);
	}
	strs[i] = NULL;
	close(fd);
	return (strs);
}

int	*return_color(char *str, int i)
{
	char	*st;
	char	**d_str;
	int		*tab;
	int		j;

	st = return_the_path(str, i);
	tab = malloc(sizeof(int) * 3);
	d_str = ft_split(st, ',');
	j = 0;
	while (j < 3)
	{
		tab[j] = ft_atoi(d_str[j]);
		j++;
	}
	i = 0;
	while (d_str[i])
	{
		free(d_str[i]);
		i++;
	}
	free(d_str);
	free(st);
	return (tab);
}

void	fill_order_and_path(t_data *data, char *str)
{
	int	i;

	i = skips_spaces(str);
	if (str[i] == 'N' && str[i + 1] == 'O' && ft_isspace(str[i + 2]))
		data->n_texture = return_the_path(str, i + 2);
	else if (str[i] == 'S' && str[i + 1] == 'O' && ft_isspace(str[i + 2]))
		data->s_texture = return_the_path(str, i + 2);
	else if (str[i] == 'W' && str[i + 1] == 'E' && ft_isspace(str[i + 2]))
		data->w_texture = return_the_path(str, i + 2);
	else if (str[i] == 'E' && str[i + 1] == 'A' && ft_isspace(str[i + 2]))
		data->e_texture = return_the_path(str, i + 2);
	else if (str[i] == 'C' && ft_isspace(str[i + 1]))
		data->c_tab = return_color(str, i + 1);
	else if (str[i] == 'F' && ft_isspace(str[i + 1]))
		data->f_tab = return_color(str, i + 1);
}

char	**cont_fill_the_map(char **str, size_t max, char *tmp, char *tmp2)
{
	int	j;
	int	i;

	j = 0;
	i = 0;
	while (str[i])
	{
		tmp2 = str[i];
		str[i] = ft_strtrim(str[i], " \n");
		free(tmp2);
		if (ft_strlen(str[i]) != max)
		{
			j = 0;
			while (ft_strlen(str[i]) < max - 1)
			{
				tmp = str[i];
				str[i] = ft_strjoin(str[i], "1", 0);
				free(tmp);
				j++;
			}
		}
		i++;
	}
	str[i] = NULL;
	return (str);
}

char	**resize_the_map(char **str)
{
	int		i;
	size_t	max;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
	tmp2 = NULL;
	max = ft_strlen(str[i]);
	while (str[i])
	{
		if (max <= ft_strlen(str[i]))
			max = ft_strlen(str[i]);
		i++;
	}
	i = 0;
	i = 0;
	str = cont_fill_the_map(str, max, tmp, tmp2);
	return (str);
}

char	**allocate_for_d_str(char **str, int i)
{
	int		j;
	char	**d_str;

	j = i;
	while (str[i])
		i++;
	d_str = malloc(sizeof(char *) * i - j + 1);
	i = j;
	j = 0;
	while (str[i])
	{
		d_str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	return (d_str);
}

char	**fill_the_map(char **str, int i)
{
	int		j;
	char	**d_str;
	char	**new_map;

	d_str = allocate_for_d_str(str, i);
	i = 0;
	j = 0;
	while ((d_str[i]))
	{
		j = 0;
		while (d_str[i][j])
		{
			if (d_str[i][j] == ' ')
				d_str[i][j] = '1';
			j++;
		}
		i++;
	}
	new_map = resize_the_map(d_str);
	return (new_map);
}

char	set_player_direction(char c, t_data *data)
{
	if (c == 'N')
		data->player_dir = NORTH;
	else if (c == 'S')
		data->player_dir = SOUTH;
	else if (c == 'E')
		data->player_dir = EAST;
	else if (c == 'W')
		data->player_dir = WEST;
	return (c);
}

int cor_of_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E' 
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->player_x = i * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->player_y = j * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->order = set_player_direction(data->map[i][j], data);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_data(t_data *data)
{
	data->c_tab = NULL;
	data->f_tab = NULL;
	data->e_texture = 0;
	data->n_texture = 0;
	data->w_texture = 0;
	data->s_texture = 0;
	data->order = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->map = NULL;
}

void	map_height_width(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
		i++;
	data->map_height = i;
	data->map_width = ft_strlen(data->map[j]);
}

int	inits_the_data(t_data *data, char **str)
{
	int	i;

	i = 0;
	init_data(data);
	while (!check_the_first_of_map(str, i))
	{
		fill_order_and_path(data, str[i]);
		i++;
	}
	data->map = fill_the_map(str, i);
	if (!cor_of_player(data))
		return (0);
	map_height_width(data);
	return (1);
}

void	display_data(t_data *data)
{
	int	i;

	i = 0;
	printf("DATA : \n");
	printf("NO ->>>> %s\n", data->n_texture);
	printf("EA ->>>> %s\n", data->e_texture);
	printf("SO ->>>> %s\n", data->s_texture);
	printf("WE ->>>> %s\n", data->w_texture);
	printf("\nC : ");
	while (i < 3)
	{
		printf(" %d |", data->c_tab[i]);
		i++;
	}
	i = 0;
	printf("\nF  : ");
	while (i < 3)
	{
		printf(" %d |", data->f_tab[i]);
		i++;
	}
	i = -1;
	printf("\n\n MAP : \n");
	while (data->map[++i])
	{
		printf("%s\n", data->map[i]);
	}
	printf("\n\nthe type  : %c \n", data->order);
	printf("Coordinate of player x : %f\n", data->player_x);
	printf("Coordinate of player y : %f\n", data->player_y);
}

int	fail_the_inits(t_data data)
{
	if (!data.e_texture)
		return (0);
	else if (!data.n_texture)
		return (0);
	else if (!data.s_texture)
		return (0);
	else if (!data.w_texture)
		return (0);
	else if (!data.c_tab)
		return (0);
	else if (!data.f_tab)
		return (0);
	else if (!data.map)
		return (0);
	else if (!data.order)
		return (0);
	else if (!data.player_x)
		return (0);
	else if (!data.player_y)
		return (0);
	return (1);
}
