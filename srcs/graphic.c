/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/14 16:28:50 by darbib            #+#    #+#             */
/*   Updated: 2020/02/14 16:36:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"

int			init_graphics(t_mlx *mlx_cfg, t_rt *rt_cfg)
{
	if (!(mlx_cfg->mlx_ptr = mlx_init()))
		return (0);
	if (!(mlx_cfg->win_ptr = mlx_new_window(mlx_cfg->mlx_ptr, rt_cfg->resx,
		rt_cfg->resy, TITLE)))
		return (0);
	if (!(create_img(mlx_cfg, rt_cfg)))
		return (0);
	return (1);
}

int			create_img(t_mlx *mlx_cfg, t_rt *rt_cfg)
{
	if (!(mlx_cfg->img_ptr = mlx_new_image(mlx_cfg->mlx_ptr, rt_cfg->resx,
		rt_cfg->resy)))
		return (0);
	if (!(mlx_cfg->img_data = mlx_get_data_addr(mlx_cfg->img_ptr,
		&mlx_cfg->bits_per_pixel, &mlx_cfg->size_line, &mlx_cfg->endian)))
		return (0);
	if (!(mlx_put_image_to_window(mlx_cfg->mlx_ptr, mlx_cfg->win_ptr,
		mlx_cfg->img_ptr, 0, 0)))
		return (0);
	return (1);
}

int			refresh_img(t_mlx *mlx_cfg, t_rt *rt_cfg)
{
	if (!(mlx_destroy_image(mlx_cfg->mlx_ptr, mlx_cfg->img_ptr)))
		return (0);
	if (!(create_img(mlx_cfg, rt_cfg)))
		return (0);
	return (1);
}

void		alter_pixel(t_mlx *cfg, int color, int x, int y)
{
	unsigned char	*p_img;
	unsigned int	mlx_color;
	
	p_img = (unsigned char *)cfg->img_data
			+ (cfg->bits_per_pixel / 8) * x
			+ cfg->size_line * y;
	mlx_color = mlx_get_color_value(cfg->mlx_ptr, color);
	if (cfg->endian != client_endian())
		mlx_color = adapt_endian(mlx_color);
	p_img[0] = ((unsigned char *)&mlx_color)[0];
	p_img[1] = ((unsigned char *)&mlx_color)[1];
	p_img[2] = ((unsigned char *)&mlx_color)[2];
	p_img[3] = ((unsigned char *)&mlx_color)[3];
}
