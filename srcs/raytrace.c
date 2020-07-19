/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 12:45:11 by darbib            #+#    #+#             */
/*   Updated: 2020/07/19 18:55:19 by darbib           ###   ########.fr       */
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
	//scale(1. / sh.ratio_sum, &near->rgb_ratio, &near->rgb_ratio);
}

t_vect send_ray(t_scene *scene, t_ray *ray)
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

void	define_ray(t_ray *ray, double half_screen, int *coord, t_scene *scene)
{
	double	aspect_ratio;
	int		x;
	int		y;

	aspect_ratio = scene->resx / scene->resy;
//	aspect_ratio = WIDTH / HEIGHT;
	x = coord[dx];
	y = coord[dy];
	x += ((!scene->lowres) + (scene->lowres * LOWFACTOR)) * 0.5 ;
	y += ((!scene->lowres) + (scene->lowres * LOWFACTOR)) * 0.5 ;
	//ray->direction.x = (2 * coord[dx] / scene->resx - 1) * half_screen
	//* aspect_ratio;
	//ray->direction.y = (1 - 2 * coord[dy] / scene->resy) * half_screen;
	//ray->direction.z = -1.0;	
	ray->direction.x = (2 * x / WIDTH - 1) * half_screen
	* aspect_ratio;
	ray->direction.y = (1 - 2 * y / HEIGHT) * half_screen;
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

void	raytrace(t_scene *scene, t_mlx *mlx_cfg)
{
	int		coord[2];
	t_ray	ray;
	double	half_screen;
	t_vect	pix_rgb;

	printf("scene sizex : %d\n", scene->resx);
	printf("scene sizey : %d\n", scene->resy);
	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	coord[dx] = 0;
	while (coord[dx] < scene->resx)
//	while (coord[dx] < WIDTH)
	{
		coord[dy] = 0;
		while (coord[dy] < scene->resy)
	//	while (coord[dy] < HEIGHT)
		{
			define_ray(&ray, half_screen, coord, scene);
			pix_rgb = send_ray(scene, &ray);	
			apply_color(&pix_rgb, mlx_cfg, coord[dx], coord[dy]); 
			coord[dy]++;
		}
		coord[dx]++;
	}
}
