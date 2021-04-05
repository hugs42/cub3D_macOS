/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hugsbord <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/14 17:35:45 by hugsbord          #+#    #+#             */
/*   Updated: 2021/04/05 14:06:39 by hugsbord         ###   ########.fr       */
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
# define KEY_FORWARD 13//119 //13
# define KEY_BACK 1//115//1
# define KEY_LEFT 0//97//0
# define KEY_RIGHT 2
# define KEY_LEFT_ROT 123//65361//123
# define KEY_RIGHT_ROT 124//65363//124
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
# define TEX_ERR -21
# define BMP_ERR -22
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
	int				*addr;
	int				size_l;
	int				bpp;
	int				endian;
	int				width;
	int				height;
}					t_img;

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
	int				r;
	int				g;
	int				b;
	unsigned int	sprite_nb;
}					t_data;

typedef struct		s_s
{
	double			x;
	double			y;
}					t_s;

typedef struct		s_spr
{
	t_s					*s;
	double				sprite_x;
	double				sprite_y;
	double				invdet;
	double				transform_x;
	double				transform_y;
	int					sprite_screen_x;
	int					sprite_h;
	int					sprite_w;
	int					draw_start_x;
	int					draw_start_y;
	int					draw_end_x;
	int					draw_end_y;
	int					tex_x;
	int					tex_y;
	double				*distance;
	int					*order;
}					t_spr;

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
	int				hit;
	double			side;
	double			perp_wall_dist;
	int				draw_start;
	int				draw_end;
	double			wall_x;
}					t_ray;

typedef struct		s_event
{
	int				forward;
	int				back;
	int				right;
	int				left;
	int				right_rot;
	int				left_rot;
	int				exit;
}					t_event;

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win;
}					t_mlx;

typedef struct		s_tex
{
	int				width;
	int				height;
	int				*addr;
	int				tex_x;
	int				tex_y;
	int				tex_num;
	double			tex_pos;
	double			step;
}					t_tex;

typedef struct		s_game
{
	t_img			*img;
	t_mlx			*mlx;
	t_data			data;
	t_player		*player;
	t_ray			*ray;
	t_event			*event;
	t_tex			*tex;
	t_spr			*spr;
	double			*z_buffer;
	int				save;
}					t_game;

int		ft_init_game(t_game *game);
int		ft_init_data_1(t_data *data);
int		ft_init_data_2(t_data *data);
int		ft_init_player(t_game *game);
int		ft_init_img(t_game *game);
int		ft_init_event(t_game *game);
int		ft_init_mlx(t_game *game);
int		ft_init_sprites(t_spr *spr);
int		ft_parser(int argc, char **argv, t_data *data);
int		ft_parse_line(t_data *data, char *line);
int		ft_parse_info_map(t_data *data, char *line);
int		ft_parse_config(t_data *data, char *line, int i);
int		ft_parse_map(t_data *data, char *line);
int		ft_check_arg(int argc, char **argv);
int		ft_check_arg_ext(char *str);
int		ft_check_tex_ext(char *str);
int		ft_check_char(t_data *data, char *line);
int		ft_check_char_first_line(t_data *data, char *line);
int		ft_check_first_space(t_data *data);
int		ft_is_player(char c);
void	ft_get_player(t_data *data, int x, int y);
int		ft_get_res(t_data *data, char *line);
int		ft_get_nb(int i, char *line, t_data *data);
int		ft_check_empty_line(t_data *data, char *line);
int		ft_start_map(t_data *data, char *line);
int		ft_get_map(t_data *data, char *line);
int		ft_copy_map(t_data *data, char *line);
int		ft_check_wall(t_data *data);
int		ft_check_player(t_data *data);
void	ft_replace_spaces(t_data *data);
int		ft_check_map_size(t_data *data);
int		ft_check_border(t_data *data);
int		ft_check_neighborhood(t_data *data, int x, int y);
int		ft_check_neighborhood_2(t_data *data, int x, int y);
int		ft_check_config_done(t_data *data);
int		ft_check_config_double(t_data *data);
int		ft_check_config(t_data *data);
int		ft_error(int error);
int		ft_is_not_wall(char c);
int		ft_get_path(t_data *data, char *line, int i);
int		ft_check_map_size(t_data *data);
int		ft_tex_path(t_data *data, char *line, int i);
int		ft_skip_spaces(char *str, int i);
int		ft_skip_spaces2(t_data *data, int x, int y);
int		ft_press_key(int key, t_game *game);
int		ft_release_key(int key, t_game *game);
int		ft_exit(t_game *game);
int		ft_key_events(t_game *game);
void	ft_rot_right(t_player *player);
void	ft_rot_left(t_player *player);
void	ft_move_forward(t_data *data, t_player *player);
void	ft_move_backward(t_data *data, t_player *player);
void	ft_move_right(t_data *data, t_player *player);
void	ft_move_left(t_data *data, t_player *player);
int		ft_init_raycasting(t_game *game);
int		ft_raycasting(t_game *game);
int		ft_draw_start_end(t_game *game, t_data *data, t_ray *ray);
int		ft_dda(t_ray *ray, t_data *data);
int		ft_check_char_color(char *line, int i, int len);
int		ft_get_nb_color(t_data *data, char *line, int i);
int		ft_get_color(t_data *data, char *line, int i);
void	ft_pos_north_south(t_player *player, t_data *data);
void	ft_pos_west_east(t_player *player, t_data *data);
int		ft_setup_player(t_player *player, t_data *data);
int		ft_setup_textures(t_game *game, t_data *data, t_mlx *mlx);
int		ft_load_textures(char *path, t_mlx *mlx, t_tex *tex);
int		ft_select_textures(t_game *game);
int		ft_render_walls(int x, t_game *game, t_data *data, t_tex *tex);
void	ft_render_colors(int x, t_game *game, t_data *data, t_mlx *mlx);
int		ft_sprite(t_game *game, t_spr *spr, t_s *s);
int		ft_setup_sprites(t_game *game, t_data *data);
int		ft_draw_sprite(t_game *game, t_spr *spr);
int		ft_bmp(t_game *game);
#endif
