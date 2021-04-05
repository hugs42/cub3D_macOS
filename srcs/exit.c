/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 15:00:50 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/05 17:33:22 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./../includes/cub3d.h"

void	ft_free_sprites(t_game *game)
{
	int i;

	i = 0;
	if (game->spr->s)
	{
		free(game->spr->s);
		while (i < game->data.sprite_nb)
		{
//			free(game->spr->s);
			i++;
		}
	}
	if (game->spr->order)
		free(game->spr->order);
	if (game->spr->distance)
		free(game->spr->distance);
	if (game->spr)
		free(game->spr);
}

void	ft_free_textures(t_game *game)
{
	int i;

	i = 0;
	while (i <= 20)
	{
		free(game->tex->addr);
		free(game->tex);
		i++;
	}
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
	}
	free(game->data.path);
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
	if (game->mlx)
		free(game->mlx);
	if (game->img)
		free(game->img);
	if (game->data.sprite_nb != 0)
		ft_free_sprites(game);
	ft_free_map(game);
	exit(0);
	return (0);
}

