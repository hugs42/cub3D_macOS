/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:51:14 by hugsbord          #+#    #+#             */
/*   Updated: 2020/02/20 16:51:06 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

char		*ft_strdup(const char *s)
{
	size_t		i;
	size_t		len;
	char		*str;

	i = 0;
	len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	while (i < len)
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

char		*ft_strchr(const char *s, int c)
{
	size_t		i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return ((char *)s + i);
		i++;
	}
	if (!c && s[i] == '\0')
		return ((char *)s + i);
	return (NULL);
}

void		*ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	i = 0;
	d = (char *)dst;
	s = (char *)src;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dst);
}

void		*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t		i;
	char		*d;
	char		*s;

	i = 0;
	d = (char*)dst;
	s = (char*)src;
	while (i < n)
	{
		d[i] = s[i];
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)dst + i + 1);
		i++;
	}
	return (NULL);
}

void		*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*d;
	char	*s;

	d = (char*)dst;
	s = (char*)src;
	if (s < d)
	{
		while (len--)
			d[len] = s[len];
	}
	else
		ft_memcpy(d, s, len);
	return (d);
}
