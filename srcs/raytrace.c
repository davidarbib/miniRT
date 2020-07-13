/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/07/13 14:41:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "print.h"
#include "rotation.h"
#include <math.h>

void	(*g_get_properties[TYPE_NB])(t_near *, t_ray);

static void	init_send_ray(t_near *near, t_scene *scene)
{
	near->t = INFINITY;
	near->obj = NULL;
	ft_memmove(near->rgb, scene->background_rgb, 3);
	near->rgb_ratio = (t_vect) {0, 0, 0};
}

static void	merge_light(t_scene *scene, t_ray *ray, t_near *near)
{
	t_vect	tmp;
	t_ray	sray;
	t_near	snear;
	int		n;

	snear.ratio_sum = 0;
	n = -1;
	while (++n < scene->olights_n)
	{
		sray.origin = near->hit;
		sub_vect(&scene->olights[n].current_pos, &near->hit, &sray.direction);
		normalize(&sray.direction, &sray.direction);
		snear.obj = NULL;
		browse_scene(scene, &sray, &snear);	
		if (snear.obj)
			continue;
		snear.current_light_ratio = scene->olights[n].ratio;
		to_rgb_ratio(scene->olights[n].rgb, &snear.rgb_ratio);
		compute_illumination(ray, &sray, near, &snear);
	}
	scale((KA * scene->ambient_ratio), &scene->ambient_rgb, &tmp); 
	add_vect(&tmp, &near->rgb_ratio, &near->rgb_ratio);
	snear.ratio_sum += scene->ambient_ratio;
	scale(1. / snear.ratio_sum, &near->rgb_ratio, &near->rgb_ratio);
}

static void send_ray(t_scene *scene, t_mlx *mlx_cfg, int dx, int dy, t_ray *ray)
{
	t_near	near;
	
	if (dx == WIDTH/2 && dy == HEIGHT/2)
		printf("cc\n");
	init_send_ray(&near, scene);
	browse_scene(scene, ray, &near);
	if (near.obj)
	{
		g_get_properties[near.type](&near, *ray);
		merge_light(scene, ray, &near);
		light_on_obj(&near.rgb_ratio, near.rgb);
	}
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

	g_get_properties[plane] = get_hit_plane;
	g_get_properties[square] = get_hit_square;
	g_get_properties[triangle] = get_hit_triangle;
	g_get_properties[sphere] = get_hit_sphere;
	g_get_properties[cylinder] = get_hit_cylinder;
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
