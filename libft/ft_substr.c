/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/04 14:44:57 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/21 12:18:12 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char		*new_str;
	size_t		len_s;

	new_str = NULL;
	if (s == NULL)
		return (NULL);
	len_s = ft_strlen(s);
	if (len > len_s)
		len = len_s;
	if (start > len_s)
		start = len_s;
	if (start + len > len_s)
		len = len_s - start;
	if (!(new_str = (char *)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	ft_memmove(new_str, s + start, len);
	new_str[len] = '\0';
	return (new_str);
}
