/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:35:45 by hugsbord          #+#    #+#             */
/*   Updated: 2021/03/16 11:34:34 by hugsbord         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define SUCCESS 1
# define ERROR -1
# define PI 3.1415
# define CASE_X 20
# define CASE_Y 15
# define BLOCK_SIZE 64
# define KEY_PRESS 2
# define KEY_RELEASE 3
# define KEY_FORWARD 13
# define KEY_BACK 1
# define KEY_LEFT 0
# define KEY_RIGHT 2
# define KEY_LEFT_ROT 123
# define KEY_RIGHT_ROT 124
# define KEY_EXIT 53
# define FOC 60
# define ESC 53
# define CAM_RIGHT 124
# define CAM_LEFT 123
# define CAM_DOWN 125
# define CAM_UP 126
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
# define WRONG_CONFIG -14
# define CONFIG_DOUBLE -15
# define MISSING_MAP -16
# define PATH_ERR -17
# define XPM_ERR -18
# define RES_ERR -19
# define COLOR_ERR -20
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
	char			*addr;
	int				size_l;
	int				bpp;
	int				endian;
}					t_img;

/*typedef struct		s_path
{
	int				x;
	int				y;
	int				nb;
}					t_path;*/

/*typedef struct		s_map
{
	char			**map_buff;
	int				x;
	int				y;
	unsigned int	width;
	unsigned int	height;
}					t_map;
*/
typedef struct		s_data
{
	unsigned int	screen_w;
	unsigned int	screen_h;
	int				is_width;
	int				tmp;
	int				res;
	int				north;
	int				curr_north;
	int				south;
	int				curr_south;
	int				west;
	int				curr_west;
	int				east;
	int				curr_east;
	int				sprite;
	int				config_done;
	int				config_double;
	int				len;
	int				max_len;
	int				nb_lines;
	int				nb_total_lines;
	int				is_player;
	int				player_dir;
	int				player_pos_x;
	int				player_pos_y;
	int				first_space_x;
	int				x;
	int				y;
	int				z;
	int				fd;
	int				start_map;
	char			**map;
	char			*path;
	char			*path_no;
	char			*path_so;
	char			*path_ea;
	char			*path_we;
	char			*path_sp;
	int				floor;
	unsigned int	floor_col;
	unsigned int	ceiling_col;
	int				ceiling;
	int				is_space;
	int				r;
	int				g;
	int				b;
}					t_data;
/*
typedef struct		s_sprite
{
	t_pos			pos_x;
	t_pos			dir;
	t_pos			x_dir;
	t_pos			planel;
}					t_sprite;
*/
typedef struct		s_player
{
	char			dir;
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plan_x;
	double			plan_y;
	double			move_speed;
	double			rot_speed;
}					t_player;

typedef struct		s_ray
{
	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plan_x;
	double			plan_y;
	double			ray_x;
	double			cam_x;
	double			ray_dir_x;
	double			ray_dir_y;
	int				map_x;
	int				map_y;
	int				line_height;
	double			delta_dist_x;
	double			delta_dist_y;
	double			step_x;
	double			step_y;
	double			side_dist_x;
	double			side_dist_y;
	double			*z_buffer;
	int				hit;
	double			side;
	double			perp_wall_dist;
	int				draw_start;
	int				draw_end;
	int				x;
	int				y;
	double			wall_x;
	double			time;
	double			old_time;
}					t_ray;

typedef struct		s_event
{
	int				forward;
	int				back;
	int				right;
	int				left;
	int				right_rot;
	int				left_rot;
}					t_event;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
}					t_mlx;


typedef struct		s_game
{
	t_img			*img;
	t_mlx			*mlx;
	t_data			data;
	t_player		*player;
	t_ray			ray;
	t_event			*event;
}					t_game;

int		ft_check_arg(int argc, char **argv);
int		ft_check_arg_ext(char *str);
int		ft_check_xpm_ext(char *str);
int		ft_check_char(t_data *data, char *line);
int		ft_check_char_first_line(t_data *data, char *line);
int		ft_get_res(t_data *data, char *line);
int		ft_get_nb(int i, char *line, t_data *data);
int		ft_check_empty_line(t_data *data, char *line);
int		ft_start_map(t_data *data, char *line);
int		ft_check_config_done(t_data *data);
int		ft_check_config_double(t_data *data);
int		ft_check_config(t_data *data);
int		ft_error(int error);
int		ft_is_not_wall(char c);
int		ft_check_map_size(t_data *data);
int		ft_textures(t_data *data, char *line);
int		ft_skip_spaces(char *str, int i);
int		ft_skip_spaces2(t_data *data, int x, int y);
int		ft_press_key(int key, t_game *game);
int		ft_release_key(int key, t_game *game);
int		ft_exit(t_game *game);
int		ft_key_events(t_game *game);
//int		ft_init_rays(t_data *data, t_player *player, t_ray *ray);
int		ft_init_raycasting(t_game *game);
#endif
