/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:52:53 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/15 16:36:40 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*new_str;
	int		i;
	int		len;

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
