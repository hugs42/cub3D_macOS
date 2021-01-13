/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 17:28:01 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/21 17:43:49 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	unsigned int len_2;

	if (*needle == '\0')
		return ((char *)haystack);
	len_2 = ft_strlen(needle);
	while (*haystack != '\0' && len >= len_2)
	{
		if (*haystack == *needle && ft_memcmp(haystack, needle, len_2) == 0)
			return ((char *)haystack);
		haystack++;
		len--;
	}
	return (NULL);
}
