/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hnait <hnait@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:48:05 by hnait             #+#    #+#             */
/*   Updated: 2023/10/08 09:42:05 by hnait            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_gnl_substr(char const *s, size_t len)
{
	char	*ss;
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	if (len > ft_strlen(s))
		len = ft_strlen(s);
		ss = (char *) malloc (sizeof(char) * (len + 1));
	if (!ss)
		return (NULL);
	while (i < len && s[i])
	{
		ss[i] = s[i];
		i++;
	}
	ss[i] = '\0';
	return (ss);
}

int	find_nl_index(char **next_line, char *buffer)
{
	int		i;
	char	*tmp_nl;

	i = 0;
	tmp_nl = ft_strjoin(*next_line, buffer, 0);
	if (!tmp_nl)
		return (-2);
	free(*next_line);
	*next_line = tmp_nl;
	while ((*next_line)[i] != '\0')
	{
		if ((*next_line)[i] == '\n')
			return (i + 1);
		i++;
	}
	return (-1);
}

int	find_nl(char **next_line, int fd)
{
	char	*buffer;
	int		i;
	int		eof;

	eof = 1;
	buffer = (char *)ft_calloc(sizeof(char), BUFFER_SIZE + 1);
	if (!buffer)
		return (-1);
	if (ft_strlen(*next_line) == 0)
		eof = read(fd, buffer, BUFFER_SIZE);
	while (eof > 0)
	{
		i = find_nl_index(next_line, buffer);
		if (i >= 0)
			return (free(buffer), i);
		if (i == -2)
			return (free(buffer), -1);
		eof = read(fd, buffer, BUFFER_SIZE);
	}
	if (eof == -1)
		return (free(buffer), -1);
	return (free(buffer), ft_strlen(*next_line));
}

void	remove_nl(char *next_line, int nl_index)
{
	int	i;

	i = 0;
	while (next_line[nl_index] != '\0')
		next_line[i++] = next_line[nl_index++];
	while (next_line[i])
		next_line[i++] = '\0';
}

char	*get_next_line(int fd)
{
	static char	*next_line;
	char		*return_value;
	int			nl_index;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!next_line)
	{
		next_line = (char *)ft_calloc(sizeof(char), 1);
		if (!next_line)
			return (NULL);
	}
	nl_index = find_nl(&next_line, fd);
	if (nl_index < 0 || ft_strlen(next_line) <= 0)
		return (free(next_line), next_line = NULL, NULL);
	return_value = ft_gnl_substr(next_line, nl_index);
	if (!return_value)
		return (free(next_line), next_line = NULL, NULL);
	remove_nl(next_line, nl_index);
	return (return_value);
}
