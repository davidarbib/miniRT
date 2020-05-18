/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation_quaternion.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:21:04 by darbib            #+#    #+#             */
/*   Updated: 2020/05/13 23:29:22 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include "quaternion.h"
#include <stdio.h>

static void set_local_quaternion(double semi_angle, t_vect *axis,
		double *quater_z)
{
	double semi_angle_sinus;

	semi_angle_sinus = sin(semi_angle);
	quater_z[A] = cos(semi_angle);
	quater_z[B] = semi_angle_sinus * axis->x;
	quater_z[C] = semi_angle_sinus * axis->y;
	quater_z[D] = semi_angle_sinus * axis->z;
}

static void	xz_projection(t_vect *cam_orient, t_vect *proj_xz, double *quater_z)
{
	t_vect	axis_orient;    
	t_vect  proj_z;
	t_vect  proj_x;
	double	angle;

	printf("cam_orient: (%lf, %lf, %lf)\n", cam_orient->x, cam_orient->y, cam_orient->z);
	axis_orient.x = 1.;
	axis_orient.y = 0.;
	axis_orient.z = 0.;
	ortho_projection(cam_orient, &axis_orient, &proj_x);	
	axis_orient.x = 0.;
	axis_orient.y = 0.;
	axis_orient.z = 1.;
	ortho_projection(cam_orient, &axis_orient, &proj_z);  
	printf("proj_x: (%lf, %lf, %lf)\n", proj_x.x, proj_x.y, proj_x.z);
	printf("proj_z: (%lf, %lf, %lf)\n", proj_z.x, proj_z.y, proj_z.z);
	add_vect(&proj_x, &proj_z, proj_xz);
	printf("proj_xz: (%lf, %lf, %lf)\n", proj_xz->x, proj_xz->y, proj_xz->z);
	normalize(proj_xz, proj_xz); 
	angle = acos(dot(cam_orient, proj_xz));
	printf("angle y-xz : %lf\n", angle);
	set_local_quaternion(angle / 2., &axis_orient, quater_z); 
}

static void	ref_projection(t_vect *ref_orient, t_vect *proj_xz,
		double *quater_y)
{
	t_vect	y_axis;
	t_vect	proj_ref;
	double angle;

	ortho_projection(proj_xz, ref_orient, &proj_ref);
	normalize(&proj_ref, &proj_ref); 
	y_axis.x = 0.;	
	y_axis.y = 1.;	
	y_axis.z = 0.;
	printf("proj_ref: (%lf, %lf, %lf)\n", proj_ref.x, proj_ref.y, proj_ref.z);
	angle = acos(dot(proj_xz, &proj_ref));
	printf("angle z-x : %lf\n", angle);
	set_local_quaternion(angle / 2., &y_axis, quater_y);
}

void		to_spherical(t_vect *cartesian, t_vect *spherical)
{
	double rho;

	rho = vect_norm(cartesian);
	spherical->x = rho; 
	spherical->y = acos(cartesian->y / rho);  
	spherical->z = atan(cartesian->x / cartesian->z;
}

void		to_cartesian(t_vect *spherical, t_vect *cartesian)
{
	cartesian->x = spherical->x * sin(spherical->y) * cos(spherical->z); 	
	cartesian->y = spherical->x * sin(spherical->y) * sin(spherical->z); 	
	cartesian->z = spherical->x * cos(spherical->y); 	
}

void		set_global_quaternions(double *global_quater,
		double *global_quater_conjugate, t_vect *cam_orient, t_vect *ref_orient)
{
	double	quater_z[4];
	double	quater_y[4];
	t_vect	proj_xz;

	xz_projection(cam_orient, &proj_xz, quater_z);
	ref_projection(ref_orient, &proj_xz, quater_y);
	mult_quater(quater_y, quater_z, global_quater);	
	conjugate_quater(global_quater, global_quater_conjugate);
}

/*
void	rotate_point(t_vect *point, double *rot_quater,
		double *conjugate_rot_quater)
{
	double	quater1[4];
	double	quater2[4];

	//printf("point = (%f, %f, %f)\n", point->x, point->y, point->z);
	to_quater(point, quater1);
	//printf("quater1 = (%f, %f, %f, %f)\n", quater1[A], quater1[B], quater1[C], quater1[D]);
	mult_quater(rot_quater, quater1, quater2);
	mult_quater(quater2, conjugate_rot_quater, quater1);
	//printf("quater1 = (%f, %f, %f, %f)\n", quater1[A], quater1[B], quater1[C], quater1[D]);
	to_point(quater1, point);
	//printf("point = (%f, %f, %f)\n", point->x, point->y, point->z);
}
*/


