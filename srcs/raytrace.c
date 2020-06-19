/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 20:37:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "print.h"
#include "rotation.h"
#include <math.h>

double	(*g_intersect_ft[TYPE_NB])(u_obj obj, t_ray ray);

void		assign_intersect_fts(void)
{
	g_intersect_ft[plane] = intersect_plane;
	g_intersect_ft[triangle] = intersect_triangle;
}

static void	loop_intersect(u_objs *objs, int n, t_ray *ray, t_near *near)
{
	double t;

	while (--n >= 0)
	{
		if ((t = g_intersect_ft[ray->current_type](objs[n], *ray)) < near->t)
		{
			near->t = t;
			near->obj = obj + n;
			near->type = ray->current_type;
		}
	}
}

static unsigned char get_obj_rgb(enum e_type type, u_obj  
static void browse_scene(t_scene *scene, t_ray *ray, t_near *near)
{
	ray->current_type = plane;
	loop_intersect(scene->planes, scene->planes_n, ray, near); 
	ray->current_type = triangle;
	loop_intersect(scene->triangles, scene->triangles_n, ray, near); 
}

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy, t_ray *ray)
{
	t_near	near;
	
	near.t = INFINITY;
	near.obj = NULL;
	browse_scene(scene, ray, &near);
	if (near.obj)
		apply_color(near.obj->rgb, mlx_cfg, dx, dy);
		
	/*
	if (intersect_triangle(ray, scene->triangles[0]) > 0)
		apply_color(scene->triangles[0].rgb, mlx_cfg, dx, dy);
	else
		apply_color(scene->background_rgb, mlx_cfg, dx, dy);
	*/
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
			ray.direction.x = (2 * (dx + 0.5) / WIDTH - 1) * half_screen
			* aspect_ratio;
			ray.direction.y = (1 - 2 * (dy + 0.5) / HEIGHT) * half_screen;
			ray.direction.z = -1.0;	

			ray.inv_direction.x = 1 / ray.direction.x;
			ray.inv_direction.y = 1 / ray.direction.y;
			ray.inv_direction.z = 1 / ray.direction.z;

			normalize(&ray.direction, &ray.direction);

			ray.sign[0] = (ray.direction.x < 0);
			ray.sign[1] = (ray.direction.y < 0);
			ray.sign[2] = (ray.direction.z < 0);
			send_ray(scene, mlx_cfg, dx, dy, &ray);	
			dy++;
		}
		dx++;
	}
}
