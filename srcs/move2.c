/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 18:22:36 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 18:55:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "update.h"
#include "general.h"
#include "print.h"
#include <stdio.h>

void	move_up(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = STEP_SIZE;
	translation.z = 0;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.y -= STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	move_down(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = -STEP_SIZE;
	translation.z = 0;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.y += STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}
