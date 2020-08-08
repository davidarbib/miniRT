/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/06 19:42:14 by darbib            #+#    #+#             */
/*   Updated: 2020/08/08 17:46:23 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "bitmap.h"
#include "scene.h"
#include "libft.h"
#include "print.h"

void			init_img(t_img *img, t_rt *cfg, t_scene *scene)
{
	img->sizex = cfg->resx;
	img->sizey = cfg->resy;
	img->bpp = COLORDEPTH;
	img->sizeline = BYTES_N * img->sizex;
	img->size = img->sizeline * img->sizey;
	if (!(img->buf = (unsigned char *)ft_calloc(img->size,
					sizeof(unsigned char))))
		img_sys_error(scene);
}
