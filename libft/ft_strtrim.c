/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 15:38:43 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/21 17:35:00 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int		ft_is_set(char const c, char const *set)
{
	int i;

	i = 0;
	while (set[i] != '\0')
	{
		if (c == set[i])
			return (1);
		else
			i++;
	}
	return (0);
}

char			*ft_strtrim(char const *s1, char const *set)
{
	size_t	min;
	size_t	max;
	size_t	len;
	char	*buff;

	buff = NULL;
	if ((!s1) || (!set))
		return (NULL);
	min = 0;
	while (s1[min] != '\0' && (ft_is_set(s1[min], set) == 1))
		min++;
	max = ft_strlen(s1);
	while (min < max && (ft_is_set(s1[max - 1], set)))
		max--;
	if (min == max)
	{
		buff = (char*)malloc(sizeof(char) * 1);
		buff[0] = '\0';
		return (buff);
	}
	len = max - min;
	return (ft_substr(s1, min, len));
}
