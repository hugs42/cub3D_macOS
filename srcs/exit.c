/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/04 15:00:50 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/07 09:47:18 by hugsbord         ###   ########.fr       */
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
		while (i < 2)//game->data.sprite_nb)
		{
//			free(game->spr[i].s);
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
//	free(game->tex[0].addr);
//	mlx_destroy_image(game->mlx->mlx_ptr, game->tex[0].addr);
	while (i < 5)
	{
//		printf("OK");
//		mlx_destroy_image(game->mlx->mlx_ptr, game->tex[i].addr);
		free(game->tex[i].addr);
//		free(game->tex);
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
	if (game->mlx)
	{
		if (game->img->img_ptr)
			mlx_destroy_image(game->mlx->mlx_ptr, game->img->img_ptr);
		if (game->mlx->win)
			mlx_destroy_window(game->mlx->mlx_ptr, game->mlx->win);
		free(game->mlx->mlx_ptr);
		free(game->mlx);
	}
	if (game->img)
		free(game->img);
	if (game->data.sprite_nb != 0)
		ft_free_sprites(game);
	if (game->data.map)
		ft_free_map(game);
	while (1);
	exit(0);
	return (0);
}

