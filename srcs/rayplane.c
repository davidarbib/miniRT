/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 20:37:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

double	intersect_plane(u_obj obj, t_ray ray)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	normalize(&obj.pl.current_pos, &obj.pl.current_pos);
	normalize(&ray.origin, &ray.origin);
	normalize(&ray.direction, &ray.direction);
	denom = dot(&ray.direction, &obj.pl.current_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&obj.pl.current_pos, &ray.origin, &tmp_v);
		t = dot(&tmp_v, &obj.pl.current_orient) / denom;
		if (t >= EPSILON)
			return (t);
	}
	return (INFINITY);
}

/*
** see Moller-Trumbore algorithm
** u, v are barycentric coordinates
*/
double	intersect_triangle(u_obj obj, t_ray ray)
{	
	double	det;
	double	inv_det;
	double 	barycoord[2];
	double	t;
	t_vect	tmp[3];
	
	cross(&ray.direction, &obj.tr.current_edge2, &tmp[PVEC]);
	det = dot(&obj.tr.current_edge1, &tmp[PVEC]);
	if (det > (EPSILON * -1) && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	sub_vect(&ray.origin, &obj.tr.current_pt1, &tmp[TVEC]);
	barycoord[U] = inv_det * dot(&tmp[TVEC], &tmp[PVEC]);
	if (barycoord[U] < 0.0 || barycoord[U] > 1.0)
		return (0);
	cross(&tmp[TVEC], &obj.tr.current_edge1, &tmp[QVEC]);
	barycoord[V] = inv_det * dot(&ray.direction, &tmp[QVEC]);
	if (barycoord[V] < 0.0 || barycoord[U] + barycoord[V] > 1.0)
		return (0);
	t = inv_det * dot(&obj.tr.current_edge2, &tmp[QVEC]);
	if (t > EPSILON)
		return (t);
	return (INFINITY);
}
