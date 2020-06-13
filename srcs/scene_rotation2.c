/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/21 18:08:31 by darbib            #+#    #+#             */
/*   Updated: 2020/06/13 20:44:28 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rotation.h"
#include "print.h"
#include "actions.h"

void	assign_turn_matrices(double *left, double *right)
{
	double costheta; 
	double sintheta; 
	
	costheta = cos(ANGLE_SIZE);
	sintheta = sin(ANGLE_SIZE);
	left[0] = costheta;
	left[1] = 0;
	left[2] = -sintheta;
	left[3] = 0;
	left[4] = 1;
	left[5] = 0;
	left[6] = sintheta;
	left[7] = 0;
	left[8] = costheta;
	right[0] = costheta;
	right[1] = 0;
	right[2] = sintheta;
	right[3] = 0;
	right[4] = 1;
	right[5] = 0;
	right[6] = -sintheta;
	right[7] = 0;
	right[8] = costheta;
}

void	assign_turn_matrices2(double *up, double *down)
{
	double cosphi; 
	double sinphi; 
	
	cosphi = cos(ANGLE_SIZE);
	sinphi = sin(ANGLE_SIZE);
	up[0] = 1;
	up[1] = 0;
	up[2] = 0;
	up[3] = 0;
	up[4] = cosphi;
	up[5] = sinphi;
	up[6] = 0;
	up[7] = -sinphi;
	up[8] = cosphi;
	down[0] = 1;
	down[1] = 0;
	down[2] = 0;
	down[3] = 0;
	down[4] = cosphi;
	down[5] = -sinphi;
	down[6] = 0;
	down[7] = sinphi;
	down[8] = cosphi;
}

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
	t_spheric pt_sph;

	while (n)
	{
		triangle = triangles + n - 1;
		to_spherical(&triangle->current_pt1, &pt_sph);
		printf("/*----triangle spheric before---*/\n");
		print_vect_sph(&pt_sph);
		rotate_point(phi, theta, &triangle->current_pt1, 
				&triangle->current_pt1);
		printf("/*----triangle spheric after---*/\n");
		to_spherical(&triangle->current_pt1, &pt_sph);
		print_vect_sph(&pt_sph);
		printf("/*-----------------------------*/\n");
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
