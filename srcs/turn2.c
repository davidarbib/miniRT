/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 15:51:40 by darbib            #+#    #+#             */
/*   Updated: 2020/07/31 16:20:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "update.h"
#include "general.h"
#include "rotation.h"
#include "matrix.h"

void	roll(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->roll_matrix);
	rotate_scene(pm->scene, pm->scene->invroll_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	inv_roll(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->invroll_matrix);
	rotate_scene(pm->scene, pm->scene->roll_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}
