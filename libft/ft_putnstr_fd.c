/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnstr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 11:55:05 by hugsbord          #+#    #+#             */
/*   Updated: 2019/12/13 12:24:56 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_putnstr_fd(char const *s, size_t len, int fd)
{
	size_t i;

	i = 0;
	while (s[i] && i < len)
	{
		ft_putchar_fd(s[i], fd);
		i++;
	}
	return (i);
}
