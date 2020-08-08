/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:42:14 by darbib            #+#    #+#             */
/*   Updated: 2020/08/07 18:45:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "bitmap.h"
#include "scene.h"
#include "libft.h"
#include "print.h"

int				client_endian(void)
{
	unsigned int nb;

	nb = 0x1;
	if (((unsigned char *)&nb)[0] == 0x1)
		return (0);
	return (1);
}

void			adapt_endian(unsigned char *color, unsigned char *color_ret)
{
	(color_ret)[0] = (color)[3];
	(color_ret)[1] = (color)[2];
	(color_ret)[2] = (color)[1];
	(color_ret)[3] = (color)[0];
}

void			init_img(t_img *img, t_rt *cfg, t_scene *scene)
{
	img->sizex = scene->resx;
	img->sizey = scene->resy;
	img->bpp = COLORDEPTH;
	img->sizeline = BYTES_N * img->sizex;
	img->size = img->sizeline * img->sizey;
	if (!(img->buf = (unsigned char *)ft_calloc(img->size,
					sizeof(unsigned char))))
		img_sys_error(scene);
}

static void		transfer_color(t_img *img, t_mlx *mlx, int *pixel, int endian)
{
	unsigned char	color[4];
	unsigned char	color_ret[4];

	if (pixel[i] == mlx->sizex / 2 && pixel[j] == mlx->sizey / 2)
		printf("cc\n");
	ft_bzero(color, 4);
	ft_bzero(color_ret, 4);
	ft_memmove(color,
			(img->buf + (pixel[i] * (img->bpp / 8)) +
			 (pixel[j] * img->sizeline)),
			BYTES_N);
	if (mlx->endian != endian)
	{
		adapt_endian(color, color_ret);
		ft_memmove(color_ret,
			(mlx->img_data + (pixel[i] * (mlx->bits_per_pixel / 8))
			+ (pixel[j] * mlx->size_line)), 4);
	}
	else
	{
		ft_memmove(color,
			(mlx->img_data + (pixel[i] * (mlx->bits_per_pixel / 8))
			+ (pixel[j] * mlx->size_line)), 4);
	}
}

void			img_to_mlx(t_img *img, t_mlx *mlx)
{
	int				pixel[2];
	int				endian;

	endian = client_endian();
	pixel[j] = 0;
	while (pixel[j] < mlx->sizey)
	{
		pixel[i] = 0;
		while (pixel[i] < mlx->sizex)
		{
			transfer_color(img, mlx, pixel, endian);
			pixel[i]++;
		}
		pixel[j]++;
	}
}
