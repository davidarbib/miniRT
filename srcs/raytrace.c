/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/06/04 19:15:31 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "print.h"
#include <math.h>

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

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy, t_ray *ray)
{
	/*
	printf("----pts triangles-----\n");
	print_vect(&scene->triangles[0].current_pt1);
	print_vect(&scene->triangles[0].current_pt2);
	print_vect(&scene->triangles[0].current_pt3);
	print_vect(&scene->triangles[1].current_pt1);
	print_vect(&scene->triangles[1].current_pt2);
	print_vect(&scene->triangles[1].current_pt3);
	printf("-----------------------\n");
	*/

	/*
	if (intersect_triangle(ray, scene->triangles[0]))
	{
		apply_color(scene->triangles[0].rgb, mlx_cfg, dx, dy);
		printf("A\n");
	}
	*/
	if (intersect_triangle(ray, scene->triangles[1]))
	{
		apply_color(scene->triangles[1].rgb, mlx_cfg, dx, dy);
		printf("B\n");
	}
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;
	double	half_screen;
	double	aspect_ratio;
	t_ray	ray;

	ray.origin.x = 0;
	ray.origin.y = 0;
	ray.origin.z = 0;
	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	aspect_ratio = WIDTH / (double)HEIGHT;
	dx = 0;
	while (dx < WIDTH)
	{
		dy = 0;
		while (dy < HEIGHT)
		{
			ray.direction.x = WIDTH/2. - dx;
			ray.direction.y = HEIGHT/2. - dy;
			ray.direction.z = -550.;	

			ray.direction.x = (2 * (dx + 0.5) / WIDTH - 1) * half_screen * aspect_ratio;
			ray.direction.y = (1 - 2 * (dy + 0.5) / HEIGHT) * half_screen;
			ray.direction.z = -1.0;	

			ray.direction.x = 0.6; 
			ray.direction.y = 0.52; 
			ray.direction.z = -1.0;	

			ray.inv_direction.x = 1 / ray.direction.x;
			ray.inv_direction.y = 1 / ray.direction.y;
			ray.inv_direction.z = 1 / ray.direction.z;

			normalize(&ray.direction, &ray.direction);

			ray.sign[0] = (ray.direction.x < 0);
			ray.sign[1] = (ray.direction.y < 0);
			ray.sign[2] = (ray.direction.z < 0);
			send_ray(scene, mlx_cfg, dx, dy, &ray);	

			if (dx == 0 && dy == 0)
				print_vect(&ray.direction);
			if (dx == WIDTH - 1 && dy == 0)
				print_vect(&ray.direction);
			if (dx == 0 && dy == HEIGHT - 1)
				print_vect(&ray.direction);
			if (dx == WIDTH - 1 && dy == HEIGHT - 1)
				print_vect(&ray.direction);
			//if (dx == WIDTH / 2 && dy == HEIGHT / 2)
			//	print_vect(&ray.direction);
			dy++;
			//break;
		}
		//break;
		dx++;
	}
}
