/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:19:28 by darbib            #+#    #+#             */
/*   Updated: 2020/05/03 16:21:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"

static inline int overlap(double *t0, double *t1, double min_, double max_)
{
	if (*t0 < min_)
		*t0 = min_;
	if (*t1 > max_)
		*t1 = max_;
	if (*t1 < *t0)
		return (0);
	return (1);
}

int		intersect_aabb(t_aabb *aabb, t_ray *ray)
{
	t_vect	tmin;
	t_vect	tmax;
	double	t0;
	double	t1;
	
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
	return (t1 > 0);	
}
