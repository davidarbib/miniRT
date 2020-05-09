/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:23:52 by darbib            #+#    #+#             */
/*   Updated: 2020/05/09 18:49:54 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h" 
#include "general.h"
#include "print.h"
#include <stdio.h>

void	move_forward(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = 0;
	translation.z = STEP_SIZE * -1;
	pm = (t_param *)param;
	pm->scene->cam_pos->z += STEP_SIZE; 
	move_scene(pm->scene, &translation);
}

void	move_backward(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = 0;
	translation.y = 0;
	translation.z = STEP_SIZE;
	pm = (t_param *)param;
	pm->scene->cam_pos->z -= STEP_SIZE; 
	move_scene(pm->scene, &translation);
}

void	move_left(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = STEP_SIZE * -1;
	translation.y = 0;
	translation.z = 0;
	printf("a gauche\n");
	pm = (t_param *)param;
	pm->scene->cam_pos->x += STEP_SIZE; 
	move_scene(pm->scene, &translation);
}

void	move_right(void *param)
{
	t_param	*pm;
	t_vect	translation;

	translation.x = STEP_SIZE;
	translation.y = 0;
	translation.z = 0;
	printf("a droite\n");
	pm = (t_param *)param;
	pm->scene->cam_pos->x -= STEP_SIZE; 
	move_scene(pm->scene, &translation);
}

void	move_scene(t_scene *scene, t_vect *translation)
{
	move_aabb(scene->aabb1, translation);
	//move_aabb(scene->aabb2, &translation);
	//move_aabb(scene->aabb3, &translation);
}
