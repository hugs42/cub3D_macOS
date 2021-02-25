/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:35:45 by hugsbord          #+#    #+#             */
/*   Updated: 2021/02/25 13:10:11 by hugsbord         ###   ########.fr       */
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
# define ERROR -1
# define EMPTY_LINE -2
# define WRONG_CHAR -3
# define MISSING_WALL -4
# define TOO_FEW_ARG -5
# define TOO_MUCH_ARG -6
# define BAD_EXTENSION -7
# define MALLOC_ERR -8
# define SMALL_MAP -9
# define ERR_PLAYER -10
# define ERR_ARG_SAVE -11
# define DIRECTORY -12
# define WRONG_FILE -13
# define SUCCESS 1
# define ERR 0

# define NORTH 33
# define EAST 34
# define SOUTH 35
# define WEST 36
# define BUFFER_SIZE 4096

# define WIN_W 1200
# define WIN_H 800

# include "./../libft/libft.h"
# include "./get_next_line.h"
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
	char			**map_buff;
	int				x;
	int				y;
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
	int				res;
	int				north;
	int				south;
	int				west;
	int				east;
	int				sprite;
	int				ceiling;
	int				config_done;
	int				len;
	int				max_len;
	int				nb_lines;
	int				nb_total_lines;
	int				is_player;
	int				player_dir;
	int				player_pos_x;
	int				player_pos_y;
	int				first_space_x;
	int				first_space_y;
	int				x;
	int				y;
	int				start_map;
	char			**map;
//	t_map			map;
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

int		ft_check_arg(int argc, char **argv);
int		ft_check_ext(char *str);
int		ft_check_char(t_data *data, char *line);
int		ft_check_char_first_line(t_data *data, char *line);
int		ft_get_res(t_data *data, char *line);
int		ft_get_nb(int i, char *line, t_data *data);
int		ft_check_empty_line(t_data *data, char *line);
int		ft_start_map(t_data *data, char *line);
int		ft_check_config(t_data *data);
int		ft_error(int error);
int		ft_is_not_wall(char c);
int		ft_check_map_size(t_data *data);
#endif
