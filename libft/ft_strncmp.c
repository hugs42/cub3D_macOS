/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:26:58 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/19 11:22:27 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t		i;

	i = 0;
	if (!s1 && !s2)
		return (0);
	while (s1[i] && i < n)
	{
		if (!s2[i] || s2[i] != s1[i])
			return ((unsigned char)s1[i] - s2[i]);
		i++;
	}
	if (i < n)
		return ((unsigned char)s1[i] - s2[i]);
	return (0);
}
