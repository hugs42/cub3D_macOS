/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:18:15 by hugsbord          #+#    #+#             */
/*   Updated: 2021/01/14 18:53:41 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_params(t_data *data)
{
	return (0);
}

int		ft_check_char(t_data *data, char *line)
{
	int i;

	i = 0;
//      printf("%s\n", line);
	while (line[i] != '\0')
	{
//      printf("%c", line[i + 2]);
		if (line[i] == '0' || line[i] == '1' || line[i] == ' ' || 
		line[i] == '\n' || line[i] == '2' || line[i] == 'N' || line[i] == 'S'
		|| line[i] == 'E' || line[i] == 'W')
			i++;
		else
		{
//			printf("%c", line[i]);
//			printf("NOP ");
			return (ERROR);
		}
	}
//	printf("%s\n",line);
	return (0);
}

int		ft_check_ext(char *str)
{
	int		len;
	char	*tmp;

	len = 0;
	len = ft_strlen(str);
	tmp = ft_substr(str, len - 4, len);
	if (ft_strncmp(tmp, ".cub", 4) != 0)
		return (ERROR);
	return (SUCCESS);
}

int		ft_check_arg(int argc, char **argv)
{
	int		id_error;
	char	*type;

	id_error = 0;
	if (argc < 2)
		id_error = 1;
	if (argc > 3)
		id_error = 2;
	if ((id_error != 0) || (ft_check_ext(argv[1]) == ERROR))
		return (ERROR);
	return (SUCCESS);
}
