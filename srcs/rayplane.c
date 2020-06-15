/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/06/15 17:43:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

int		intersect_plane(t_vect plane_pos, t_vect plane_orient,
		t_vect ray_origin, t_vect ray_direction)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	normalize(&plane_pos, &plane_pos);
	normalize(&ray_origin, &ray_origin);
	normalize(&ray_direction, &ray_direction);
	denom = dot(&ray_direction, &plane_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&plane_pos, &ray_origin, &tmp_v);
		t = dot(&tmp_v, &plane_orient) / denom;
		return (t >= EPSILON);
	}
	return (0);
}

/*
** Moller-Trumbore algorithm implementation
** u, v are barycentric coordinates
*/
double	intersect_triangle(t_ray *ray, t_trig triangle)
{	
	double	det;
	double	inv_det;
	double 	barycoord[2];
	double	t;
	t_vect	tmp[3];

	cross(&ray->direction, &triangle.current_edge2, &tmp[PVEC]);
	det = dot(&triangle.current_edge1, &tmp[PVEC]);
	if (det > (EPSILON * -1) && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	sub_vect(&ray->origin, &triangle.current_pt1, &tmp[TVEC]);
	barycoord[U] = inv_det * dot(&tmp[TVEC], &tmp[PVEC]);
	if (barycoord[U] < 0.0 || barycoord[U] > 1.0)
		return (0);
	cross(&tmp[TVEC], &triangle.current_edge1, &tmp[QVEC]);
	barycoord[V] = inv_det * dot(&ray->direction, &tmp[QVEC]);
	if (barycoord[V] < 0.0 || barycoord[U] + barycoord[V] > 1.0)
		return (0);
	t = inv_det * dot(&triangle.current_edge2, &tmp[QVEC]);
	if (t > EPSILON)
	//if (t > 0)
		return (t);
	return (0);
}
