/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:48:42 by darbib            #+#    #+#             */
/*   Updated: 2020/07/08 18:42:56 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"

void	get_hit_plane(t_near *near, t_ray ray)
{
	t_plane *plane;

	plane = (t_plane *)near->obj;
	get_hit_point(&near->t, ray.direction, ray.origin, near->hit);
	near->normal = plane->current_orient;
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_triangle(t_near *near, t_ray ray)
{
	t_trig *triangle;

	triangle = (t_trig *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, near->hit);
	near->normal = triangle->current_orient;
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_square(t_near *near, t_ray ray)
{
	t_square *square;

	square = (t_square *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, near->hit);
	near->normal = square->current_orient;
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_sphere(t_near *near, t_ray ray)
{
	t_sphere *sphere;

	sphere = (t_sphere *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, near->hit);
	sub_vect(near->hit, sphere->current_orient, near->normal);
	normalize(near->normal, near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_cylinder(t_near *near, t_ray ray)
{
	t_cylinder *cylinder;
	t_vect		hit_bc;
	t_vect		proj_hit_on_a;
	t_vect		a;

	cylinder = (t_cylinder *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, near->hit);
	sub_vect(&near->hit, &cylinder->current_pos, &hit_bc);
	a = cylinder->current_orient;
	scale(dot(hit_bc, a) / dot(a, a), a, proj_hit_on_a);	
	sub_vect(&near->hit, &proj_hit_on_a, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

double intersect_cylinder(t_cylinder cylinder, t_ray ray)
{
	double	var[6];
	t_vect	bc_min_br;
	t_vect	r_x_a;
	t_vect	tmp_v;
	
	cross(&ray.direction, &cylinder.current_orient, &r_x_a);
	if (is_null_vect(r_x_a))
		return (0);
	sub_vect(&cylinder.current_pos, &ray.origin, &bc_min_br);
	var[len_rxa] = vect_norm(&r_x_a);
	normalize(&r_x_a, &r_x_a);
	var[dc] = ft_double_abs(dot(&bc_min_br, &r_x_a));
	if (var[dc] > cylinder.diam / 2)
		return (0);
	cross(&bc_min_br, &cylinder.current_orient, &tmp_v);
	var[tc] = dot(&tmp_v, &r_x_a) / var[len_rxa];
	cross(&r_x_a, &cylinder.current_orient, &tmp_v);
	var[s] = ft_double_abs(sqrt((cylinder.radius) * (cylinder.radius) 
			- var[dc] * var[dc]) / dot(&ray.direction, &tmp_v));
	var[t1c] = var[tc] - var[s];
	var[t2c] = var[tc] + var[s];
	if (var[t1c] > EPSILON)
		return (var[t1c]);
	return (var[t2c]);
}

int main()
{
	t_cylinder cyl;
	t_near near;
	t_ray ray;

	near.obj = &cyl;
	cyl.current_pos = (t_vect) {0., 0., -2.};
	cyl.current_orient = (t_vect) {1., 0., 0.};
	cyl.radius = 2;
	ray.origin = (t_vect) {0., 0., 0.};
	ray.direction = (t_vect) {0., 0., -1.};
	near.t = intersect_cylinder(cyl, ray);
	get_hit_cylinder(&near, ray);
	printf("normal at P : \n");
	print_vect(near.normal);
}
