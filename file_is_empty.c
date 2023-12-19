/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_is_empty.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hachahbo <hachahbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 17:59:56 by hachahbo          #+#    #+#             */
/*   Updated: 2023/12/19 15:12:53 by hachahbo         ###   ########.fr       */
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
