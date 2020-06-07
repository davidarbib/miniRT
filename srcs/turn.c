/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:39:51 by darbib            #+#    #+#             */
/*   Updated: 2020/06/02 17:49:40 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "general.h"
#include "rotation.h"
#include "print.h"

void	turn_cam(double phi, double theta, t_param *param)
{
	t_vect *current_orient;

	print_angle(phi, theta);
	current_orient = &param->scene->active_cam->current_orient;
	rotate_point(phi, theta, current_orient, current_orient); 
	rotate_scene(param->scene, phi * -1, theta * -1);
	print_angle(phi, theta);
}

void	turn_left(void *param)
{
	turn_cam(to_radian(ANGLE_SIZE), 0, (t_param *)param);
}

void	turn_right(void *param)
{
	turn_cam(to_radian(ANGLE_SIZE * -1), 0, (t_param *)param);
}
