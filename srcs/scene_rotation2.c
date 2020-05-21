/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   obj_rotation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:08:31 by darbib            #+#    #+#             */
/*   Updated: 2020/05/21 21:26:54 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "print.h"

void	rotate_planes(t_plane *planes, int n, double phi, double theta)
{
	t_plane *plane;

	while (n)
	{
		plane = planes + n - 1;
		rotate_point(phi, theta, plane->current_pos, plane->current_pos);
		rotate_point(phi, theta, plane->current_orient, plane->current_orient);
		n--;
	}
}

void		rotate_scene(t_scene *scene, double phi, double theta)
{	
	rotate_planes(scene->planes, scene->planes_n, phi, theta);
}
