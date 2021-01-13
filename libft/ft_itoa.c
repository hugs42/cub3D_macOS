/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/23 13:51:39 by hugsbord          #+#    #+#             */
/*   Updated: 2019/11/21 17:30:26 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_intlen(int n)
{
	size_t			i;

	i = 1;
	while (n /= 10)
		i++;
	return (i);
}

static char		*ft_check_min_zero(int n)
{
	char *str;

	if (n == -2147483648)
	{
		if (!(str = (char*)malloc(sizeof(char) + 11)))
			return (NULL);
		ft_memcpy(str, "-2147483648", 11);
		str[11] = '\0';
		return (str);
	}
	else if (n == 0)
	{
		if (!(str = (char*)malloc(sizeof(char) * 1 + 1)))
			return (NULL);
		ft_memcpy(str, "0", 1);
		str[1] = '\0';
		return (str);
	}
	return (NULL);
}

char			*ft_itoa(int n)
{
	char			*str;
	size_t			len;
	size_t			len_tmp;
	int				n_tmp;

	len = ft_intlen(n);
	n_tmp = n;
	len_tmp = len;
	if ((n == -2147483648) || (n == 0))
		return (ft_check_min_zero(n));
	if (n < 0)
	{
		n_tmp = -n;
		len++;
	}
	if (!(str = (char *)malloc(sizeof(char) * len + 1)))
		return (NULL);
	str[--len] = n_tmp % 10 + 48;
	while (n_tmp /= 10)
		str[--len] = n_tmp % 10 + 48;
	if (n < 0)
		*(str + 0) = '-';
	len_tmp = n < 0 ? ++len_tmp : len_tmp;
	str[len_tmp] = '\0';
	return (str);
}
