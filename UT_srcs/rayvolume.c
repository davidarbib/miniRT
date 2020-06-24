/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayvolume.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/23 19:19:23 by darbib            #+#    #+#             */
/*   Updated: 2020/06/24 15:47:39 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include <assert.h>

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
	if (var[t0] < 0)
		return (var[t1]);
	return (var[t0]);
}

int main()
{
	t_ray		ray;
	t_sphere	sphere;

	ray.origin = (t_vect){0., 0., 0.};
	ray.direction = (t_vect){0., 0., -1.};
	sphere.current_pos = (t_vect){0., 0., -5}; 
	sphere.diam = 8.; 
	printf("t = %lf\n", intersect_sphere(sphere, ray));// = 1

	ray.origin = (t_vect){0., 0., -1.};
	printf("t = %lf\n", intersect_sphere(sphere, ray));// = 0

	ray.origin = (t_vect){0., 0., -2.};
	printf("t = %lf\n", intersect_sphere(sphere, ray));// = 7

	ray.origin = (t_vect){2., 0., 0.};
	printf("t = %lf\n", intersect_sphere(sphere, ray));// 1.5 < t < 2

	ray.origin = (t_vect){2., 0., -2.};
	printf("t = %lf\n", intersect_sphere(sphere, ray));// 6 < t < 7
}
