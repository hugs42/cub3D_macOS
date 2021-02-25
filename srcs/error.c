/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:26:11 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/25 10:45:20 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "././../includes/cub3d.h"

int		ft_error(int error)
{
	if (error == EMPTY_LINE)
		ft_putstr_fd("Error: empty line in map ...\n", 1);
	else if (error == WRONG_CHAR)
		ft_putstr_fd("Error: wrong char in map ...\n", 1);
	else if (error == MISSING_WALL)
		ft_putstr_fd("Error: the map is not close ...\n", 1);
	else if (error == TOO_FEW_ARG)
		ft_putstr_fd("Error: missing arguments ...\n", 1);
	else if (error == TOO_MUCH_ARG)
		ft_putstr_fd("Error: too much arguments ...\n", 1);
	else if (error == BAD_EXTENSION)
		ft_putstr_fd("Error: input file is not a .cub extension ...\n", 1);
	else if (error == MALLOC_ERR)
		ft_putstr_fd("Error: memory not correctly allocated (malloc) ...\n", 1);
	else if (error == SMALL_MAP)
		ft_putstr_fd("Error: too small map ...\n", 1);
	else if (error == ERR_PLAYER)
		ft_putstr_fd("Error: wrong number of player in map ...\n", 1);
	ft_putstr_fd("Leaving program\n", 1);
	return (ERROR);
}
