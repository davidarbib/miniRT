/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:21:50 by darbib            #+#    #+#             */
/*   Updated: 2020/07/11 01:37:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

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
	r_dot_v = pow(dot(&reflect, &ray->direction), SHINE); 
	scale((KD * l_dot_n + KS * r_dot_v), &shadow->rgb_ratio, &tmp);
	scale(shadow->current_light_ratio, &tmp, &tmp);
	add_vect(&near->rgb_ratio, &tmp, &near->rgb_ratio);
	shadow->light_actions++;
}
