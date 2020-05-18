/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 16:37:26 by darbib            #+#    #+#             */
/*   Updated: 2020/05/17 18:36:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_H
# define GRAPHIC_H

typedef struct		s_mlx
{
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
}					t_mlx;

int				init_graphics(t_mlx *mlx_cfg, int resx, int resy);
void			init_cfg(t_rt *cfg);
int				create_img(t_mlx *mlx_cfg, int resx, int resy);
int				refresh_img(t_mlx *mlx_cfg, int resx, int resy);
void			alter_pixel(t_mlx *cfg, int color, int x, int y);
void			apply_color(unsigned char *rgb, t_mlx *mlx_cfg, int x, int y);

#endif
