/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayaabb.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 19:03:08 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 19:09:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "aabb.h"

static inline int	overlap(double *t0, double *t1, double min_, double max_)
{
	if ((*t0 > max_) || (min_ > *t1))
		return (0);
	if (min_ > *t0)
		*t0 = min_;
	if (max_ < *t1)
		*t1 = max_;
	return (1);
}

int					intersect_aabb(t_aabb *aabb, t_ray *ray)
{
	t_vect	tmin;
	t_vect	tmax;
	double	t0;
	double	t1;

	tmin.x = (aabb->corner[ray->sign[0]].x - ray->origin.x)
			* ray->inv_direction.x;
	tmax.x = (aabb->corner[1 - ray->sign[0]].x - ray->origin.x)
			* ray->inv_direction.x;
	tmin.y = (aabb->corner[ray->sign[1]].y - ray->origin.y)
			* ray->inv_direction.y;
	tmax.y = (aabb->corner[1 - ray->sign[1]].y - ray->origin.y)
			* ray->inv_direction.y;
	t0 = tmin.x;
	t1 = tmax.x;
	if (!overlap(&t0, &t1, tmin.y, tmax.y))
		return (0);
	tmin.z = (aabb->corner[ray->sign[2]].z - ray->origin.z)
			* ray->inv_direction.z;
	tmax.z = (aabb->corner[1 - ray->sign[2]].z - ray->origin.z)
			* ray->inv_direction.z;
	if (!overlap(&t0, &t1, tmin.z, tmax.z))
		return (0);
	return (t1 > 0.);
}
