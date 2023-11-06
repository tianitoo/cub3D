/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hamza <hamza@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 19:10:34 by hachahbo          #+#    #+#             */
/*   Updated: 2023/11/06 20:49:19 by hamza            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int skips_spaces(char *str)
{
    int  i;
    i = 0;
    while(str[i])
    {
        if(ft_isspace(str[i]))
            i++;
        else
            break;
    }
    return(i);
} 

int check_the_order(char *str)
{
    int i;

    i = skips_spaces(str);   
    while(str[i])
    {
        if(str[i] == 'N' && str[i + 1] == 'O' && ft_isspace(str[i+2]))
            return(i+2);
        else if(str[i] == 'S' && str[i + 1] == 'O' && ft_isspace(str[i+2]))
            return(i+2);
        else if(str[i] == 'W' && str[i + 1] == 'E' && ft_isspace(str[i+2]))
            return(i+2);
        else if(str[i] == 'E' && str[i + 1] == 'A' && ft_isspace(str[i+2]))
            return(i+2);
        else if(str[i] == 'C' && ft_isspace(str[i + 1]))
            return(i+1);
        else if(str[i] == 'F' && ft_isspace(str[i + 1]))
            return(i+1);
        i++;
    }
    return (0);
}

char *return_the_path(char *str, int i)
{
    int j;
    char *s;
    j = 0;
    while(str[i])
    {
        if(ft_isspace(str[i]))
            i++;
        else
            break;
    }
    j = i;
    while(!ft_isspace(str[j]))
        j++;
    s = (char *)malloc(j + 1 - i);
    j = 0;
    while(!ft_isspace(str[i]))
    {
        s[j] = str[i];
        j++;
        i++;        
    }
    s[j] = '\0';
    return(s);
}
 
int file_exist(char  *str)
{
    char *s = return_the_path(str, 0);
	int fd = open(s, O_RDWR);
    if(fd == -1)
        return (0);
    return (1);
}

int check_the_order_and_path(char *str)
{
    char    *s;
    int     i;
	i = 0;
    if(!check_the_order(str))
        return(0);
    i = check_the_order(str);
    s = return_the_path(str, i);
	if(!file_exist(s))
    {
	    free(s);
		return(0);
    }
	return 1;
}