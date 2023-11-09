/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_f_color.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:08:53 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/07 20:32:03 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"


int is_empty(char *str)
{
    int i;

    i = 0;
    if(!str)
        return (0);
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

char * delete_last_spaces(char *s)
{
    char *str;
    int i;
    int j;
    
    i = 0;
    j = 0;
        
    while(s[i])
        i++;
    i--;
    while(ft_isspace(s[i]))
        i--;
    str = malloc(i + 1);
    while(j <= i)
    {
           str[j] = s[j];
           j++;
    }
    str[j] = '\0';
    // printf("tetse ->>> %s\n" , str);
    return(str);
}
int check_floor_sky(char* str)
{
    int i;
    char *s;
    char *st;
    
    i = skips_spaces(str);
    st = NULL;
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
                st = delete_last_spaces(s);
                if(check_the_color(st))
                    return (2);
                break;
            }
        }
        i++;
    }
    return (0);
}