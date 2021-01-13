/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 17:36:01 by hugsbord          #+#    #+#             */
/*   Updated: 2020/02/17 12:45:58 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *s)
{
	char	*str;
	char	*tmp;
	int		i;
	int		x;

	i = 0;
	x = 0;
	if (!(str = ft_calloc(ft_strlen(s), sizeof(char))))
		return (NULL);
	if (!(tmp = ft_calloc(ft_strlen(s), sizeof(char))))
		return (NULL);
	ft_strlcpy(str, s, ft_strlen(s) + 1);
	while (str[i] != '\0')
	{
		tmp[i] = str[i];
		i++;
	}
	i--;
	while (i >= 0)
		str[x++] = tmp[i--];
	str[x] = '\0';
	free(tmp);
	return (str);
}
