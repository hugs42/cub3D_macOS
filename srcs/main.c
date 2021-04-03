/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:36:27 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/03 13:52:39 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

int		ft_game_loop(t_game *game, t_data *data)
{
	ft_key_events(game);
	ft_raycasting(game);
	return (0);
}

int		ft_game_init(t_game *game, t_data *data)
{
	ft_setup_player(game->player, &game->data);
	ft_init_raycasting(game);
	game->mlx->mlx_ptr = mlx_init();
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
	t_game		game;

	if (ft_check_arg(argc, argv) != SUCCESS)
		return (ERROR);
	ft_init_game(&game);
	if (ft_parser(argc, argv, &game.data) != SUCCESS)
		return (ERROR);
	if (ft_game(&game, &game.data) != SUCCESS)
		return (ERROR);
	return (0);
}
