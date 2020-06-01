/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/06/01 21:52:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

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
** original triangle vertices used to store the three tmp vectors
** (its why we need a triangle copy)
** t, u, v are barycentric coordinates
*/
int		intersect_triangle(t_ray *ray, t_trig triangle)
{	
	double	det;
	double	inv_det;
	double	u;
	double	v;
	double	t;

	cross(&ray->direction, &triangle.current_edge2, &triangle.pt1);
	det = dot(&triangle.current_edge1, &triangle.pt1);
	if (ft_abs(det) < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	sub_vect(&ray->origin, &triangle.current_pt1, &triangle.pt2);
	u = inv_det * dot(&triangle.pt2, &triangle.pt1);
	if (u < 0.0 || u > 1.0)
		return (0);
	cross(&triangle.pt2, &triangle.current_edge1, &triangle.pt3);
	v = inv_det * dot(&ray->direction, &triangle.pt3);
	if (v < 0.0 || u + v > 1.0)
		return (0);
	t = inv_det * dot(&triangle.current_edge2, &triangle.pt3);
	if (t > EPSILON)
		return (t);
	return (0);
}
