/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/25 15:26:12 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/07 09:22:55 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_parse_info_map(t_data *data, char *line)
{
	static int i = 0;

	i++;
	if (ft_check_char(data, line) == ERROR)
		return (ft_error(WRONG_CHAR));
	if (data->len > data->max_len)
		data->max_len = data->len;
	return (SUCCESS);
}

int		ft_parse_line_2(t_data *data, char *line, int i)
{
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

int		ft_parse_line(t_data *data, char *line)
{
	int				len;
	int				i;
	static int		x = 0;

	len = 0;
	i = 0;
	len = ft_strlen(line);
	data->nb_total_lines += 1;
	ft_check_config_done(data);
	i = ft_skip_spaces(line, i);
	if (line[i] == '\n' || line[i] == '\0' || len == 0)
		return (SUCCESS);
	else if (ft_parse_config(data, line, i) != SUCCESS)
		return (ERROR);
	if (ft_parse_line_2(data, line, i) != SUCCESS)
		return (ERROR);
	return (SUCCESS);
}

int		ft_parse_map(t_data *data, char *line)
{
	ft_get_map(data, line);
	ft_check_map_size(data);
	ft_check_border(data);
	ft_check_wall(data);
	ft_check_player(data);
	ft_replace_spaces(data);
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
	free(line);
	if (data->start_map == 0)
		return (ft_error(MISSING_MAP));
	if (data->config_done == 0)
		return (ft_error(WRONG_CONFIG));
	if (data->config_double != 0)
		return (ft_error(CONFIG_DOUBLE));
	close(data->fd);
	ft_parse_map(data, argv[1]);
	return (SUCCESS);
}
