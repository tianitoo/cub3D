/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_part_three.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:49:17 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/02 16:20:50 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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
	char	*s;
	int		j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if (check_the_first_of_map(str, j))
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
