/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:48:42 by darbib            #+#    #+#             */
/*   Updated: 2020/07/15 15:46:50 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "assert.h"
#include "print.h"

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
	//t_vect		tmp;

	cylinder = (t_cylinder *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	//print_vect(&ray.origin);
	//print_vect(&ray.direction);
	//printf("t : %lf\n", near->t);
	//printf("P : \n");
	//print_vect(&near->hit);
	sub_vect(&near->hit, &cylinder->current_pos, &hit_bc);
	/*
	cross(&hit_bc, &cylinder->current_orient, &tmp);
	normalize(&tmp, &tmp);
	cross(&tmp, &cylinder->current_orient, &near->normal);
	*/
	//printf("u : \n");
	//print_vect(&hit_bc);
	a = cylinder->current_orient;
	//printf("a : \n");
	//print_vect(&a);
	scale(dot(&hit_bc, &a), &a, &proj_hit_on_a);	
	//printf("projpona : \n");
	//print_vect(&proj_hit_on_a);
	sub_vect(&hit_bc, &proj_hit_on_a, &near->normal);
	normalize(&near->normal, &near->normal);
	if (dot(&ray.direction, &near->normal) > EPSILON)
		scale(-1, &near->normal, &near->normal);
	//printf("normal : \n");
	//print_vect(&near->normal);
	/*
	assert(near->normal.x <= 0.000001 && near->normal.x >= -0.000001
			&& near->normal.y <= 0.000001 && near->normal.y >= -0.000001
			&& near->normal.z <= 1.000001 && near->normal.z >= .99999);
	*/
	get_obj_rgb(near->obj, near->type, near->rgb); 
}
