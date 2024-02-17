/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yrimek <yrimek@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/16 13:21:11 by yrimek            #+#    #+#             */
/*   Updated: 2024/02/17 17:49:19 by yrimek           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

size_t	ft_strlen(char const *str)
{
	int	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

char	*ft_strchr(const char *str, int c)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] == (char)c)
			return ((char *)&str[i]);
		i++;
	}
	return (NULL);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*str;
	size_t	len;

	if (s1)
		len = ft_strlen(s1);
	if (s2)
		len = ft_strlen(s1) + ft_strlen(s2);
	str = malloc(sizeof(char) * (len + 1));
	if (!str)
		return (NULL);
	len = 0;
	while (s1 && s1[len])
	{
		str[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2 && s2[i])
	{
		str[len + i] = s2[i];
		i++;
	}
	str[len + i] = '\0';
	return (free((char *)s1), str);
}

char	*ft_select_left(char *buf)
{
	int		i;
	char	*dest;

	if (!buf[0])
		return (NULL);
	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
		i++;
	if (buf[i] == '\n')
		i++;
	dest = malloc(sizeof(*dest) * (i + 1));
	if (!dest)
		return (NULL);
	i = 0;
	while (buf && buf[i] && buf[i] != '\n')
	{
		dest[i] = buf[i];
		i++;
	}
	if (buf[i] == '\n')
		dest[i++] = '\n';
	dest[i] = '\0';
	return (dest);
}

void	ft_select_right(char *buf)
{
	int	i;
	int	j;

	i = 0;
	if (ft_strchr(buf, '\n'))
	{
		while (buf && buf[i] && buf[i] != '\n')
			i++;
		j = 0;
		while (buf && buf[i])
			buf[j++] = buf[++i];
		buf[j] = '\0';
	}
	else
		buf[0] = '\0';
}

char	*get_next_line(int fd)
{
	static char	str[BUFFER_SIZE + 1] = "";
	char		*temp;
	int			ret;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	ret = BUFFER_SIZE;
	temp = NULL;
	while (ret > 0)
	{
		if (ft_strchr(str, '\n'))
			break ;
		ret = read(fd, str, BUFFER_SIZE);
		if (ret == -1)
			return (free(temp), NULL);
		else if (ret > 0)
		{
			str[ret] = '\0';
			temp = ft_strjoin(temp, str);
			
		}
		else
			str[ft_strlen(str)] = 0;
	}
	line = ft_select_left(str);
	ft_select_right(str);
	//printf("str = %s\n", str);
	return (line);
}

int	main(void)
{
	int		fd;
	char	*gnl;

	fd = open("text.txt", O_RDONLY);
	gnl = get_next_line(fd);
	while (gnl)
	{
		printf("%s", gnl);
		free(gnl);
		gnl = get_next_line(fd);
	}
	printf("%s", gnl);
}
