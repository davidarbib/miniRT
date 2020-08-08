/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/08/07 17:18:00 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include "print.h"
#include "rotation.h"
#include <math.h>

void		(*g_get_properties[TYPE_NB])(t_near *, t_ray);

static void	init_send_ray(t_near *near, t_scene *scene)
{
	g_get_properties[plane] = get_hit_plane;
	g_get_properties[square] = get_hit_square;
	g_get_properties[triangle] = get_hit_triangle;
	g_get_properties[sphere] = get_hit_sphere;
	g_get_properties[cylinder] = get_hit_cylinder;
	near->t = INFINITY;
	near->obj = NULL;
	ft_memmove(near->rgb, scene->background_rgb, 3);
	near->rgb_ratio = (t_vect) {0, 0, 0};
}

static void	merge_light(t_scene *scene, t_ray *ray, t_near *near)
{
	t_vect		tmp;
	t_ray		sray;
	t_shadow	sh;
	int			n;

	sh.ratio_sum = 0;
	n = -1;
	while (++n < scene->olights_n)
	{
		sub_vect(&scene->olights[n].current_pos, &near->hit, &sray.direction);
		scale(EPSILON, &sray.direction, &tmp);
		add_vect(&near->hit, &tmp, &sray.origin);
		sh.t_light = vect_norm(&sray.direction);
		normalize(&sray.direction, &sray.direction);
		if (light_cast(scene, &sray, &sh))
			continue;
		sh.current_light_ratio = scene->olights[n].ratio;
		to_rgb_ratio(scene->olights[n].rgb, &sh.rgb_ratio);
		compute_illumination(ray, &sray, near, &sh);
	}
	scale((KA * scene->ambient_ratio), &scene->ambient_rgb, &tmp);
	add_vect(&tmp, &near->rgb_ratio, &near->rgb_ratio);
	sh.ratio_sum += scene->ambient_ratio;
}

t_vect		send_ray(t_scene *scene, t_ray *ray)
{
	t_near	near;
	t_vect	pix_rgb;

	init_send_ray(&near, scene);
	browse_scene(scene, ray, &near);
	if (near.obj)
	{
		g_get_properties[near.type](&near, *ray);
		merge_light(scene, ray, &near);
		pix_rgb = light_on_obj(&near.rgb_ratio, near.rgb);
	}
	else
		to_rgb_ratio(near.rgb, &pix_rgb);
	return (pix_rgb);
}

void		define_ray(t_ray *ray, double half_screen, int *coord,
			t_scene *scene)
{
	double	aspect_ratio;
	double	x;
	double	y;

	aspect_ratio = (double)scene->resx / scene->resy;
	x = (double)coord[dx];
	y = (double)coord[dy];
	x += ((!scene->lowres) + (scene->lowres * LOWFACTOR)) * 0.5;
	y += ((!scene->lowres) + (scene->lowres * LOWFACTOR)) * 0.5;
	ray->direction.x = (2 * x / scene->resx - 1) * half_screen
	* aspect_ratio;
	ray->direction.y = (1 - 2 * y / scene->resy) * half_screen;
	ray->direction.z = -1.0;
	ray->inv_direction.x = 1 / ray->direction.x;
	ray->inv_direction.y = 1 / ray->direction.y;
	ray->inv_direction.z = 1 / ray->direction.z;
	normalize(&ray->direction, &ray->direction);
	ray->sign[0] = (ray->direction.x < 0);
	ray->sign[1] = (ray->direction.y < 0);
	ray->sign[2] = (ray->direction.z < 0);
	ray->origin = (t_vect) {0, 0, 0};
}

void		raytrace(t_scene *scene, t_mlx *cfg)
{
	int		coord[2];
	t_ray	ray;
	double	half_screen;
	t_vect	pix_rgb;

	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	coord[dx] = 0;
	while (coord[dx] < cfg->resx)
	{
		coord[dy] = 0;
		while (coord[dy] < cfg->resy)
		{
			define_ray(&ray, half_screen, coord, scene);
			print_vect(&ray.direction);
			pix_rgb = send_ray(scene, &ray);
			apply_color(&pix_rgb, cfg, coord[dx], coord[dy]);
			coord[dy]++;
		}
		coord[dx]++;
	}
}
