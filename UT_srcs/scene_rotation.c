/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:25:44 by darbib            #+#    #+#             */
/*   Updated: 2020/06/02 17:46:36 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "vector.h"
#include <math.h>
#include <stdio.h>

static void	to_spherical(t_vect *cartesian, t_spheric *spherical)
{
	double rho;

	rho = vect_norm(cartesian);
	spherical->rho = rho; 
	spherical->phi = acos(cartesian->z / rho);  
	spherical->theta = atan2(cartesian->y, cartesian->x);
}

void		to_cartesian(t_spheric *spherical, t_vect *cartesian)
{
	cartesian->x = spherical->rho * sin(spherical->phi) * cos(spherical->theta); 	
	cartesian->y = spherical->rho * sin(spherical->phi) * sin(spherical->theta); 	
	cartesian->z = spherical->rho * cos(spherical->phi); 	
}

void		extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
			double *phi, double *theta)
{
	t_spheric spherical_cam;
	t_spheric spherical_ref;

	to_spherical(cam_orient, &spherical_cam);
	to_spherical(ref_orient, &spherical_ref);
	*phi = spherical_ref.phi - spherical_cam.phi;
	*theta = spherical_ref.theta - spherical_cam.theta;
}

void		rotate_point(double phi, double theta, t_vect *v_in, t_vect *v_out)
{
	t_spheric spherical_in;

	if (!vect_norm(v_in))
	{
		v_out->x = v_in->x; 
		v_out->y = v_in->y; 
		v_out->z = v_in->z; 
	}
	else
	{
		to_spherical(v_in, &spherical_in);
		spherical_in.phi += phi;
		spherical_in.theta += theta;
		to_cartesian(&spherical_in, v_out);
	}
}

int main()
{
	t_vect v;
	t_vect ref;
	double phi = 0;
	double theta = 0;

	v.x = 1;
	v.y = 0;
	v.z = 0;
	ref.x = 0;
	ref.y = 0;
	ref.z = 1;
	extract_scene_rotation(&v, &ref, &phi, &theta);
	print_angle(phi, theta);
	/*
	print_vect(&v);
	rotate_point(to_radian(90), 0, &v, &v);
	print_vect(&v);
	rotate_point(0, to_radian(90), &v, &v);
	print_vect(&v);
	*/
	return (0);
}
