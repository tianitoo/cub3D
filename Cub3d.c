/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/28 19:24:35 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/26 15:32:45 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r'
		|| c == '\0')
		return (1);
	return (0);
}

void	free_two_d(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

int	check_the_map(char **str, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		j = 0;
		while (str[i][j])
		{
			if (str[i][j] != '0' && str[i][j] != '1' 
				&& str[i][j] != 'S' && str[i][j] != 'N' 
				&& str[i][j] != 'W' && str[i][j] != 'E' 
				&& !ft_isspace(str[i][j]))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_each_element(char **str, int x, int i)
{
	int	j;

	j = 0;
	while (i < x - 1)
	{
		j = skips_spaces(str[i]);
		if (str[i][j] != '1')
			return (0);
		while (str[i][j] != '\n')
			j++;
		j--;
		while (str[i][j] != '1')
		{
			if (str[i][j] == '0' 
				|| str[i][j] == 'S' || str[i][j] == 'N' 
				|| str[i][j] == 'W' || str[i][j] == 'E')
				return (0);
			if (ft_isspace(str[i][j]))
				j--;
		}
		i++;
	}
	return (i);
}

int	check_the_map_is_valid(char **str, int x, int i)
{
	int	j;

	j = 0;
	if (!check_the_map(str, i))
		return (0);
	while (str[i][j] != '\n')
	{
		if (str[i][j] != '1' && !ft_isspace(str[i][j]))
			return (0);
		j++;
	}
	i++;
	if (!check_each_element(str, x, i))
		return (0);
	i = check_each_element(str, x, i);
	j = 0;
	while (str[i][j] != '\0')
	{
		if (str[i][j] != '1' && !ft_isspace(str[i][j]))
			return (0);
		j++;
	}
	return (1);
}

int	check_is_one_player(char **str, int x, char c, int i)
{
	int	j;
	int	l;

	j = 0;
	l = 0;
	if (c == '0')
		return (1);
	while (i < x - 1)
	{
		j = 0;
		while (str[i][j] != '\n')
		{
			if (str[i][j] == c)
				l++;
			j++;
		}
		i++;
	}
	if (l > 1)
		return (0);
	return (1);
}

int	check_is_only_one_order(char **str, int x, char c, int i)
{
	int	j;
	int	l;

	j = 0;
	l = 0;
	if (c == '0')
		return (1);
	while (i < x - 1)
	{
		j = 0;
		while (str[i][j] != '\n')
		{
			if (str[i][j] == 'N' || str[i][j] == 'W' 
				|| str[i][j] == 'E' || str[i][j] == 'S')
				l++;
			j++;
		}
		i++;
	}
	if (l > 1)
		return (0);
	return (1);
}

int	check_element_is_valid(char **str, int x, char c, int i)
{
	int	j;
	int	l;

	i++;
	l = i;
	j = 0;
	while (i < x - 1)
	{
		j = 0;
		while (str[i][j] != '\n')
		{
			if (str[i][j] == c)
			{
				if (ft_isspace(str[i][j - 1]) || ft_isspace(str[i][j + 1])
					|| ft_isspace(str[i - 1][j]) || ft_isspace(str[i + 1][j]))
					return (0);
			}
			j++;
		}
		i++;
	}
	if (!check_is_one_player(str, x, c, l)
		|| !check_is_only_one_order(str, x, c, l))
		return (0);
	return (1);
}

int	check_the_player_is_valid(char **str, int x, int i)
{
	if (!check_element_is_valid(str, x, '0', i))
		return (0);
	if (!check_element_is_valid(str, x, 'N', i))
		return (0);
	if (!check_element_is_valid(str, x, 'E', i))
		return (0);
	if (!check_element_is_valid(str, x, 'W', i))
		return (0);
	if (!check_element_is_valid(str, x, 'S', i))
		return (0);
	return (1);
}

int	the_map(char **str, int x, int i)
{
	if (!check_the_map_is_valid(str, x, i))
		return (0);
	if (!check_the_player_is_valid(str, x, i))
		return (0);
	return (1);
}

int	check_the_first_of_map(char **str, int i)
{
	int	j;

	j = 0;
	if (!str[i])
		return (0);
	while (str[i][j] != '\n')
	{
		if (str[i][j] != '1' && !ft_isspace(str[i][j]))
			return (0);
		j++;
	}
	return (1);
}

char	*fill_the_str_to_check(char *str)
{
	char	*s;
	int		i;
	int		j;

	i = check_the_order(str);
	s = malloc(i + 1);
	j = 0;
	while (j < i)
	{
		s[j] = str[j];
		j++;
	}
	s[j] = '\0';
	return (s);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	part_two_of_check_order(char **str, int j, char *s)
{
	char	*st;

	while (str[j])
	{
		if (check_the_first_of_map(str, j))
			break ;
		st = fill_the_str_to_check(str[j]);
		if (!ft_strcmp(st, s))
			return (free(st), 0);
		free(st);
		j++;
	}
	return (1);
}

int	check_the_orders_is_valid(char **str)
{
	int		i;
	int		j;
	char	*s;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_the_first_of_map(str, i))
			break ;
		s = fill_the_str_to_check(str[i]);
		j = i + 1;
		if (!part_two_of_check_order(str, j, s))
			return (free(s), 0);
		free(s);
		i++;
	}
	return (1);
}

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

int	count_the_lines(char *path)
{
	char	*str;
	int		i;
	int		fd;

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
	free_two_d(d_str);
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

char	**cont_fill_the_map(char **str, int max, char *tmp, char *tmp2)
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
				str[i] = ft_strjoin(str[i], "1");
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
	int		max;
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
	i = 0;
	return (new_map);
}

int	cor_of_player(t_data *data)
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
			if (data->map[i][j] == 'N' 
			|| data->map[i][j] == 'E'
			|| data->map[i][j] == 'W'
			|| data->map[i][j] == 'S')
			{
				data->x_player = j;
				data->y_player = i;
				data->order = data->map[i][j];
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
	data->x_player = 0;
	data->y_player = 0;
	data->map = NULL;
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
	printf("Coordinate of player x : %d\n", data->x_player);
	printf("Coordinate of player y : %d\n", data->y_player);
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
	else if (!data.x_player)
		return (0);
	else if (!data.y_player)
		return (0);
	return (1);
}

void	f(void)
{
	system("leaks cub3D");
}

void	free_the_data(char **str, t_data *data)
{
	display_data(data);
	free_two_d(str);
	free_two_d(data->map);
	free(data->n_texture);
	free(data->e_texture);
	free(data->w_texture);
	free(data->s_texture);
	free(data->c_tab);
	free(data->f_tab);
}

int	main(int ac, char **av)
{
	int		j;
	char	**str;
	t_data	data;

	atexit(f);
	str = NULL;
	if (!count_the_lines(av[1]))
		return (printf("NOT VALID\n"), 0);
	j = count_the_lines(av[1]);
	str = fill_string(j, av[1]);
	if (!the_minimalist(str, j))
	{
		printf("NOT VALID\n");
		return (free_two_d(str), 0);
	}
	if (!inits_the_data(&data, str) || !fail_the_inits(data))
		return (printf("NOT VALID\n"), 0);
	else
	{
		printf("VALID\n");
		free_the_data(str, &data);
	}
	return (0);
}
