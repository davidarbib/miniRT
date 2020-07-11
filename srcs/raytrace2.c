/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/10 21:59:50 by darbib            #+#    #+#             */
/*   Updated: 2020/07/11 01:36:54 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "minirt.h"
#include "raytrace.h"
#include <assert.h>
#include "print.h"
#include "rotation.h"
#include <math.h>

void	light_on_obj(t_vect *light, unsigned char *obj_rgb)
{
	obj_rgb[r] = floor(obj_rgb[r] * light->x);
	obj_rgb[g] = floor(obj_rgb[g] * light->y);
	obj_rgb[b] = floor(obj_rgb[b] * light->z);
}

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
		ft_memmove(rgb, ((t_cylinder *)obj)->rgb, 3);
}

void browse_scene(t_scene *scene, t_ray *ray, t_near *near)
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
