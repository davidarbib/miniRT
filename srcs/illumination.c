/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   illumination.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:21:50 by darbib            #+#    #+#             */
/*   Updated: 2020/07/16 17:39:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

void	compute_illumination(t_ray *ray, t_ray *shadow_ray, t_near *near,
		t_shadow *shadow)
{
	t_vect	tmp;
	t_vect	reflect;
	double 	l_dot_n;
	double 	r_dot_v;
	double	illu;

	l_dot_n = dot(&shadow_ray->direction, &near->normal);
	scale(2 * l_dot_n, &near->normal, &tmp);
	sub_vect(&tmp, &shadow_ray->direction, &reflect);
	normalize(&reflect, &reflect);
	scale(-1, &ray->direction, &tmp);
	r_dot_v = dot(&reflect, &tmp); 
	illu = KD * fmax(l_dot_n, 0);
	if (illu > 0)
		illu += KS * pow(fmax(r_dot_v, 0), SHINE);	
	scale(illu, &shadow->rgb_ratio, &tmp);
	scale(shadow->current_light_ratio, &tmp, &tmp);
	add_vect(&near->rgb_ratio, &tmp, &near->rgb_ratio);
	shadow->ratio_sum += shadow->current_light_ratio;
}
