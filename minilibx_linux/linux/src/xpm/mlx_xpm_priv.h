/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm_priv.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 16:31:54 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/02/18 14:59:52 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef		MLX_XPM_PRIV_H
# define	MLX_XPM_PRIV_H

# include "../mlx_int.h"

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
	t_img			*img;
	t_xpm_col		*colors;
	int				*colors_direct;
	int				width;
	int				height;
	XImage			*clip_img;
	XGCValues		xgcv;
	Pixmap			clip_pix;

	t_xvar			*xvar;
	void			*info;
	int				info_size;
	char			*(*f)();
}					t_xpm_parse_ctx;

typedef struct		s_xpm_set_pixel_data
{
	t_img			*img;
	char			*data;
	int				opp;
	int				col;
	int				x;
}					t_xpm_set_pixel_data;

bool				xpm_parse_ctx_finish(t_xpm_parse_ctx *self);
int					mlx_int_xpm_set_pixel(t_xpm_set_pixel_data *data);
int					mlx_int_get_col_name(const char *str, int size);
int					mlx_int_get_text_rgb(char *name, char *end);

#endif
