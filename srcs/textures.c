/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/27 12:46:53 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/25 10:30:54 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_select_textures(t_game *game)
{
	int num;

	if (game->data.map[game->ray.map_x][game->ray.map_y] == '1')
		num = 0;
	else if (game->data.map[game->ray.map_x][game->ray.map_y] == '2')
		num = 1;
	if (game->ray.side == 1)
		num = 1;
	else if (game->ray.side == 2)
		num = 2;
	else if (game->ray.side == 3)
		num = 3;
	return (num);
}

void	ft_copy_addr_content(int *addr, int *tmp_addr, int width, int height)
{
	int		x;
	int		y;

	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			addr[width * y + x] = tmp_addr[width * y + x];
			x++;
		}
		y++;
	}
}

int		ft_load_texture(char *path, t_mlx *mlx, t_tex *tex)
{
	void	*img_tmp_ptr;
	int		*addr_tmp;
	int		tmp;

	if (!(img_tmp_ptr = mlx_xpm_file_to_image(mlx->mlx_ptr, path, &tex->width,
	&tex->height)))
		return (ERROR);
	addr_tmp = (int *)mlx_get_data_addr(img_tmp_ptr, &tmp, &tmp, &tmp);
	tex->addr = (int *)malloc(sizeof(int) * tex->width * tex->height);
	ft_copy_addr_content(tex->addr, addr_tmp, tex->width, tex->height);
	mlx_destroy_image(mlx->mlx_ptr, img_tmp_ptr);
	tex->step = 0;
	tex->tex_pos = 0;
	tex->tex_x = 0;
	tex->tex_y = 0;
	return (SUCCESS);
}

int		ft_setup_textures(t_game *game, t_data *data, t_mlx *mlx)
{
	t_img	*tex;

	if (ft_load_texture(data->path_no, game->mlx, &game->tex[0]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_so, game->mlx, &game->tex[1]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_ea, game->mlx, &game->tex[2]) == ERROR)
		return (ft_error(TEX_ERR));
	if (ft_load_texture(data->path_we, game->mlx, &game->tex[3]) == ERROR)
		return (ft_error(TEX_ERR));
	return (SUCCESS);
}
