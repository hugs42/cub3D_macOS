/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 15:00:50 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/07 12:57:18 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_free_sprites(t_game *game)
{
	if (game->spr->s)
		free(game->spr->s);
	if (game->spr)
		free(game->spr);
}

void	ft_free_textures(t_game *game)
{
	int i;

	i = 0;
	while (i < 5)
	{
		free(game->tex[i].addr);
		i++;
	}
	free(game->tex);
}

void	ft_free_map(t_game *game)
{
	int i;

	i = 0;
	if (game->data.map)
	{
		while (i <= game->data.nb_lines)
		{
			free(game->data.map[i]);
			i++;
		}
		free(game->data.map);
	}
	free(game->data.path_no);
	free(game->data.path_so);
	free(game->data.path_ea);
	free(game->data.path_we);
	free(game->data.path_sp);
}

int		ft_exit(t_game *game)
{
	if (game->player)
		free(game->player);
	if (game->ray)
		free(game->ray);
	if (game->event)
		free(game->event);
	if (game->tex)
		ft_free_textures(game);
	mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win);
	mlx_destroy_image(game->mlx->mlx_ptr, game->mlx->mlx_ptr);
	if (game->mlx)
	{
		free(game->mlx->mlx_ptr);
		free(game->mlx);
	}
	if (game->img)
		free(game->img);
	if (game->data.sprite_nb != 0)
		ft_free_sprites(game);
	if (game->data.map)
		ft_free_map(game);
	exit(0);
	return (0);
}
