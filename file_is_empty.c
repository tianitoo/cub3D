/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_is_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:59:56 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 17:02:35 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	check_the_file_is_empty(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		if (!is_empty(strs[i]))
			i++;
		else
			break ;
	}
	if (!strs[i])
		return (0);
	return (1);
}

char	**fill_string(int i, char *path)
{
	char	*str;
	char	**strs;
	int		fd;

	fd = open(path, O_RDWR, 0666);
	strs = (char **)malloc((i + 1) * sizeof(char *));
	if (!strs)
		return (NULL);
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
	if (!st)
		return (0);
	tab = malloc(sizeof(int) * 3);
	if (!tab)
		return (NULL);
	d_str = ft_split(st, ',');
	if (!d_str)
		return (NULL);
	j = 0;
	while (j < 3)
	{
		tab[j] = ft_atoi(d_str[j]);
		j++;
	}
	i = -1;
	while (d_str[++i])
		free(d_str[i]);
	return (free(d_str), free(st), tab);
}
