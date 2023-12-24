/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_f_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:08:53 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 17:34:11 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	free_d_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}

int	while_of_check_the_color(int i, char *str)
{
	int	j;

	j = 0;
	if (i >= 3 || !is_empty(str))
		return (0);
	if (str[j] == ' ')
		return (0);
	while (str[j])
	{
		if (!(ft_isdigit(str[j])) && str[j] != '\n')
			return (0);
		j++;
	}
	return (1);
}

int	check_the_color(char *str)
{
	int		i;
	int		x;
	char	**strs;
	int		n;

	x = 0;
	n = 0;
	strs = ft_split(str, ',');
	i = 0;
	if (!check_coma(str))
		return (free_d_strs(strs), 0);
	while (strs[i])
	{
		if (!while_of_check_the_color(i, strs[i]))
			return (free_d_strs(strs), 0);
		n = ft_atoi(strs[i]);
		if (n >= 0 && n < 256)
			x++;
		i++;
	}
	free_d_strs(strs);
	if (x == 3)
		return (1);
	return (0);
}

char	*delete_last_spaces(char *s)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (s[i])
		i++;
	i--;
	while (ft_isspace(s[i]))
		i--;
	str = malloc(i + 1);
	if (!str)
		return (NULL);
	while (j <= i)
	{
		str[j] = s[j];
		j++;
	}
	str[j] = '\0';
	return (str);
}

int	check_floor_sky(char *str)
{
	int		i;
	char	*s;
	char	*st;

	st = NULL;
	i = skips_spaces(str) - 1;
	while (str[++i])
	{
		if (str[i] == 'C' || str[i] == 'F')
		{
			s = ft_strdup(str + 1);
			if (!s || !str[i])
				return (0);
			i = skips_spaces(s);
			free(s);
			i++;
			if (ft_isspace(str[i - 1]))
			{
				if (complete_check(s, st, str, i))
					return (2);
				return (0);
			}
		}
	}
	return (0);
}
