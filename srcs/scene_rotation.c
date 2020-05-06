/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:21:04 by darbib            #+#    #+#             */
/*   Updated: 2020/05/07 01:32:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include <math.h>
#include <stdio.h>

 //pour mes axes
static void	to_spherical(t_vect *cartesian, t_vect *spherical)
{
	double rho;

	rho = vect_norm(cartesian);
	spherical->x = rho; 
	spherical->y = acos(cartesian->y / rho);  
	spherical->z = atan(cartesian->x / cartesian->z);
}

static void	to_cartesian(t_vect *spherical, t_vect *cartesian)
{
	cartesian->x = spherical->x * sin(spherical->y) * sin(spherical->z); 	
	cartesian->y = spherical->x * cos(spherical->y); 	
	cartesian->z = spherical->x * sin(spherical->y) * cos(spherical->z); 	
}

/* //comme conseille
static void	to_spherical(t_vect *cartesian, t_vect *spherical)
{
	double rho;

	rho = vect_norm(cartesian);
	spherical->x = rho; 
	spherical->y = acos(cartesian->z / rho);  
	spherical->z = atan(cartesian->y / cartesian->x);
}

static void	to_cartesian(t_vect *spherical, t_vect *cartesian)
{
	cartesian->x = spherical->x * sin(spherical->y) * cos(spherical->z); 	
	cartesian->y = spherical->x * sin(spherical->y) * sin(spherical->z); 	
	cartesian->z = spherical->x * cos(spherical->y); 	
}

*/
void		extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
			double *phi, double *theta)
{
	t_vect spherical_cam;
	t_vect spherical_ref;

	to_spherical(cam_orient, &spherical_cam);
	to_spherical(ref_orient, &spherical_ref);
	*phi = spherical_ref.y - spherical_cam.y;
	*theta = spherical_ref.z - spherical_cam.z;
	//printf("phi = %lf, theta = %lf\n", *phi, *theta);
}

void		rotate_point(double phi, double theta, t_vect *v_in, t_vect *v_out)
{
	t_vect spherical_in;

	to_spherical(v_in, &spherical_in);
	printf("spherical = (%lf, %lf, %lf)\n", spherical_in.x, spherical_in.y, 
			spherical_in.z);
	//printf("phi = %lf, theta = %lf\n", phi, theta);
	spherical_in.y += phi;
	spherical_in.z += theta;
	printf("spherical = (%lf, %lf, %lf)\n", spherical_in.x, spherical_in.y, 
			spherical_in.z);
	to_cartesian(&spherical_in, v_out);
}
