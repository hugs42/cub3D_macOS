/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp_save.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 13:16:16 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/06 15:30:41 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_file_header(t_game *game, int fd)
{
	int size;
	int zero;
	int p_data_offset;

	size = 0;
	zero = 0;
	p_data_offset = 54;
	write(fd, "BM", 2);
	size = p_data_offset + game->data.screen_w * game->data.screen_h;
	write(fd, &size, 4);
	write(fd, &zero, 2);
	write(fd, &zero, 2);
	write(fd, &p_data_offset, 4);
}

void	ft_img_header(t_game *game, int fd)
{
	int h_size;
	int img_size;
	int plane;
	int zero;

	h_size = 40;
	img_size = game->data.screen_w * game->data.screen_h;
	plane = 1;
	zero = 0;
	write(fd, &h_size, 4);
	write(fd, &game->data.screen_w, 4);
	write(fd, &game->data.screen_h, 4);
	write(fd, &plane, 2);
	write(fd, &game->img->bpp, 2);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &img_size, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
	write(fd, &zero, 4);
}

int		ft_screen_bmp(t_game *game, int fd)
{
	int x;
	int y;

	y = 0;
	while (y <= game->data.screen_h)
	{
		x = 0;
		while (x < game->data.screen_w)
		{
			write(fd, &game->img->addr[y * game->img->size_l / 4 + x], 4);
			x++;
		}
		y++;
	}
	return (SUCCESS);
}

int		ft_bmp(t_game *game)
{
	int		fd;

	if ((fd = open("screenshot.bmp", O_CREAT | O_RDWR, 0644)) == -1)
		return (ft_error(BMP_ERR));
	ft_file_header(game, fd);
	ft_img_header(game, fd);
	ft_screen_bmp(game, fd);
	ft_exit(game);
	return (SUCCESS);
}
