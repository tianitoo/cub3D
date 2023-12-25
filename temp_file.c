/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_file.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/03 22:51:45 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 17:32:29 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	complete_check_the_new_line(char **strs, int i)
{
	int	j;

	j = 0;
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

int	findmap(char **str, int i)
{
	int	j;

	j = 0;
	i = 0;
	while (str[i])
	{
		j = skips_spaces(str[i]);
		while (str[i][j] == '1')
			j++;
		if (str[i][j] == '\n' && j != 0)
			return (i);
		i++;
	}
	return (0);
}

int	check_the_new_line(char **strs)
{
	int	i;

	i = findmap(strs, 0);
	if (!i)
		return (printf("Error\ninvalid"), 0);
	i++;
	if (!complete_check_the_new_line(strs, i))
		return (printf("Error\nthe map is inccorrect\n"), 0);
	return (1);
}

int	check_map_is_there_is_there_new_line(int i, char *path)
{
	char	*str;
	char	**strs;
	int		fd;

	fd = open(path, O_RDWR, 0666);
	if (fd == -1)
		return (0);
	strs = (char **)malloc((i + 1) * sizeof(char *));
	if (!strs)
		return (close(fd), 0);
	str = get_next_line(fd);
	i = 0;
	while (str)
	{
		strs[i] = ft_strdup(str);
		if (!strs)
			return (close(fd), 0);
		free(str);
		str = get_next_line(fd);
		i++;
	}
	strs[i] = NULL;
	if (!check_the_new_line(strs) || !check_the_file_is_empty(strs))
		return (printf("Error\nempty file"), free_two_d(strs), close(fd), 0);
	return (free_two_d(strs), close(fd), 1);
}

int	count_the_lines_one(char *path)
{
	char	*str;
	int		i;
	int		fd;

	fd = open(path, O_RDWR, 0666);
	if (fd == -1)
		return (printf("Error\nfile doesn't exist"), close(fd), 0);
	i = 0;
	str = get_next_line(fd);
	while (str)
	{
		i++;
		free(str);
		str = get_next_line(fd);
	}
	close(fd);
	if (!i)
		return (printf("Error\nfile is empty\n"), 0);
	return (i);
}
