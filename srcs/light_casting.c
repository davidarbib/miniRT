/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_casting.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 16:34:41 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:01:12 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

extern t_olight *g_light_ptr;

static int		light_cast2(t_scene *scene, t_ray *ray, t_shadow *sh)
{
	int n;

	n = -1;
	while (++n < scene->planes_n)
	{
		sh->t = intersect_plane(scene->planes[n], *ray);
		if (sh->t > EPSILON && (sh->t + EPSILON) < sh->t_light)
			return (1);
	}
	n = -1;
	while (++n < scene->squares_n)
	{
		sh->t = intersect_square(scene->squares[n], *ray);
		if (sh->t > EPSILON && (sh->t + EPSILON) < sh->t_light)
			return (1);
	}
	n = -1;
	while (++n < scene->triangles_n)
	{
		sh->t = intersect_triangle(scene->triangles[n], *ray);
		if (sh->t > EPSILON && (sh->t + EPSILON) < sh->t_light)
			return (1);
	}
	return (0);
}

int				light_cast(t_scene *scene, t_ray *ray, t_shadow *sh)
{
	int n;

	sh->t = -1.;
	if (light_cast2(scene, ray, sh))
		return (1);
	n = -1;
	while (++n < scene->spheres_n)
	{
		sh->t = intersect_sphere(scene->spheres[n], *ray);
		if (sh->t > EPSILON && (sh->t + EPSILON) < sh->t_light)
			return (1);
	}
	n = -1;
	while (++n < scene->cylinders_n)
	{
		sh->t = intersect_cylinder(scene->cylinders[n], *ray);
		if (sh->t > EPSILON && (sh->t + EPSILON) < sh->t_light)
			return (1);
	}
	return (0);
}
