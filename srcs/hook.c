/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 18:08:55 by darbib            #+#    #+#             */
/*   Updated: 2020/05/09 16:43:53 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "math.h"
#include "keys_linux.h"
#include "print.h"

int		loop_hook(void *param)
{
	t_scene *scene;
	t_mlx	*cfg;

	scene = ((t_param *)param)->scene;
	cfg = ((t_param *)param)->mlx_cfg;
	//	scene->phi += M_PI/10000;
	refresh_img(cfg, scene->resx, scene->resy);
	adapt_scene(scene);
	raytrace(scene, cfg);
	if (!(mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr,
		cfg->img_ptr, 0, 0)))
		return (0);
	return (1);
}
