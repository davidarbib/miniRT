/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:08:31 by darbib            #+#    #+#             */
/*   Updated: 2020/06/02 12:44:13 by darbib           ###   ########.fr       */
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
		rotate_point(phi, theta, &plane->current_pos, &plane->current_pos);
		rotate_point(phi, theta, &plane->current_orient, &plane->current_orient);
		n--;
	}
}

void	rotate_triangles(t_trig *triangles, int n, double phi, double theta)
{
	t_trig *triangle;

	while (n)
	{
		triangle = triangles + n - 1;
		rotate_point(phi, theta, &triangle->current_pt1, 
				&triangle->current_pt1);
		rotate_point(phi, theta, &triangle->current_pt2, 
				&triangle->current_pt2);
		rotate_point(phi, theta, &triangle->current_pt3, 
				&triangle->current_pt3);
		n--;
	}
}

void		rotate_scene(t_scene *scene, double phi, double theta)
{	
	rotate_planes(scene->planes, scene->planes_n, phi, theta);
	rotate_triangles(scene->triangles, scene->triangles_n, phi, theta);
	compute_triangles_edges(scene->triangles, scene->triangles_n);
}
