/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/06/30 15:12:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

void	get_ray_point(double t, t_ray ray, t_vect *v_out)
{
	t_vect tmp;
	scale(t, &ray.direction, &tmp);
	add_vect(&tmp, &ray.origin, v_out);
}

double	intersect_plane(t_plane plane, t_ray ray)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	denom = dot(&ray.direction, &plane.current_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&plane.current_pos, &ray.origin, &tmp_v);
		t = dot(&tmp_v, &plane.current_orient) / denom;
		if (t >= EPSILON)
			return (t);
	}
	return (0);
}

double	intersect_square(t_square square, t_ray ray)
{
	t_plane	plane;
	double	t;
	double	proj1;
	double	proj2;
	t_vect	v;
	
	plane.current_pos = square.current_pos;
	plane.current_orient = square.current_orient;	
	if (!(t = intersect_plane(plane, ray)))
		return (0);
	get_ray_point(t, ray, &v);
	sub_vect(&v, &square.current_pos, &v);
	normalize(&square.edge1, &square.edge1);
	normalize(&square.edge2, &square.edge2);
	proj1 = dot(&v, &square.edge1);
	proj2 = dot(&v, &square.edge2);
	if ((proj1 < square.height && proj1 > 0) 
		&& (proj2 < square.height && proj2 > 0))
		return (t);
	return (0);
}

/*
** see Moller-Trumbore algorithm
** u, v are barycentric coordinates
*/
double	intersect_triangle(t_trig triangle, t_ray ray)
{	
	double	det;
	double	inv_det;
	double 	barycoord[2];
	double	t;
	t_vect	tmp[3];
	
	cross(&ray.direction, &triangle.current_edge2, &tmp[PVEC]);
	det = dot(&triangle.current_edge1, &tmp[PVEC]);
	if (det > (EPSILON * -1) && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	sub_vect(&ray.origin, &triangle.current_pt1, &tmp[TVEC]);
	barycoord[U] = inv_det * dot(&tmp[TVEC], &tmp[PVEC]);
	if (barycoord[U] < 0.0 || barycoord[U] > 1.0)
		return (0);
	cross(&tmp[TVEC], &triangle.current_edge1, &tmp[QVEC]);
	barycoord[V] = inv_det * dot(&ray.direction, &tmp[QVEC]);
	if (barycoord[V] < 0.0 || barycoord[U] + barycoord[V] > 1.0)
		return (0);
	t = inv_det * dot(&triangle.current_edge2, &tmp[QVEC]);
	if (t > EPSILON)
		return (t);
	return (-1);
}
