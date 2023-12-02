/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_part_two.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:45:38 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/02 16:20:59 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
