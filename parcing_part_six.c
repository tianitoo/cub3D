/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parcing_part_six.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 16:12:34 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/02 16:20:44 by hachahbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include  "cub3D.h"

char	**allocate_for_d_str(char **str, int i)
{
	int		j;
	char	**d_str;

	j = i;
	while (str[i])
		i++;
	d_str = malloc(sizeof(char *) * i - j + 1);
	i = j;
	j = 0;
	while (str[i])
	{
		d_str[j] = ft_strdup(str[i]);
		i++;
		j++;
	}
	return (d_str);
}

char	**fill_the_map(char **str, int i)
{
	int		j;
	char	**d_str;
	char	**new_map;

	d_str = allocate_for_d_str(str, i);
	i = 0;
	j = 0;
	while ((d_str[i]))
	{
		j = 0;
		while (d_str[i][j])
		{
			if (d_str[i][j] == ' ')
				d_str[i][j] = '1';
			j++;
		}
		i++;
	}
	new_map = resize_the_map(d_str);
	return (new_map);
}

char	set_player_direction(char c, t_data *data)
{
	if (c == 'N')
		data->player_dir = NORTH;
	else if (c == 'S')
		data->player_dir = SOUTH;
	else if (c == 'E')
		data->player_dir = EAST;
	else if (c == 'W')
		data->player_dir = WEST;
	return (c);
}

int cor_of_player(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (data->map[i])
	{
		j = 0;
		while (data->map[i][j])
		{
			if (data->map[i][j] == 'N' || data->map[i][j] == 'E' 
				|| data->map[i][j] == 'W' || data->map[i][j] == 'S')
			{
				data->player_x = i * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->player_y = j * SQUARE_SIZE + SQUARE_SIZE / 2;
				data->order = set_player_direction(data->map[i][j], data);
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	init_data(t_data *data)
{
	data->c_tab = NULL;
	data->f_tab = NULL;
	data->e_texture = 0;
	data->n_texture = 0;
	data->w_texture = 0;
	data->s_texture = 0;
	data->order = 0;
	data->player_x = 0;
	data->player_y = 0;
	data->map = NULL;
}
