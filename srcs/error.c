/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 11:26:11 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/09 15:54:36 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "././../includes/cub3d.h"

int		ft_arg_error(int error)
{
	if (error == TOO_FEW_ARG)
		ft_putstr_fd("Missing arguments ...\n", 1);
	else if (error == TOO_MUCH_ARG)
		ft_putstr_fd("Too much arguments ...\n", 1);
	else if (error == BAD_EXTENSION)
		ft_putstr_fd("Input file is not a .cub extension ...\n", 1);
	else if (error == ERR_ARG_SAVE)
		ft_putstr_fd("The third argument is not --save ...\n", 1);
	else if (error == DIRECTORY)
		ft_putstr_fd("Second argument is a directory ...\n", 1);
	else if (error == WRONG_FILE)
		ft_putstr_fd("File is misssing or is incorrect ...\n", 1);
	return (0);
}

int		ft_map_error(int error)
{
	if (error == EMPTY_LINE)
		ft_putstr_fd("Empty line in map ...\n", 1);
	else if (error == WRONG_CHAR)
		ft_putstr_fd("Wrong char in map ...\n", 1);
	else if (error == MISSING_WALL)
		ft_putstr_fd("The map is not close ...\n", 1);
	else if (error == SMALL_MAP)
		ft_putstr_fd("Too small map ...\n", 1);
	else if (error == ERR_PLAYER)
		ft_putstr_fd("Wrong number of player in map ...\n", 1);
	else if (error == MISSING_MAP)
		ft_putstr_fd("The map is missing ...\n", 1);
	return (0);
}

int		ft_config_error(int error)
{
	if (error == WRONG_CONFIG)
		ft_putstr_fd("One or more elements are missing in map config ...\n", 1);
	else if (error == CONFIG_DOUBLE)
		ft_putstr_fd("One or more elements are duplicated in map config ...\n",
		1);
	else if (error == PATH_ERR)
		ft_putstr_fd("Wrong path file for texture or sprite ...\n", 1);
	else if (error == TEX_ERR)
		ft_putstr_fd("Invalid texture file ...\n", 1);
	else if (error == XPM_ERR)
		ft_putstr_fd("Texture or sprite is not a .xpm extension ...\n", 1);
	else if (error == RES_ERR)
		ft_putstr_fd("Wrong window's resolution ...\n", 1);
	else if (error == COLOR_ERR)
		ft_putstr_fd("Wrong color's configuration ...\n", 1);
	else if (error == WRONG_LINE)
		ft_putstr_fd("There is a wrong line in config header ...\n", 1);
	return (0);
}

int		ft_error(int error)
{
	ft_putstr_fd("Error\n", 1);
	ft_arg_error(error);
	ft_config_error(error);
	ft_map_error(error);
	if (error == BMP_ERR)
		ft_putstr_fd("Error while creating BMP screenshot ...\n", 1);
	ft_putstr_fd("Leaving program\n", 1);
	exit(0);
}
