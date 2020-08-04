/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayvolume.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:19:23 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 17:29:33 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

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
	var[d] = sqrt(fabs(len_co * len_co - var[t_ca] * var[t_ca]));	
	/*
	if (acos(var[t_ca]) < EPSILON && ft_abs(len_co - var[t_ca]) < EPSILON)
		var[d] = 0;
	*/
	if (var[d] > r)
		return (0);
	var[t_hc] = sqrt(r * r - var[d] * var[d]);
	var[t0] = var[t_ca] - var[t_hc];
	var[t1] = var[t_ca] + var[t_hc];
	/*
	printf("len_co = %.20lf\n", len_co);
	printf("d = %lf\nt_ca = %.20lf\nt_hc = %lf\n", var[d], var[t_ca], var[t_hc]);
	printf("t0 = %lf\nt1 = %lf\n", var[t0], var[t1]);
	*/
	if (var[t0] < EPSILON)
	{
		if (var[t1] >= EPSILON)
			return (var[t1]);
		else
			return (0);
	}
	return (var[t0]);
}

void	compute_t_check_height(t_cylinder cylinder, t_ray ray, double *var,
		t_vect tmp)
{
	t_vect	tmp_v[2];
	t_vect	hit_bc[2];
	double	pt_c[2];
	
	var[s] = ft_double_abs(sqrt((cylinder.radius) * (cylinder.radius) 
			- var[dc] * var[dc]) / dot(&ray.direction, &tmp));
	var[t1c] = var[tc] - var[s];
	var[t2c] = var[tc] + var[s];
	get_hit_point(var[t1c], ray.direction, ray.origin, &tmp_v[0]);
	get_hit_point(var[t2c], ray.direction, ray.origin, &tmp_v[1]);
	sub_vect(&tmp_v[0], &cylinder.current_pos, &hit_bc[0]);
	sub_vect(&tmp_v[1], &cylinder.current_pos, &hit_bc[1]);
	pt_c[0] = dot(&hit_bc[0], &cylinder.current_orient);
	pt_c[1] = dot(&hit_bc[1], &cylinder.current_orient);
	if (var[t1c] > EPSILON && pt_c[0] > EPSILON
			&& pt_c[0] < cylinder.height + EPSILON)
		var[t_return] = var[t1c];
	else if (var[t2c] > EPSILON && pt_c[1] > EPSILON
				&& pt_c[1] < cylinder.height + EPSILON)
		var[t_return] = var[t2c];
	else
		var[t_return] = 0;
}

/*
**
*/
double intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	double	var[7];
	t_vect	tmp[2];
	t_vect	tmp_v;

	cross(&ray.direction, &cylinder.current_orient, &tmp[rxa]);
	if (is_null_vect(tmp[rxa]))
		return (0);
	sub_vect(&cylinder.current_pos, &ray.origin, &tmp[bc_min_br]);
	var[len_rxa] = vect_norm(&tmp[rxa]);
	normalize(&tmp[rxa], &tmp[rxa]);
	var[dc] = ft_double_abs(dot(&tmp[bc_min_br], &tmp[rxa]));
	if (var[dc] > (cylinder.radius) + EPSILON)
		return (0);
	cross(&tmp[bc_min_br], &cylinder.current_orient, &tmp_v);
	var[tc] = dot(&tmp_v, &tmp[rxa]) / var[len_rxa];
	cross(&tmp[rxa], &cylinder.current_orient, &tmp_v);
	compute_t_check_height(cylinder, ray, var, tmp_v);
	return (var[t_return]);
}
