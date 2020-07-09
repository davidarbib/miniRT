/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_hit_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 14:48:42 by darbib            #+#    #+#             */
/*   Updated: 2020/07/09 16:36:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"

void	get_hit_plane(t_near *near, t_ray ray)
{
	t_plane *plane;

	plane = (t_plane *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	near->normal = plane->current_orient;
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_triangle(t_near *near, t_ray ray)
{
	t_trig *triangle;

	triangle = (t_trig *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	cross(&triangle->current_edge1, &triangle->current_edge2, &near->normal);
	normalize(&near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_square(t_near *near, t_ray ray)
{
	t_square *square;

	square = (t_square *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	near->normal = square->current_orient;
	get_obj_rgb(near->obj, near->type, near->rgb); 
}

void	get_hit_sphere(t_near *near, t_ray ray)
{
	t_sphere *sphere;

	sphere = (t_sphere *)near->obj;
	get_hit_point(near->t, ray.direction, ray.origin, &near->hit);
	sub_vect(&near->hit, &sphere->current_pos, &near->normal);
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
	normalize(&near->normal, &near->normal);
	get_obj_rgb(near->obj, near->type, near->rgb); 
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

int main()
{
	t_cylinder cyl;
	t_trig		trig;
	t_near near;
	t_ray ray;
	t_vect test;

	near.obj = &cyl;
	cyl.current_pos = (t_vect) {0., 0., -2.};
	cyl.current_orient = (t_vect) {1., 0., 0.};
	cyl.radius = 2;
	ray.origin = (t_vect) {0., 0., 0.};
	ray.direction = (t_vect) {0., 0., -1.};
	near.t = intersect_cylinder(cyl, ray);
	printf("t : %lf\n", near.t);
	get_hit_cylinder(&near, ray);
	printf("cylinder normal at P : \n");
	print_vect(&near.normal);

	near.obj = &trig;
	trig.current_pt1 = (t_vect) {-1., -1., -1.};
	trig.current_pt2 = (t_vect) {1., -1., -1.};
	trig.current_pt3 = (t_vect) {0., 1., -1.};
	sub_vect(&trig.current_pt2, &trig.current_pt1, &trig.current_edge1);
	sub_vect(&trig.current_pt3, &trig.current_pt1, &trig.current_edge2);
	near.t = intersect_triangle(trig, ray);
	printf("t : %lf\n", near.t);
	get_hit_triangle(&near, ray);
	printf("triangle normal at P : \n");
	print_vect(&near.normal);
	print_vect(&trig.current_edge1);
	print_vect(&trig.current_edge2);
	cross(&trig.current_edge1, &trig.current_edge2, &test);
	print_vect(&test);
}
