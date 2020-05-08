/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:21:04 by darbib            #+#    #+#             */
/*   Updated: 2020/05/08 20:10:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "spheric.h"
#include "print.h"
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

void	to_cartesian(t_spheric *spherical, t_vect *cartesian)
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

	print_vect(v_in);
	to_spherical(v_in, &spherical_in);
	spherical_in.phi += phi;
	spherical_in.theta += theta;
	to_cartesian(&spherical_in, v_out);
	print_vect(v_out);
}
