/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:51:45 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/15 17:50:07 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_the_data(t_data *data)
{
	free_two_d(data->map);
	free(data->n_texture);
	free(data->e_texture);
	free(data->w_texture);
	free(data->s_texture);
	free(data->c_tab);
	free(data->f_tab);
}

int	complete_check_the_new_line(char **strs, int i)
{
	int	j;

	while (strs[i])
	{
		if (!strs[i + 1])
			break ;
		if (!is_empty(strs[i]))
		{
			j = 0;
			while (strs[i + 1][j] != '\n')
			{
				if (strs[i + 1][j] == '1' || strs[i + 1][j] == '0')
					return (0);
				j++;
			}
		}
		i++;
	}
	return (1);
}

int	check_the_new_line(char **strs)
{
	int	i;
	int	j;
	int	x;

	i = 0;
	j = 0;
	x = 0;
	while (strs[i])
	{
		j = 0;
		while (strs[i][j] != '\n')
		{
			if (strs[i][j] == '1')
				x = 1;
			j++;
		}
		if (x)
			break ;
		i++;
	}
	if (!complete_check_the_new_line(strs, i))
		return (0);
	return (1);
}

int	check_map_is_there_is_there_new_line(int i, char *path)
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
		strs[i] = ft_strdup(str);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	strs[i] = NULL;
	close(fd);
	if (!check_the_new_line(strs))
	{
		free_two_d(strs);
		return (0);
	}
	return (free_two_d(strs), 1);
}

int	count_the_lines_one(char *path)
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
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	return (i);
}
