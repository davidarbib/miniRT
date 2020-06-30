/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   observer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/21 18:03:41 by darbib            #+#    #+#             */
/*   Updated: 2020/06/22 19:30:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "actions.h"

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