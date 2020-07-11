/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:48:42 by darbib            #+#    #+#             */
/*   Updated: 2020/07/11 01:41:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	get_hit_plane(t_near *near, t_ray ray)
{
	t_plane *plane;

	plane = (t_plane *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	near->normal = plane->current_orient;
	if (dot(&ray.direction, &near->normal) > 0)
		scale(-1, &near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_triangle(t_near *near, t_ray ray)
{
	t_trig *triangle;

	triangle = (t_trig *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	cross(&triangle->current_edge1, &triangle->current_edge2, &near->normal);
	if (dot(&ray.direction, &near->normal) > 0)
		scale(-1, &near->normal, &near->normal);
	normalize(&near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_square(t_near *near, t_ray ray)
{
	t_square *square;

	square = (t_square *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	near->normal = square->current_orient;
	if (dot(&ray.direction, &near->normal) > 0)
		scale(-1, &near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_sphere(t_near *near, t_ray ray)
{
	t_sphere *sphere;

	sphere = (t_sphere *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	sub_vect(&near->hit, &sphere->current_pos, &near->normal);
	if (dot(&ray.direction, &near->normal) > 0)
		scale(-1, &near->normal, &near->normal);
	normalize(&near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_cylinder(t_near *near, t_ray ray)
{
	t_cylinder *cylinder;
	t_vect		hit_bc;
	t_vect		proj_hit_on_a;
	t_vect		a;

	cylinder = (t_cylinder *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	sub_vect(&near->hit, &cylinder->current_pos, &hit_bc);
	a = cylinder->current_orient;
	scale(dot(&hit_bc, &a) / dot(&a, &a), &a, &proj_hit_on_a);	
	sub_vect(&near->hit, &proj_hit_on_a, &near->normal);
	if (dot(&ray.direction, &near->normal) > 0)
		scale(-1, &near->normal, &near->normal);
	normalize(&near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}
