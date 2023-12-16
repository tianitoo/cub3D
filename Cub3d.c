/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 15:52:49 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/16 14:11:07 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	is_empty(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (ft_isspace(str[i]))
			i++;
		else
			break ;
	}
	if (!str[i])
		return (0);
	return (1);
}

void	map_height_width(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
		i++;
	data->map_height = i;
	data->map_width = ft_strlen(data->map[j]);
}

int	inits_the_data(t_data *data, char **str)
{
	int	i;

	i = 0;
	init_data(data);
	while (!check_the_first_of_map(str, i))
	{
		fill_order_and_path(data, str[i]);
		i++;
	}
	data->map = fill_the_map(str, i);
	if (!cor_of_player(data))
		return (0);
	map_height_width(data);
	return (1);
}

int	fail_the_inits(t_data data)
{
	if (!data.e_texture)
		return (0);
	else if (!data.n_texture)
		return (0);
	else if (!data.s_texture)
		return (0);
	else if (!data.w_texture)
		return (0);
	else if (!data.c_tab)
		return (0);
	else if (!data.f_tab)
		return (0);
	else if (!data.map)
		return (0);
	else if (!data.order)
		return (0);
	else if (!data.player_x)
		return (0);
	else if (!data.player_y)
		return (0);
	return (1);
}
