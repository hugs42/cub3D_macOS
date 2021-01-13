/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: s72h <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 13:26:29 by s72h              #+#    #+#             */
/*   Updated: 2020/05/25 20:18:53 by s72h             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define PI 3.1415
# define CASE_X 20
# define CASE_Y 15
# define BLOCK_SIZE 64
# define FOC 60
# define ESC 53
# define TOWARD 13
# define LEFT 0
# define RIGHT 2
# define CAM_RIGHT 124
# define CAM_LEFT 123
# define CAM_DOWN 125
# define CAM_UP 126
# define ERROR_INF -1
# define SUCCESS 1
# define ERR 0
# define NORTH 0
# define EAST 1
# define SOUTH 2
# define WEST 3

# define WIN_W 1200
# define WIN_H 800

# include "./../libft/libft.h"
# include "./../get_next_line/get_next_line.h"
# include <mlx.h>
# include <math.h>
# include <time.h>
# include <stdio.h>
# include <fcntl.h>

typedef struct		s_img
{
	void			*img_ptr;
	int				*data;
	char			*addr;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

typedef struct		s_pos
{
	unsigned int	pos_x;
	unsigned int	pos_y;
	unsigned int	dir_x;
	unsigned int	dir_y;
}					t_pos;

typedef struct		s_path
{
	int				x;
	int				y;
	int				nb;
}					t_path;

typedef struct		s_map
{
	char			**map;
	unsigned int	width;
	unsigned int	height;
}					t_map;

typedef struct		s_cam
{
	t_pos			pos;
	t_pos			dir;
	t_pos			dir_x;
	t_pos			plane;
}					t_cam;

typedef struct		s_data
{
	unsigned int	screen_w;
	unsigned int	screen_h;
	int				is_width;
	int				tmp;
	int				north;
	int				south;
	int				west;
	int				east;
	int				sprite;
	char			*path_textures;
	int				ground;
}					t_data;

typedef struct		s_sprite
{
	t_pos			pos_x;
	t_pos			dir;
	t_pos			x_dir;
	t_pos			planel;
}					t_sprite;



typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
//	s_img			*img;
}					t_mlx;

typedef struct		s_game
{
	t_mlx			mlx;
	t_data			data;
	t_cam			cam;
	t_sprite		*sprite;
	
}					t_game;

#endif
