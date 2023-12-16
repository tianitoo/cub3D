/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part_five.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:09:38 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/16 15:07:41 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	**fill_string(int i, char *path)
{
	char	*str;
	char	**strs;
	int		fd;

	fd = open(path, O_RDWR, 0666);
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
