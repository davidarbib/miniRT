/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 21:59:50 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:02:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "rotation.h"
#include <math.h>

t_vect		light_on_obj(t_vect *light, unsigned char *obj_rgb)
{
	t_vect	obj_color;

	obj_color.x = obj_rgb[r] / 255. * fmin(light->x, 1.0);
	obj_color.y = obj_rgb[g] / 255. * fmin(light->y, 1.0);
	obj_color.z = obj_rgb[b] / 255. * fmin(light->z, 1.0);
	return (obj_color);
}

void		colorize_pixels(t_vect pix_rgb, t_mlx *cfg, int *beginc, int *endc)
{
	int x;
	int y;

	x = beginc[dx];
	while (x < endc[dx])
	{
		y = beginc[dy];
		while (y < endc[dy])
		{
			apply_color(&pix_rgb, cfg, x, y);
			y++;
		}
		x++;
	}
}

void		raytrace_lowres(t_scene *scene, t_mlx *cfg)
{
	int		begincoord[2];
	int		endcoord[2];
	t_ray	ray;
	double	half_screen;
	t_vect	pix_rgb;

	half_screen = tan(to_radian(scene->active_cam->fov * 0.5));
	begincoord[dx] = 0;
	endcoord[dx] = LOWFACTOR;
	while (begincoord[dx] < scene->resx)
	{
		begincoord[dy] = 0;
		endcoord[dy] = LOWFACTOR;
		while (begincoord[dy] < scene->resy)
		{
			define_ray(&ray, half_screen, begincoord, scene);
			pix_rgb = send_ray(scene, &ray);
			colorize_pixels(pix_rgb, cfg, begincoord, endcoord);
			begincoord[dy] += LOWFACTOR;
			endcoord[dy] += LOWFACTOR;
		}
		begincoord[dx] += LOWFACTOR;
		endcoord[dx] += LOWFACTOR;
	}
}

void		get_obj_rgb(void *obj, enum e_type type, unsigned char *rgb)
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
		ft_memmove(rgb, ((t_cylinder *)obj)->rgb, 3);
}

void		browse_scene(t_scene *scene, t_ray *ray, t_near *near)
{
	ray->current_type = plane;
	loop_intersect_planes(scene->planes, scene->planes_n, ray, near);
	ray->current_type = triangle;
	loop_intersect_triangles(scene->triangles, scene->triangles_n, ray, near);
	ray->current_type = sphere;
	loop_intersect_spheres(scene->spheres, scene->spheres_n, ray, near);
	ray->current_type = square;
	loop_intersect_squares(scene->squares, scene->squares_n, ray, near);
	ray->current_type = cylinder;
	loop_intersect_cylinders(scene->cylinders, scene->cylinders_n, ray, near);
}
