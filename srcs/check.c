/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 18:18:15 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/12 10:00:09 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_check_config_double(t_data *data)
{
	if (data->res > 1 || data->north > 1 || data->south > 1 || data->west
	> 1 || data->east > 1 || data->sprite > 1 || data->
	ground > 1 || data->ceiling > 1)
		data->config_double = 1;
	return (0);
}

int		ft_check_config_done(t_data *data)
{
	if (data->res == 1 && data->north == 1 && data->south == 1 && data->west
	== 1 && data->east == 1 && data->south == 1 && data->sprite == 1 && data->
	ground == 1 && data->ceiling == 1)
		data->config_done = 1;
	return (0);
}

int		ft_check_first_space(t_data *data)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while (x < data->nb_lines)
	{
		y = 0;
		while (data->map[x][y] != '\0')
		{
			if (ft_is_not_wall(data->map[x][y]))
			{
				data->first_space_x = x;
				return (SUCCESS);
			}
			y++;
		}
		x++;
	}
	return (ERROR);
}

int		ft_check_map_size(t_data *data)
{
	int count;

	data->x = 0;
	data->y = 0;
	count = 0;
	if (data->nb_lines < 2)
		return (ft_error(SMALL_MAP));
	ft_check_first_space(data);
	data->x = data->first_space_x - 1;
	data->z = data->first_space_x + 1;
	while (data->x <= data->z)
	{
		data->y = 0;
		count = 0;
		while (data->map[data->x][data->y] != '\0')
		{
			if (!(ft_isspace(data->map[data->x][data->y])))
				count++;
			data->y++;
		}
		if (count < 3)
			return (ft_error(SMALL_MAP));
		data->x++;
	}
	return (SUCCESS);
}

int		ft_check_empty_line(t_data *data, char *line)
{
	int i;
	int y;

	i = 0;
	y = 0;
	if (ft_strlen(line) == 0)
		return (ERROR);
	while (line[i] != '\0')
	{
		if (ft_strchr(line, '1') == NULL && (ft_strchr(line, '0') == NULL))
			return (ERROR);
		i++;
	}
	return (SUCCESS);
}

int		ft_start_map(t_data *data, char *line)
{
	int i;
	int len;

	i = 0;
	len = ft_strlen(line);
	while (line[i] != '\0')
	{
		if (line[i] == '1' || ft_isspace(line[i]))
			i++;
		else if (line[i] == '0')
			return (ft_error(MISSING_WALL));
		else
			return (0);
	}
	if (i == len)
		data->start_map = data->nb_total_lines;
	return (SUCCESS);
}

int		ft_check_char_first_line(t_data *data, char *line)
{
	int len;

	len = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '1' || line[len] == ' ' || line[len] == '\n' ||
		line[len] == '\t')
			len++;
		else if (ft_is_not_wall(line[len]))
			return (ft_error(MISSING_WALL));
		else
			return (ft_error(WRONG_CHAR));
	}
	return (SUCCESS);
}

int		ft_check_char(t_data *data, char *line)
{
	int len;

	len = 0;
	while (line[len] != '\0')
	{
		if (line[len] == '0' || line[len] == '1' || line[len] == ' ' ||
		line[len] == '\n' || line[len] == '2' || line[len] == 'N' || line[len]
		== 'S' || line[len] == 'E' || line[len] == 'W' || line[len] == '\t')
			len++;
		else
			return (ERROR);
	}
	data->nb_lines++;
	data->len = len;
	return (SUCCESS);
}

int		ft_check_xpm_ext(char *str)
{
	int		len;
	char	*tmp;

	len = 0;
	len = ft_strlen(str);
	tmp = ft_substr(str, len - 4, len);
	if (ft_strncmp(tmp, ".xpm", 4) != 0)
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
	char	*type;

	if (argc < 2)
		return (ft_error(TOO_FEW_ARG));
	if (ft_check_arg_ext(argv[1]) == ERROR)
		return (ft_error(BAD_EXTENSION));
	if (argc == 3)
	{
		if ((ft_strncmp(argv[2], "--save", 6) != 0 || ft_strlen(argv[2]) != 6))
			return (ft_error(ERR_ARG_SAVE));
	}
	if (argc > 3)
		return (ft_error(TOO_MUCH_ARG));
	return (SUCCESS);
}
