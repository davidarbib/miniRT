/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:21:50 by darbib            #+#    #+#             */
/*   Updated: 2020/07/11 22:05:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

void	compute_illumination(t_ray *ray, t_ray *shadow_ray, t_near *near,
		t_near *shadow)
{
	t_vect	tmp;
	t_vect	reflect;
	double 	l_dot_n;
	double 	r_dot_v;

	l_dot_n = dot(&shadow_ray->direction, &near->normal); 
	scale(2 * l_dot_n, &near->normal, &tmp);
	sub_vect(&tmp, &shadow_ray->direction, &reflect);
	printf("reflect :\n");
	print_vect(&reflect);
	//normalize(&reflect, &reflect);
	printf("r_dot_v : %lf\n", dot(&reflect, &ray->direction));
	r_dot_v = pow(dot(&reflect, &ray->direction), SHINE); 
	scale((KD * l_dot_n + KS * r_dot_v), &shadow->rgb_ratio, &tmp);
	scale(shadow->current_light_ratio, &tmp, &tmp);
	add_vect(&near->rgb_ratio, &tmp, &near->rgb_ratio);
	shadow->ratio_sum += shadow->current_light_ratio;
}


int main()
{
	t_ray ray;
	t_ray shadow_ray;
	t_near near;
	t_near shadow;

	shadow_ray.direction = (t_vect) {1, 0, 1};
	near.normal = (t_vect) {0, 0, 1};
	ray.direction = (t_vect) {0, 0, -1};
	shadow.rgb_ratio = (t_vect) {0, 0, 1.};
	shadow.current_light_ratio = 0.3;
	near.rgb_ratio = (t_vect) {0.5, 0.5, 0.5};
	compute_illumination(&ray, &shadow_ray, &near, &shadow);
}
