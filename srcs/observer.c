/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:03:41 by darbib            #+#    #+#             */
/*   Updated: 2020/07/31 15:54:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "actions.h"
#include "print.h"

void	cam_switch(void *param)
{
	t_scene				*scene;
	t_mlx				*cfg;
	static unsigned int current_idx = 0;

	scene = ((t_param *)param)->scene;
	cfg = ((t_param *)param)->mlx_cfg;
	current_idx++;
	current_idx %= scene->cams_n;
	scene->active_cam = scene->cams + current_idx;
	place_objs(scene);
	if (!(update_display(scene, cfg)))
		return ;
}

void	res_switch(void *param)
{
	t_scene				*scene;
	t_mlx				*cfg;

	scene = ((t_param *)param)->scene;
	cfg = ((t_param *)param)->mlx_cfg;
	if (scene->lowres)
	{
		scene->lowres = 0;
		if (!(update_display(scene, cfg)))
			return ;
	}
	else
	{
		scene->lowres = 1;	
		refresh_img(cfg);
		raytrace_lowres(scene, cfg);
		if (!(mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr,
						cfg->img_ptr, 0, 0)))
			return ;
	}
}
