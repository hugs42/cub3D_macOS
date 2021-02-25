/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:26:12 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/25 15:27:17 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_parser(int argc, char **argv, t_data *data)
{
	int			fd;
	int			ret;
	char		*line;
	t_data		*map_buff;

	ret = 1;
	if ((fd = open(argv[1], O_DIRECTORY) != -1))
		return (ft_error(DIRECTORY));
	if ((fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(WRONG_FILE));
	while ((ret =  get_next_line(fd, &line)) > 0)
	{
		if (ft_parse_line(data, line) != SUCCESS)
			return (ERROR);
		free(line);
	}
	close(fd);
	if (ft_parse_map(data, argv[1]) != SUCCESS)
		return (ERROR);
	int i = 0;
	while (i <= data->nb_lines)
	{
		printf("%s\n", data->map[i]);
		i++;
	}
	printf("\n start_map = %d\n", data->start_map);
	return (SUCCESS);
}
