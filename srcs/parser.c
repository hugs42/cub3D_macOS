/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:26:12 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/26 10:04:49 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_parse_line(t_data *data, char *line)
{
	int		len;
	int		i;
	static int		x = 0;

	len = 0;
	i = 0;
//	printf("start_map= %d \n", data->start_map);
	len = ft_strlen(line);
	data->nb_total_lines += 1;
	ft_check_config_done(data);
	i = ft_skip_spaces(line, i);
	if (line[i] == '\n' || line[i] == '\0' || len == 0)
		return (SUCCESS);
	else if (ft_parse_config(data, line, i) != SUCCESS)
		return (ERROR);
	if (data->start_map == 0 && data->config_done == 1)
	{
		if (ft_check_char_first_line(data, line) == ERROR)
			return (ERROR);
		if (ft_start_map(data, line) == ERROR)
			return (ERROR);
	}
	else if (data->start_map != 0 && data->nb_total_lines >= data->start_map)
	{
		i = ft_skip_spaces(line, i);
		if (!(ft_isspace(line[i])))
		{
			if (ft_parse_info_map(data, line) != SUCCESS)
				return (ERROR);
		}
	}
	return (SUCCESS);
}

int		ft_parser(int argc, char **argv, t_data *data)
{
	int			ret;
	char		*line;

	ret = 1;
	if ((data->fd = open(argv[1], O_DIRECTORY) != -1))
		return (ft_error(DIRECTORY));
	if ((data->fd = open(argv[1], O_RDONLY)) < 0)
		return (ft_error(WRONG_FILE));
	while ((ret = get_next_line(data->fd, &line)) > 0)
	{
		if (ft_parse_line(data, line) != SUCCESS)
			return (ERROR);
		free(line);
	}
	if (data->start_map == 0)
		return (ft_error(MISSING_MAP));
	if (data->config_done == 0)
		return (ft_error(WRONG_CONFIG));
	if (data->config_double != 0)
		return (ft_error(CONFIG_DOUBLE));
	close(data->fd);
	if (ft_parse_map(data, argv[1]) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}
