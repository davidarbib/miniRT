/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:19:28 by darbib            #+#    #+#             */
/*   Updated: 2020/05/05 17:36:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <stdio.h>

static inline int overlap(double *t0, double *t1, double min_, double max_)
{
	//printf("t0 : %lf, t1 : %lf, min_ : %lf, max_ : %lf\n", *t0, *t1, min_, max_);
	if ((*t0 > max_) || (min_ > *t1))
		return (0);
	if (min_ > *t0)
		*t0 = min_;
	if (max_ < *t1)
		*t1 = max_;
	return (1);
}

int		intersect_aabb(t_aabb *aabb, t_ray *ray)
{
	t_vect	tmin;
	t_vect	tmax;
	double	t0;
	double	t1;
	
	/*
	printf("corner[0] = (%lf, %lf, %lf)\n", aabb->corner[0].x, aabb->corner[0].y,
			aabb->corner[0].z);
	printf("corner[1] = (%lf, %lf, %lf)\n", aabb->corner[1].x, aabb->corner[1].y,
			aabb->corner[1].z);
	printf("------------------\n");
	printf("ray_origin : (%lf, %lf, %lf)\n", ray->origin->x, ray->origin->y,
			ray->origin->z);
	*/
	tmin.x = (aabb->corner[ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	tmax.x = (aabb->corner[1 - ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	tmin.y = (aabb->corner[ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	tmax.y = (aabb->corner[1 - ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	t0 = tmin.x;
	t1 = tmax.x;
	if (!overlap(&t0, &t1, tmin.y, tmax.y))
		return (0);
	tmin.z = (aabb->corner[ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	tmax.z = (aabb->corner[1 - ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	if (!overlap(&t0, &t1, tmin.z, tmax.z))
		return (0);
	return (t1 > 0.);	
}
