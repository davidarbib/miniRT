/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 19:22:58 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/28 20:33:42 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MLX_XPM_PRIV_H
# define MLX_XPM_PRIV_H

# include "../mlx_int.h"
# include "../mlx_rgb_priv.h"
# include <stdbool.h>
# include <stdlib.h>
# include <string.h>

/*
** For lseek
*/

# include <unistd.h>
# include <sys/types.h>

/*
** For open
*/

# include <stdio.h>

typedef struct		s_xpm_parse_ctx
{
	int				pos;
	char			*line;
	char			**tab;
	char			*data;
	char			*clip_data;
	int				nc;
	int				opp;
	int				cpp;
	int				col;
	int				rgb_col;
	int				col_name;
	int				method;
	int				x;
	int				i;
	int				j;
	mlx_img_list_t	*img;
	t_xpm_col		*colors;
	int				*colors_direct;
	int				width;
	int				height;

	mlx_ptr_t		*xvar;
	void			*info;
	int				info_size;
	char			*(*f)();
}					t_xpm_parse_ctx;

bool				xpm_parse_ctx_finish(t_xpm_parse_ctx *self);
char				*mlx_int_get_line(char *ptr, int *pos, int size);
char				*mlx_int_static_line(char **xpm_data, int *pos, int size);
int					mlx_int_get_col_name(const char *str, int size);
int					mlx_int_get_text_rgb(char *name, char *end);
void				mlx_int_xpm_set_pixel(char *data, int c, int x);

bool				mlx_int_parse_xpm_first_step(t_xpm_parse_ctx *self);
bool				mlx_int_parse_xpm_second_step(t_xpm_parse_ctx *self);
bool				mlx_int_parse_xpm_third_step(t_xpm_parse_ctx *self);
bool				mlx_int_parse_xpm_fourth_step(t_xpm_parse_ctx *self);
bool				mlx_int_parse_xpm_fifth_step(t_xpm_parse_ctx *self);

#endif
