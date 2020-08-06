/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:39:51 by darbib            #+#    #+#             */
/*   Updated: 2020/08/06 21:30:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "update.h"
#include "general.h"
#include "rotation.h"
#include "matrix.h"

void	turn_cam(t_param *param, double *matrix)
{
	t_vect *current_orient;

	current_orient = &param->scene->active_cam->current_orient;
	normalize(current_orient, current_orient);
	rotate_point(matrix, current_orient, current_orient);
}

void	turn_left(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->left_matrix);
	rotate_scene(pm->scene, pm->scene->right_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg, pm->img)))
		return ;
}

void	turn_right(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->right_matrix);
	rotate_scene(pm->scene, pm->scene->left_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg, pm->img)))
		return ;
}

void	turn_up(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->up_matrix);
	rotate_scene(pm->scene, pm->scene->down_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg, pm->img)))
		return ;
}

void	turn_down(void *param)
{
	t_param	*pm;

	pm = (t_param *)param;
	turn_cam(pm, pm->scene->down_matrix);
	rotate_scene(pm->scene, pm->scene->up_matrix);
	if (!(update_display(pm->scene, pm->mlx_cfg, pm->img)))
		return ;
}
