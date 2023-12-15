/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_part_one.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:39:23 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/12 00:10:47 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

int	ft_isspace(char c)
{
	if (c == ' ' || c == '\t'
		|| c == '\n' || c == '\v'
		|| c == '\f' || c == '\r'
		|| c == '\0')
		return (1);
	return (0);
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
				return (printf("Error map : \"%c\" inccorect element ",
						str[i][j]), 0);
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
