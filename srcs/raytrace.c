/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/07/19 15:01:01 by darbib           ###   ########.fr       */
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
	//	printf("---------------------\n");
	//	print_vect(&sray.origin);
	//	print_vect(&sray.direction);
	//	printf("---------------------\n");
		normalize(&sray.direction, &sray.direction);
		if (light_cast(scene, &sray, &sh))
			continue;
		//printf("sh obj %p coord :\n", sh.obj);
		//print_vect(&((t_plane *)sh.obj)->current_pos);
		sh.current_light_ratio = scene->olights[n].ratio;
		to_rgb_ratio(scene->olights[n].rgb, &sh.rgb_ratio);
		compute_illumination(ray, &sray, near, &sh);
	}
	scale((KA * scene->ambient_ratio), &scene->ambient_rgb, &tmp); 
	add_vect(&tmp, &near->rgb_ratio, &near->rgb_ratio);
	sh.ratio_sum += scene->ambient_ratio;
	scale(1. / sh.ratio_sum, &near->rgb_ratio, &near->rgb_ratio);
}

static t_vect send_ray(t_scene *scene, t_ray *ray)
{
	t_near	near;
	t_vect pix_rgb;
	
	init_send_ray(&near, scene);
	browse_scene(scene, ray, &near);
	if (near.obj)
	{
		g_get_properties[near.type](&near, *ray);
		merge_light(scene, ray, &near);
		light_on_obj(&near.rgb_ratio, near.rgb);
	}
	to_rgb_ratio(near.rgb, &pix_rgb);
	return (pix_rgb);
	//apply_color(near.rgb, mlx_cfg, dx, dy);
}

# define RESX 200
# define RESY 200

static void	define_ray(t_ray *ray, double half_screen, int *coord,
		t_scene *scene)
{
	double	aspect_ratio;

	aspect_ratio = WIDTH / (double)HEIGHT;
	coord[dx] += (WIDTH / scene->resx) / 2;
	coord[dy] += (HEIGHT / scene->resy) / 2;
	ray->direction.x = (2 * coord[dx] / WIDTH - 1) * half_screen
	* aspect_ratio;
	ray->direction.y = (1 - 2 * coord[dy] / HEIGHT) * half_screen;
	ray->direction.z = -1.0;	
	//ray->direction.x = (2 * (coord[dx] + 0.5) / WIDTH - 1) * half_screen
	//	* aspect_ratio;
	//ray->direction.y = (1 - 2 * (coord[dy] + 0.5) / HEIGHT) * half_screen;
	//ray->direction.z = -1.0;	
	ray->inv_direction.x = 1 / ray->direction.x;
	ray->inv_direction.y = 1 / ray->direction.y;
	ray->inv_direction.z = 1 / ray->direction.z;
	normalize(&ray->direction, &ray->direction);
	ray->sign[0] = (ray->direction.x < 0);
	ray->sign[1] = (ray->direction.y < 0);
	ray->sign[2] = (ray->direction.z < 0);
	ray->origin = (t_vect) {0, 0, 0};
}

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int		begincord[2];
	int		endcord[2];
	t_ray	ray;
	double	half_screen;
	t_vect	pix_rgb;

	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	begincord[dx] = 0;
	while (begincord[dx] < scene->resx)
	{
		begincord[dy] = 0;
		endcord[dx] = begincord[dx] + WIDTH / scene->resx;
		while (begincord[dy] < scene->resy)
		{
			define_ray(&ray, half_screen, begincord, scene);
			pix_rgb = send_ray(scene, &ray);	
			endcord[dy] = begincord[dy] + HEIGHT / scene->resy;
			colorize_pixels(pix_rgb, mlx_cfg, begincord, endcord);
			begincord[dy] = endcord[dy];
		}
		begincord[dx] = endcord[dx];
	}
}
