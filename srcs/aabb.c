/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:19:28 by darbib            #+#    #+#             */
/*   Updated: 2020/04/30 20:31:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"

static int xy_intersection(t_aabb *aabb, t_ray *ray, double *tmin, double *tmax)
{
	double tymin;
	double tymax;

	*tmin = (aabb->corner[ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	*tmax = (aabb->corner[1 - ray->sign[0]].x - ray->origin->x)
			* ray->inv_direction->x;
	tymin = (aabb->corner[ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	tymax = (aabb->corner[1 - ray->sign[1]].y - ray->origin->y)
			* ray->inv_direction->y;
	if ((*tmin > tymax) || (tymin > tymax))
		return (0);
	if (tymin > *tmin)
		*tmin = tymin;
	if (tymax < *tmax)
		*tmax = tymax;
	return (1);
}

int		intersect_aabb(t_aabb *aabb, t_ray *ray)
{
	double tmin;
	double tmax;
	double tzmin;
	double tzmax;
	
	if (!xy_intersection(aabb, ray, &tmin, &tmax))
		return (0);
	tzmin = (aabb->corner[ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	tzmax = (aabb->corner[1 - ray->sign[2]].z - ray->origin->z)
			* ray->inv_direction->z;
	if ((tmin > tzmax) || (tzmin > tmax))
		return (0);
	if (tzmin > tmin)
		tmin = tzmin;
	if (tzmax < tmax)
		tmax = tzmax;
	return (tmax > 0);
}
