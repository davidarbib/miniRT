/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/05 18:21:04 by darbib            #+#    #+#             */
/*   Updated: 2020/06/17 15:02:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vector.h"
#include "rotation.h"
#include <math.h>
#include "matrix.h"

void	to_spherical(t_vect *cartesian, t_spheric *spherical)
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

void	extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
		double *matrix)
{
	t_vect normal;
	double dot_result;

	cross(cam_orient, ref_orient, &normal);
	normalize(&normal, &normal);
	dot_result = dot(cam_orient, ref_orient);
}

void	rotate_point(double *matrix, t_vect *v_in, t_vect *v_out)
{
	if (!vect_norm(v_in))
	{
		v_out->x = v_in->x; 
		v_out->y = v_in->y; 
		v_out->z = v_in->z; 
	}
	else
		matrix_by_vect(matrix, v_in, v_out);
}
