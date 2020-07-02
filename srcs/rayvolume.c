/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayvolume.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:19:23 by darbib            #+#    #+#             */
/*   Updated: 2020/07/02 20:51:56 by darbib           ###   ########.fr       */
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

	r = (sphere.diam / 2);
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
double intersect_cylinder(t_cyld cylinder, t_ray ray)
{
	double	var[6];
	t_vect	br_min_bc;
	t_vect	r_x_a;
	t_vect	d_x_a;
	t_vect	tmp_v;
	
	cross(&ray.direction, &cylinder.current_orient, &r_x_a);
	if (is_null_vect(r_x_a))
		return (0);
	sub_vect(&ray.origin, &cylinder.pos, &br_min_bc);
	var[len_rxa] = vect_norm(&r_x_a);
	normalize(&r_x_a, &r_x_a);
	var[d] = ft_double_abs(dot(&br_min_bc, &r_x_a));
	if (var[d] > cylinder.diam)
		return (0);
	cross(&br_min_bc, &ray.direction, &tmp_v);
	var[t] = dot(&tmp_v, &r_x_a) / var[len_rxa];
	cross(&r_x_a, &cylinder.current_orient, &tmp_v);
	var[s] = ft_double_abs(sqrt((diam / 2) * (diam / 2) - var[d] * var[d])
								/ dot(&ray.current_orient, &tmp_v));
	var[t1] = var[t] - var[s];
	var[t2] = var[t] + var[s];
	if (var[t1] > EPSILON)
		return (var[t1]);
	return (var[t2]);
}
