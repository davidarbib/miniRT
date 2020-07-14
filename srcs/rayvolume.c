/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayvolume.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:19:23 by darbib            #+#    #+#             */
/*   Updated: 2020/07/13 18:59:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

/*
** geometric solution
*/
double intersect_sphere(t_sphere sphere, t_ray ray)
{
	t_vect	v_co;
	double	var[5];
	double	len_co;
	double	r;

	r = sphere.radius;
	sub_vect(&sphere.current_pos, &ray.origin, &v_co);
	var[t_ca] = dot(&v_co, &ray.direction);
	if (var[t_ca] < 0)
		return (0);
	len_co = vect_norm(&v_co);
	var[d] = sqrt(len_co * len_co - var[t_ca] * var[t_ca]);	
	if (var[d] > r)
		return (0);
	var[t_hc] = sqrt(r * r - var[d] * var[d]);
	var[t0] = var[t_ca] - var[t_hc];
	var[t1] = var[t_ca] + var[t_hc];
	if (var[t0] < EPSILON)
		return (var[t1]);
	return (var[t0]);
}

/*
**
*/
double intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	double	var[6];
	t_vect	bc_min_br;
	t_vect	r_x_a;
	t_vect	tmp_v;
	
	cross(&ray.direction, &cylinder.current_orient, &r_x_a);
	if (is_null_vect(r_x_a))
		return (0);
	sub_vect(&cylinder.current_pos, &ray.origin, &bc_min_br);
	var[len_rxa] = vect_norm(&r_x_a);
	normalize(&r_x_a, &r_x_a);
	var[dc] = ft_double_abs(dot(&bc_min_br, &r_x_a));
	if (var[dc] > (cylinder.diam / 2) + EPSILON)
		return (0);
	cross(&bc_min_br, &cylinder.current_orient, &tmp_v);
	var[tc] = dot(&tmp_v, &r_x_a) / var[len_rxa];
	cross(&r_x_a, &cylinder.current_orient, &tmp_v);
	var[s] = ft_double_abs(sqrt((cylinder.radius) * (cylinder.radius) 
			- var[dc] * var[dc]) / dot(&ray.direction, &tmp_v));
	var[t1c] = var[tc] - var[s];
	var[t2c] = var[tc] + var[s];
	if (var[t1c] > EPSILON)
		return (var[t1c]);
	return (var[t2c]);
}
