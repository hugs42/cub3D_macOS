/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:44:22 by hugsbord          #+#    #+#             */
/*   Updated: 2020/03/03 15:22:30 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t		ft_strlen(const char *s)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

int			ft_strjoin_free(char **buf, char *tmp)
{
	char		*new;

	new = NULL;
	if (*buf == NULL)
	{
		if ((*buf = ft_strdup(tmp)) == NULL)
			return (ERROR);
	}
	else
	{
		if ((new = ft_strjoin(*buf, tmp)) == NULL)
			return (ERROR);
		free(*buf);
		*buf = new;
	}
	return (FINISH);
}

char		*ft_strjoin(char const *s1, char const *s2)
{
	char		*new_str;
	int			i;
	int			len;

	i = 0;
	if (!s1 || !s2)
		return (NULL);
	if (!(new_str = (char *)malloc(sizeof(char) * (ft_strlen(s1) +
						ft_strlen(s2) + 1))))
		return (NULL);
	while (s1[i])
	{
		new_str[i] = s1[i];
		i++;
	}
	len = i;
	i = 0;
	while (s2[i])
		new_str[len++] = s2[i++];
	new_str[len] = '\0';
	return (new_str);
}

char		*ft_check_buff(char *buff)
{
	char		*tmp;
	char		*new;

	if (buff == NULL)
		return (0);
	tmp = ft_strchr(buff, ENDLINE);
	if (tmp != NULL)
	{
		if ((new = (char*)malloc(tmp - buff + 1)) == NULL)
			return (NULL);
		ft_memcpy(new, buff, (tmp - buff));
		new[tmp - buff] = '\0';
		ft_memmove(buff, tmp + 1, ft_strlen(tmp));
		return (new);
	}
	return (NULL);
}

int			get_next_line(int fd, char **line)
{
	static char			*buf = NULL;
	char				tmp[BUFFER_SIZE + 1];
	ssize_t				ret;

	if (BUFFER_SIZE == 0 || fd < 0 || !line || (ret = read(fd, tmp, 0)) == -1)
		return (ERROR);
	if ((*line = ft_check_buff(buf)) != NULL)
		return (SUCCES_READ);
	while ((ret = read(fd, tmp, BUFFER_SIZE)) > 0)
	{
		tmp[ret] = '\0';
		ft_strjoin_free(&buf, tmp);
		if ((*line = ft_check_buff(buf)) != NULL)
			return (SUCCES_READ);
	}
	if (ret == 0 && buf)
	{
		*line = ft_strdup(buf);
		free(buf);
		buf = NULL;
	}
	else if (ret != -1)
		*line = ft_strdup("");
	return (ret == -1) ? (ERROR) : (FINISH);
}
