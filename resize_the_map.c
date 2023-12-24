/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_part_five.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:09:38 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/24 17:02:29 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	complete_fill_order(t_data *data, char *str, int i)
{
	if (str[i] == 'E' && str[i + 1] == 'A' && ft_isspace(str[i + 2]))
	{
		data->e_texture = return_the_path(str, i + 2);
		if (!data->e_texture)
			return (0);
	}
	else if (str[i] == 'C' && ft_isspace(str[i + 1]))
	{
		data->c_tab = return_color(str, i + 1);
		if (!data->c_tab)
			return (0);
	}
	else if (str[i] == 'F' && ft_isspace(str[i + 1]))
	{
		data->f_tab = return_color(str, i + 1);
		if (!data->f_tab)
			return (0);
	}
	return (1);
}

int	fill_order_and_path(t_data *data, char *str)
{
	int	i;

	i = skips_spaces(str);
	if (str[i] == 'N' && str[i + 1] == 'O' && ft_isspace(str[i + 2]))
	{
		data->n_texture = return_the_path(str, i + 2);
		if (!data->n_texture)
			return (0);
	}
	else if (str[i] == 'S' && str[i + 1] == 'O' && ft_isspace(str[i + 2]))
	{
		data->s_texture = return_the_path(str, i + 2);
		if (!data->s_texture)
			return (0);
	}
	else if (str[i] == 'W' && str[i + 1] == 'E' && ft_isspace(str[i + 2]))
	{
		data->w_texture = return_the_path(str, i + 2);
		if (!data->w_texture)
			return (0);
	}
	if (!complete_fill_order(data, str, i))
		return (0);
	return (1);
}

int	complet_fill_the_map(char **str, size_t max, int i, char *tmp)
{
	int	j;

	j = 0;
	while (ft_strlen(str[i]) < max - 1)
	{
		tmp = str[i];
		str[i] = ft_strjoin(str[i], "1", 0);
		if (!str[i])
			return (0);
		free(tmp);
		j++;
	}
	return (1);
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
		if (!str[i])
			return (NULL);
		free(tmp2);
		if (ft_strlen(str[i]) != max)
		{
			if (!complet_fill_the_map(str, max, i, tmp))
				return (NULL);
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
	if (!str)
		return (NULL);
	return (str);
}
