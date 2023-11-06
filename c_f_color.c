/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_f_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:08:53 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/06 20:57:57 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int is_empty(char *str)
{
    int i;

    i = 0;
    while(str[i])
    {
        if(ft_isspace(str[i]))
            i++;
        else
            break;
    }
    if(!str[i])
        return (0);
    return(1);
}
int check_the_color(char *str)
{
    int  i;
    int x;
    char **strs;
    int n;
    int j;
    
    j = 0;
    x = 0;
    n = 0;
    strs = ft_split(str, ',');
    i  = 0;
    while (strs[i])
    {
        if(i >= 3 || !is_empty(strs[i]))
            return (0);
        j = 0;
        if(strs[i][0] == ' ')
            return (0);
        while(strs[i][j])
        {
            if(!(ft_isdigit(strs[i][j])) && strs[i][j] != '\n')
                return (0);
            j++;
        }
        n = ft_atoi(strs[i]);
        if(n >=  0 && n < 256)
            x++;
        i++;
    }
    if(x == 3)
        return (1);
    return (0);
}

int check_floor_sky(char* str)
{
    int i;
    char *s;
    
    i = skips_spaces(str);
    while(str[i])
    {
        if((str[i] == 'C' || str[i] == 'F'))
        {
            s = ft_strdup(str + 1);
            i = skips_spaces(s);
            free(s);
            i++;
            if(ft_isspace(str[i - 1]))
            {
                s = ft_strdup(str + i);
                if(check_the_color(s))
                    return (2);
                break;
            }
        }
        i++;
    }
    return (0);
}