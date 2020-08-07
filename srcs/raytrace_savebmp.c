/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_savebmp.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/07 16:42:35 by darbib            #+#    #+#             */
/*   Updated: 2020/08/07 16:48:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

static void		alter_pixel_savebmp(t_img *img, int color, int x, int y)
{
	unsigned char	*p_img;

	p_img = img->buf + (img->bpp / 8) * x + img->sizeline * y;
	p_img[0] = ((unsigned char *)&color)[0];
	p_img[1] = ((unsigned char *)&color)[1];
	p_img[2] = ((unsigned char *)&color)[2];
}

static void		apply_color_savebmp(t_vect *pix_rgb, t_img *img, int x, int y)
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
	alter_pixel_savebmp(img, color, x, y);
}

void			raytrace_savebmp(t_scene *scene, t_img *img)
{
	int		coord[2];
	t_ray	ray;
	double	half_screen;
	t_vect	pix_rgb;

	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	coord[dx] = 0;
	while (coord[dx] < img->resx)
	{
		coord[dy] = 0;
		while (coord[dy] < img->resy)
		{
			define_ray(&ray, half_screen, coord, scene);
			print_vect(&ray.direction);
			pix_rgb = send_ray(scene, &ray);
			apply_color_savebmp(&pix_rgb, img, coord[dx], coord[dy]);
			coord[dy]++;
		}
		coord[dx]++;
	}
}
