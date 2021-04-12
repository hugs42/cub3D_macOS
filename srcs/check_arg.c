/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:18:15 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/12 15:38:58 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_tex_ext(char *str)
{
	int		len;
	char	*tmp;

	len = 0;
	len = ft_strlen(str);
	tmp = ft_substr(str, len - 4, len);
	if ((ft_strncmp(tmp, ".xpm", 4) != 0) && (ft_strncmp(tmp, ".png", 4) != 0))
		return (ERROR);
	free(tmp);
	return (SUCCESS);
}

int		ft_check_arg_ext(char *str)
{
	int		len;
	char	*tmp;

	len = 0;
	len = ft_strlen(str);
	tmp = ft_substr(str, len - 4, len);
	if (ft_strncmp(tmp, ".cub", 4) != 0)
		return (ERROR);
	free(tmp);
	return (SUCCESS);
}

int		ft_check_arg(int argc, char **argv)
{
	if (argc < 2)
		ft_error(TOO_FEW_ARG);
	if (ft_check_arg_ext(argv[1]) == ERROR)
		ft_error(BAD_EXTENSION);
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6) != 0 || ft_strlen(argv[2]) != 6))
			ft_error(ERR_ARG_SAVE);
		else
			return (2);
	}
	if (argc > 3)
		ft_error(TOO_MUCH_ARG);
	return (SUCCESS);
}
