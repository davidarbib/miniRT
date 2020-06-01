/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/06/01 22:04:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>

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

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy)
{
	t_ray	ray;

	ray.direction.x = scene->resx/2. - dx;
	ray.direction.y = scene->resy/2. - dy;
	ray.direction.z = 550.;	
	ray.inv_direction.x = 1 / ray.direction.x;
	ray.inv_direction.y = 1 / ray.direction.y;
	ray.inv_direction.z = 1 / ray.direction.z;
	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;
	ray.sign[0] = (ray.direction.x < 0);
	ray.sign[1] = (ray.direction.y < 0);
	ray.sign[2] = (ray.direction.z < 0);
	/*
	if (intersect_plane(scene->planes->current_pos, scene->planes->current_orient,
				*ray.origin, *ray.direction)) 
		apply_color(scene->planes->rgb, mlx_cfg, dx, dy);
	*/
	if (intersect_triangle(&ray, scene->triangles[0]))
		apply_color(scene->triangles[0].rgb, mlx_cfg, dx, dy);
	//else if (intersect_aabb(scene->aabb2, &ray))
	//	apply_color(scene->aabb2->rgb, mlx_cfg, dx, dy);
	//else if (intersect_aabb(scene->aabb3, &ray))
	//	apply_color(scene->aabb3->rgb, mlx_cfg, dx, dy);
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;

	dx = 0;
	while (dx < scene->resx)
	{
		dy = 0;
		while (dy < scene->resy)
		{
			send_ray(scene, mlx_cfg, dx, dy);	
			dy++;
		}
		dx++;
	}
}
