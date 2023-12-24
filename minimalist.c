/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part_four.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:06:28 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 16:44:55 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	the_minimalist(char **str, int x)
{
	int	i;

	i = 0;
	while (!check_the_first_of_map(str, i))
	{
		if (!str[i])
			return (printf("Error : there is no map\n"), 0);
		if (!check_the_order_and_path(str[i]) && !check_floor_sky(str[i]))
			return (printf("Error : incorrect path or the color\n"), 0);
		i++;
	}
	if (!check_the_orders_is_valid(str))
		return (printf("Error : there is double orders or double colors\n"), 0);
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

	i = find_point_cube(st, ".cub");
	if (find_point_cube(st, ".cub") && st[i] == '\0')
		return (1);
	return (0);
}

int	count_the_lines(char *path)
{
	char	*str;
	int		i;
	int		fd;

	if (!count_the_lines_one(path))
		return (0);
	i = count_the_lines_one(path);
	if (!check_map_is_there_is_there_new_line(i, path))
		return (0);
	if (!check_point_cube(path))
		return (printf("Error : the path doesn't have .cub\n"), 0);
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
