/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/25 09:39:37 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/02 13:53:59 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_render_colors(int x, t_game *game, t_data *data, t_mlx *mlx)
{
	int	y;

	y = 0;
	data->ceiling_col = mlx_get_color_value(mlx->mlx_ptr, data->ceiling_col);
	data->floor_col = mlx_get_color_value(mlx->mlx_ptr, data->floor_col);
	while (y < game->ray.draw_start)
	{
		game->img->addr[y * game->img->size_l / 4 + x] = data->ceiling_col;
		y++;
	}
	y = game->ray.draw_end + 1;
	while (y < game->data.screen_h)
	{
		game->img->addr[y * game->img->size_l / 4 + x] = data->floor_col;
		y++;
	}
}

int		ft_render_walls(int x, t_game *game, t_data *data, t_tex *tex)
{
	int		y;
	int		color;

	color = 0;
	y = game->ray.draw_start;
	tex->tex_num = ft_select_textures(game);
	tex->tex_x = (int)(game->ray.wall_x * (double)tex[tex->tex_num].width);
	if (game->ray.side == 0 && game->ray.ray_dir_x > 0)
		tex->tex_x = tex->width - tex->tex_x - 1;
	if (game->ray.side == 1 && game->ray.ray_dir_y < 0)
		tex->tex_x = game->tex->width - tex->tex_x - 1;
	tex->step = 1.0 * game->tex->height / game->ray.line_height;
	tex->tex_pos = (game->ray.draw_start - data->screen_h / 2 +
	game->ray.line_height / 2) * tex->step;
	while (y <= game->ray.draw_end)
	{
		tex->tex_y = (int)tex->tex_pos & (tex[tex->tex_num].height - 1);
		tex->tex_pos += tex->step;
		color = tex[tex->tex_num].addr[tex->height * tex->tex_y + tex->tex_x];
		game->img->addr[y * game->img->size_l / 4 + x] = color;
		y++;
	}
	ft_render_colors(x, game, &game->data, game->mlx);
	return (SUCCESS);
}
