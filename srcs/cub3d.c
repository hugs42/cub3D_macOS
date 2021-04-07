/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/07 09:27:33 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_game_loop(t_game *game, t_data *data)
{
	ft_key_events(game);
	ft_raycasting(game);
	return (0);
}

int		ft_get_size_screen(t_game *game, t_data *data)
{
	int		max_width;
	int		max_height;

	max_width = 0;
	max_height = 0;
	mlx_get_screen_size(game->mlx->mlx_ptr, &max_width, &max_height);
	if (data->screen_w > max_width)
		data->screen_w = max_width;
	if (data->screen_h > max_height)
		data->screen_h = max_height;
	return (SUCCESS);
}

int		ft_game_init(t_game *game, t_data *data)
{
	ft_setup_player(game->player, &game->data);
	ft_init_raycasting(game);
	game->mlx->mlx_ptr = mlx_init();
	ft_get_size_screen(game, data);
	ft_setup_textures(game, data, game->mlx);
	if (data->sprite_nb > 0)
		ft_setup_sprites(game, &game->data);
	game->mlx->win = (mlx_new_window(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h, "cub3D"));
	game->img->img_ptr = mlx_new_image(game->mlx->mlx_ptr, data->screen_w,
	data->screen_h);
	game->img->addr = (int*)mlx_get_data_addr(game->img->img_ptr,
	&game->img->bpp, &game->img->size_l, &game->img->endian);
	return (SUCCESS);
}

int		ft_game(t_game *game, t_data *data)
{
	if (ft_game_init(game, data) == ERROR)
		return (ERROR);
	mlx_loop_hook(game->mlx->mlx_ptr, &ft_game_loop, game);
	mlx_hook(game->mlx->win, KEY_PRESS, 0, &ft_press_key, game);
	mlx_hook(game->mlx->win, KEY_RELEASE, 0, &ft_release_key, game);
	mlx_hook(game->mlx->win, 17, 0, &ft_exit, game);
	mlx_loop(game->mlx->mlx_ptr);
	return (SUCCESS);
}

int		main(int argc, char **argv)
{
	int			save;
	t_game		game;

	save = 0;
	save = ft_check_arg(argc, argv);
	ft_init_game(&game);
	ft_parser(argc, argv, &game.data);

	if (save == 2)
		game.save = 1;
	ft_game(&game, &game.data);
	return (0);
}
