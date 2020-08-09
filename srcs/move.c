/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:23:52 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:01:22 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "update.h"
#include "general.h"

void	move_forward(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = 0;
	translation.z = STEP_SIZE;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.z -= STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	move_backward(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = 0;
	translation.z = -STEP_SIZE;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.z += STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	move_left(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = STEP_SIZE;
	translation.y = 0;
	translation.z = 0;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.x -= STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	move_right(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = -STEP_SIZE;
	translation.y = 0;
	translation.z = 0;
	pm = (t_param *)param;
	pm->scene->active_cam->current_pos.x += STEP_SIZE;
	move_scene(pm->scene, &translation);
	if (!(update_display(pm->scene, pm->mlx_cfg)))
		return ;
}

void	move_scene(t_scene *scene, t_vect *translation)
{
	move_planes(scene->planes, scene->planes_n, translation);
	move_triangles(scene->triangles, scene->triangles_n, translation);
	move_spheres(scene->spheres, scene->spheres_n, translation);
	move_squares(scene->squares, scene->squares_n, translation);
	move_cylinders(scene->cylinders, scene->cylinders_n, translation);
	move_olights(scene->olights, scene->olights_n, translation);
}
