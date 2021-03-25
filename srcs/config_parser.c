/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   config_parser.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 15:23:36 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/25 18:42:31 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_parse_east_west(t_data *data, char *line, int i)
{
	if (line[i] == 'E' && line[i + 1] == 'A')
	{
		data->east += 2;
		if (ft_tex_path(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->east -= 1;
	}
	else if (line[i] == 'W' && line[i + 1] == 'E')
	{
		data->west += 2;
		if (ft_tex_path(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->west -= 1;
	}
	return (SUCCESS);
}

int		ft_parse_north_south(t_data *data, char *line, int i)
{
	if (line[i] == 'N' && line[i + 1] == 'O')
	{
		data->north += 2;
		if (ft_tex_path(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->north -= 1;
	}
	else if (line[i] == 'S' && line[i + 1] == 'O')
	{
		data->south += 2;
		if (ft_tex_path(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->south -= 1;
	}
	return (SUCCESS);
}

int		ft_parse_colors(t_data *data, char *line, int i)
{
	if (line[i] == 'F' && line[i + 1] == ' ')
	{
		data->floor += 2;
		if (ft_get_color(data, line, i) == ERROR)
			return (ft_error(COLOR_ERR));
		data->floor -= 1;
	}
	else if (line[i] == 'C' && line[i + 1] == ' ')
	{
		data->ceiling += 2;
		if (ft_get_color(data, line, i) == ERROR)
			return (ft_error(COLOR_ERR));
		data->ceiling -= 1;
	}
	return (SUCCESS);
}

int		ft_parse_res_sprite(t_data *data, char *line, int i)
{
	if (line[i] == 'R' && line[i + 1] == ' ')
	{
		if (ft_get_res(data, line) == ERROR)
			return (ft_error(RES_ERR));
	}
	else if (line[i] == 'S' && line[i + 1] == ' ')
	{
		data->sprite += 2;
		if (ft_tex_path(data, line, i) == ERROR)
			return (ft_error(PATH_ERR));
		data->sprite -= 1;
	}
	return (SUCCESS);
}

int		ft_parse_config(t_data *data, char *line, int i)
{
	while (ft_isspace(line[i]))
		i++;
	ft_parse_north_south(data, line, i);
	ft_parse_east_west(data, line, i);
	ft_parse_colors(data, line, i);
	ft_parse_res_sprite(data, line, i);
	ft_check_config_double(data);
	if (data->config_double != 0)
		return (ft_error(CONFIG_DOUBLE));
	return (SUCCESS);
}
