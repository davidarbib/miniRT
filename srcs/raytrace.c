/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/06/22 19:42:49 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "print.h"
#include "rotation.h"
#include <math.h>

void	get_obj_rgb(void *obj, enum e_type type, unsigned char *rgb)
{
	if (type == triangle)
		ft_memmove(rgb, ((t_trig *)obj)->rgb, 3);
	else if (type == plane)
		ft_memmove(rgb, ((t_plane *)obj)->rgb, 3);
	else if (type == square)
		ft_memmove(rgb, ((t_square *)obj)->rgb, 3);
	else if (type == sphere)
		ft_memmove(rgb, ((t_sphere *)obj)->rgb, 3);
	else if (type == cylinder)
		ft_memmove(rgb, ((t_cyld *)obj)->rgb, 3);
}

static void browse_scene(t_scene *scene, t_ray *ray, t_near *near)
{
	ray->current_type = plane;
	loop_intersect_planes(scene->planes, scene->planes_n, ray, near); 
	ray->current_type = triangle;
	loop_intersect_triangles(scene->triangles, scene->triangles_n, 
					ray, near); 
}

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy, t_ray *ray)
{
	t_near	near;
	
	near.t = INFINITY;
	near.obj = NULL;
	ft_memmove(near.rgb, scene->background_rgb, 3);
	browse_scene(scene, ray, &near);
	apply_color(near.rgb, mlx_cfg, dx, dy);
}

static void	define_ray(t_ray *ray, double half_screen, int dx, int dy)
{
	double	aspect_ratio;

	aspect_ratio = WIDTH / (double)HEIGHT;
	ray->direction.x = (2 * (dx + 0.5) / WIDTH - 1) * half_screen
		* aspect_ratio;
	ray->direction.y = (1 - 2 * (dy + 0.5) / HEIGHT) * half_screen;
	ray->direction.z = -1.0;	
	//-----------------
	if (dx == WIDTH/2 && dy == HEIGHT/2)
	{
		printf("ray_direction at (0, 0)\n");
		print_vect(&ray->direction);
	}
	//-----------------
	ray->inv_direction.x = 1 / ray->direction.x;
	ray->inv_direction.y = 1 / ray->direction.y;
	ray->inv_direction.z = 1 / ray->direction.z;
	normalize(&ray->direction, &ray->direction);
	ray->sign[0] = (ray->direction.x < 0);
	ray->sign[1] = (ray->direction.y < 0);
	ray->sign[2] = (ray->direction.z < 0);
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int dx;
	int dy;
	t_ray	ray;
	double	half_screen;

	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	ray.origin = (t_vect) {0, 0, 0};
	dx = -1;
	while (++dx < WIDTH)
	{
		dy = -1;
		while (++dy < HEIGHT)
		{
			define_ray(&ray, half_screen, dx, dy);
			send_ray(scene, mlx_cfg, dx, dy, &ray);	
		}
	}
}
