/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: warchang <warchang@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/23 16:29:57 by warchang          #+#    #+#             */
/*   Updated: 2021/04/24 15:50:08 by warchang         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx_mms/mlx.h"
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <math.h>
# include <fcntl.h>
# include <stdio.h>
# include "../libft/libft.h"
# define SCL 1
# define SPD 0.1f
# define ESC 64
# define FORW 32
# define BACKW 16
# define MV_L 8
# define MV_R 4
# define RT_L 2
# define RT_R 1
# define D 0.1f
# define NT 1 << 26
# define ST 1 << 27
# define WS 1 << 28
# define ES 1 << 29
# define MAX_RE 5120
# define MIN_RE 1
# define WR_ARG_MSG "Wrong argument"

typedef struct		s_plr
{
	double			pos_x;
	double			pos_y;
	double			ang_h;
	double			angle_v;
}					t_plr;

typedef struct		s_sprt
{
	double			pos_x;
	double			pos_y;
	double			dist;
	double			angle;
}					t_sprt;

typedef struct		s_txt
{
	void			*img;
	void			*adr;
	int				line_l;
	int				bpp;
	int				en;
	int				w_tex;
	int				h_tex;
}					t_txt;

typedef struct		s_win
{
	unsigned int	move_mask;
	void			*mlx;
	void			*win;
	void			*img;
	void			*addr;
	int				line_l;
	int				bpp;
	int				en;
	t_txt			*north;
	t_txt			*south;
	t_txt			*west;
	t_txt			*east;
	t_txt			*sprite;
}					t_win;

typedef	struct		s_parameters
{
	int				res_v;
	int				res_h;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*sprite;
	int				fl_clr;
	int				ceil_clr;
	int				i;
	char			**map;
	t_sprt			**sprites;
	t_plr			plr;
	double			*dists;
}					t_parameters;

typedef struct		s_allrend
{
	t_parameters	*prms;
	t_win			*win;
}					t_allrend;

int					is_clr(int color);
int					ft_clr(const char *line, int i, int *color, int *error);
int					ft_clrs(const char *line, int color, int *error);
char				*gnl_join(char *str1, char *str2);
int					prs_mp(int fd, t_parameters *params, char **line);
char				**split_mp(char const *str, char c);
int					mp_chk(t_parameters *params);
double				ft_ang(char c);
int					ft_plr(t_parameters *params);
int					sprt_cnt(char **mp);
int					ft_sprites(t_parameters *params);
int					mp_ln(char *str);
t_parameters		*prs_prms(int fd, t_parameters *params, char **line,
					int *error);
int					chk_prms(t_parameters *params, int *error);
int					err_prms(int *error);
int					prms_fre(t_parameters *params, int *error);
void				main_free(t_parameters *params);
int					ft_parse(char *f_name, t_parameters *params);
int					key_pr(int key, t_allrend *all);
int					key_rel(int key, t_allrend *all);
int					rndr_next_fr(t_allrend *all);
int					my_exit(t_allrend *all);
int					get_height(t_allrend *all, int i);
int					is_wall(t_allrend *all, t_plr p, double angle, char h);
int					move(t_allrend *all, double angle);
void				ft_scrnshot(t_allrend *all);
int					freewin(t_allrend *all);
void				mypxl_put(t_win *win, int x, int y, unsigned int color);
void				line_txt(t_allrend *all, int xpos, int h);
void				dr_fc(t_allrend *all);
void				dr_wal(t_allrend *all);
int					spr_prms(t_sprt *spr, t_plr plr);
void				dr_sprt(t_allrend *all);
int					mk_img(t_allrend *all);
int					skip_n(const char *s, int i);
int					ft_spaceskip(const char *line, int i);
int					init_prms(t_parameters *params);
void				ft_rndr(t_parameters *params, int argc);
int					inpt_chk(int argc, char **argv);
void				mp_free(char **map);
int					ft_rezol(t_parameters *params, const char *ln, int *error);
t_sprt				*get_sprite(int j, int i);

#endif
