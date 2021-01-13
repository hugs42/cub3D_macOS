/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minilbx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s72h <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 12:44:16 by s72h              #+#    #+#             */
/*   Updated: 2020/05/12 22:03:48 by s72h             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mlx.h>
#include "./includes/cub3d.h"

/*t_mlx		*ft_init_game(void)
{
	t_mlx *g1;
	
	if (!(g1 = (t_mlx*)malloc(sizeof(t_mlx))))
		return (NULL);
	g1->plan_x = 0;
	g1->plan_y = 0;
	g1->time = 0;
	g1->old_time = 0;
	g1->camera_x = 32;
	g1->raydir_x = 0;
	g1->raydir_y =  0;
	g1->widthscreen = CASE_X * BLOCK_SIZE;
	g1->heightscreen = CASE_Y * BLOCK_SIZE;
	return (g1);
}*/

int		ft_exit_window(int keycode, t_mlx *g1)
{
	mlx_destroy_window(g1->mlx, g1->win);
	return (0);
}

void	ft_mlx_pixel_put(t_image *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_l + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

int		ft_deal_key(int key, t_mlx *g1)
{
//	char	*str;
	int i = 0;
	t_image img;
//	str = "Cyber| 25/		return (0);/
	img.img_ptr = mlx_new_image(g1->mlx, 1200, 800);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	ft_putnbr_fd(key, 1);
	if (key == 53)
		ft_exit_window(key, g1);
	if (key == 13)
	{
		i = 0;
		while (i < 800)
		{
			ft_mlx_pixel_put(&img, i, 500, 0xFFFFFF);
			i++;
		}
	}
//	mlx_pixel_put(g1->mlx, g1->win, 250,  250, 43);
//	ft_putstr_fd(str, 1);

//	mlx_string_put(g1->mlx, g1->window, 250, 250, 21, 0);
//	mlx_pixel_put(mlx, window,	250, 250, 12);
	return (0);
}

int		ft__game(void *mlx, void *window)
{

/*	int		x;

	x = 0;
	while (x < w)
	{
		g1->camera_x = 2 * x / double(w) - 1;
		g1->raydir_x = dir_x + plan_x * camera_x;
		g1->raydir_y = dir_y + plan_y * camera_x;
		x++;
	}*/
	return (0);
}

int		ft_parser(char *arg)
{
	return (0);
}



int		main(int argc, char **argv)
{
//	if (argc != 2)
//		return (ERROR);
	t_mlx		g1;
	t_image		img;
	int			count_w;
	int			count_h;

	int		x = 0;
	int		y = 0;
	int		i = 0;
	if ((g1.mlx = mlx_init()) == NULL)
		return (-1);
	if ((g1.win = mlx_new_window(g1.mlx, WIN_W, WIN_H, "Cub3d")) == NULL)
		return (-1);
	img.img_ptr = mlx_new_image(g1.mlx, 800, 600);
	img.addr = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l, &img.endian);
	while (i < 400)
	{
		ft_mlx_pixel_put(&img, x, y, 0x00FF0000);
//		ft_mlx_pixel_put(&img, x, y, 0x00FF0000);
//		ft_mlx_pixel_put(&img, x, y, 0x00FF0000);
		x++;
		y++;
		i++;
	}
	mlx_put_image_to_window(g1.mlx, g1.win, img.img_ptr, 0, 0);
	mlx_key_hook(g1.win, ft_deal_key, &g1);
	mlx_loop(g1.mlx);
	return (0);
}
