/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:28:50 by darbib            #+#    #+#             */
/*   Updated: 2020/08/06 22:02:00 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "math.h"
#include "raytrace.h"
#include "mlx.h"
#include <stdio.h>
#include "bitmap.h"

int			init_graphics(t_mlx *mlx_cfg, t_rt *rt)
{
	int display_resy;
	int display_resx;

	if (!(mlx_cfg->mlx_ptr = mlx_init()))
		return (0);
	mlx_get_screen_size(mlx_cfg->mlx_ptr, &display_resx, &display_resy);
	mlx_cfg->sizex = ft_min(rt->resx, display_resx);
	mlx_cfg->sizey = ft_min(rt->resy, display_resy);
	if (!(mlx_cfg->win_ptr = mlx_new_window(mlx_cfg->mlx_ptr, mlx_cfg->sizex,
		mlx_cfg->sizey, TITLE)))
		return (0);
	if (!(create_img(mlx_cfg)))
		return (0);
	return (1);
}

int			create_img(t_mlx *mlx_cfg)
{
	if (!(mlx_cfg->img_ptr = mlx_new_image(mlx_cfg->mlx_ptr, mlx_cfg->sizex,
		mlx_cfg->sizey)))
		return (0);
	if (!(mlx_cfg->img_data = mlx_get_data_addr(mlx_cfg->img_ptr,
		&mlx_cfg->bits_per_pixel, &mlx_cfg->size_line, &mlx_cfg->endian)))
		return (0);
	return (1);
}

int			refresh_img(t_mlx *mlx_cfg)
{
	mlx_destroy_image(mlx_cfg->mlx_ptr, mlx_cfg->img_ptr);
	if (!(create_img(mlx_cfg)))
		return (0);
	return (1);
}

void		apply_color(t_vect *pix_rgb, t_img *img, int x, int y)
{
	int				color;
	unsigned char	rgb[3];

	rgb[r] = round(pix_rgb->x * 255.);
	rgb[g] = round(pix_rgb->y * 255.);
	rgb[b] = round(pix_rgb->z * 255.);
	color = 0;
	color += (int)rgb[b];
	color += (int)rgb[g] * 256;
	color += (int)rgb[r] * 256 * 256;
	alter_pixel(img, color, x, y);
}

void		alter_pixel(t_img *img, int color, int x, int y)
{
	unsigned char	*p_img;

	p_img = img->buf + (img->bpp / 8) * x + img->sizeline * y;
	p_img[0] = ((unsigned char *)&color)[0];
	p_img[1] = ((unsigned char *)&color)[1];
	p_img[2] = ((unsigned char *)&color)[2];
}
