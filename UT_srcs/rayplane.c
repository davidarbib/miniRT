/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rayplane.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/23 14:47:38 by darbib            #+#    #+#             */
/*   Updated: 2020/07/13 15:46:52 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raytrace.h"
#include "print.h"
#include "assert.h"

void	get_ray_point(double t, t_ray ray, t_vect *v_out)
{
	t_vect tmp;
	scale(t, &ray.direction, &tmp);
	add_vect(&tmp, &ray.origin, v_out);
}

double	intersect_plane(t_plane plane, t_ray ray)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	denom = dot(&ray.direction, &plane.current_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&plane.current_pos, &ray.origin, &tmp_v);
		t = dot(&tmp_v, &plane.current_orient) / denom;
		if (t >= EPSILON)
			return (t);
	}
	return (0);
}

/*
double	intersect_square(t_square square, t_ray ray)
{
	t_plane	plane;
	double	t;
	double	proj1;
	double	proj2;
	t_vect	v;
	
	plane.current_pos = square.current_pos;
	plane.current_orient = square.current_orient;	
	if (!(t = intersect_plane(plane, ray)))
		return (0);
	get_ray_point(t, ray, &v);
	//printf("v : \n");
	print_vect(&v);
	sub_vect(&v, &square.current_pos, &v);
	normalize(&square.edge1, &square.edge1);
	normalize(&square.edge2, &square.edge2);
	//proj1 = vect_norm(&v) * dot(&v, &square.edge1);
	//proj2 = vect_norm(&v) * dot(&v, &square.edge2);
	proj1 = dot(&v, &square.edge1);
	proj2 = dot(&v, &square.edge2);
	if ((proj1 < square.height && proj1 > 0) 
		&& (proj2 < square.height && proj2 > 0))
		return (t);
	return (0);
}
int		intersect_plane(t_vect plane_pos, t_vect plane_orient,
		t_vect ray_origin, t_vect ray_direction)
{
	double	denom;
	double	t;
	t_vect	tmp_v; 

	normalize(&plane_pos, &plane_pos);
	normalize(&ray_origin, &ray_origin);
	normalize(&ray_direction, &ray_direction);
	denom = dot(&ray_direction, &plane_orient);	
	if (ft_double_abs(denom) > EPSILON)
	{
		sub_vect(&plane_pos, &ray_origin, &tmp_v);
		t = dot(&tmp_v, &plane_orient) / denom;
		return (t >= EPSILON);
	}
	return (0);
}
*/
/*
** Moller-Trumbore algorithm implementation
** original triangle vertices used to store the three tmp vectors
** (its why we need a triangle copy)
** t, u, v are barycentric coordinates
*/
/*
int		intersect_triangle(t_ray *ray, t_trig triangle)
{	
	double	det;
	double	inv_det;
	double 	barycoord[2];
	double	t;
	t_vect	tmp[3];
	printf("----pts triangles -----\n");
	print_vect(&triangle.current_pt1);
	print_vect(&triangle.current_pt2);
	print_vect(&triangle.current_pt3);
	print_vect(&triangle.current_edge1);
	print_vect(&triangle.current_edge2);
	print_vect(&ray->direction);
	printf("-----------------------\n");
	cross(&ray->direction, &triangle.current_edge2, &tmp[PVEC]);
	det = dot(&triangle.current_edge1, &tmp[PVEC]);
	//if (det < EPSILON)
	if (det > (EPSILON * -1) && det < EPSILON)
		return (0);
	inv_det = 1.0 / det;
	sub_vect(&ray->origin, &triangle.current_pt1, &tmp[TVEC]);
	barycoord[U] = inv_det * dot(&tmp[TVEC], &tmp[PVEC]);
	//barycoord[U] = dot(&tmp[TVEC], &tmp[PVEC]);
	if (barycoord[U] < 0.0 || barycoord[U] > 1.0)
	//if (barycoord[U] < 0.0 || barycoord[U] > det)
		return (0);
	cross(&tmp[TVEC], &triangle.current_edge1, &tmp[QVEC]);
	barycoord[V] = inv_det * dot(&ray->direction, &tmp[QVEC]);
	//barycoord[V] = dot(&ray->direction, &tmp[QVEC]);
	printf("------------------------\n");
	printf("(u, v) = (%lf, %lf)\n", barycoord[U], barycoord[V]);
	printf("det = %lf\n", det);
	printf("pvec = \n");
	print_vect(&tmp[PVEC]);
	printf("tvec = \n");
	print_vect(&tmp[TVEC]);
	printf("qvec = \n");
	print_vect(&tmp[QVEC]);
	if (barycoord[V] < 0.0 || barycoord[U] + barycoord[V] > 1.0)
	//if (barycoord[V] < 0.0 || barycoord[U] + barycoord[V] > det)
		return (0);
	t = inv_det * dot(&triangle.current_edge2, &tmp[QVEC]);
	if (t > EPSILON)
		return (t);
	return (0);
}
*/

int main()
{
	t_plane plane;
	t_ray	ray;
	
	ray.origin = (t_vect){0, 0, 0};
	ray.direction = (t_vect){0, 0, -1};
	plane.current_pos = (t_vect){0, 0, 0};
	plane.current_orient = (t_vect){0, 0, -1};
	printf("t = %lf\n", intersect_plane(plane, ray));
	plane.current_pos = (t_vect){0, 0, -4};
	printf("t = %lf\n", intersect_plane(plane, ray));
	plane.current_pos = (t_vect){0, 0, 4};
	printf("t = %lf\n", intersect_plane(plane, ray));
/*
	t_ray ray;
	t_square square;
	//double t = 0.;

	ray.origin = (t_vect) {0, 0, 0};
	ray.direction = (t_vect) {0, 0, -1};
	square.current_pos = (t_vect) {-1, -1, -1};
	square.current_orient = (t_vect) {0, 0, -1};
	square.edge1 = (t_vect){1, 0, 0};
	square.edge2 = (t_vect){0, 1, 0};
	square.height = 3;
	printf("t = %lf\n", intersect_square(square, ray));

	ray.origin = (t_vect) {6, 0, 0};
	printf("t = %lf\n", intersect_square(square, ray));

	ray.origin = (t_vect) {2., 0, 0};
	printf("t = %lf\n", intersect_square(square, ray));

	ray.origin = (t_vect) {0, 1., 0};
	printf("t = %lf\n", intersect_square(square, ray));

	ray.origin = (t_vect) {0, 2., 0};
	printf("t = %lf\n", intersect_square(square, ray));

	ray.origin = (t_vect) {0, 1, 5};
	printf("t = %lf\n", intersect_square(square, ray));

	t_vect v1;
	double t = 2;
	get_ray_point(t, ray, &v1);
	printf("v_out : \n");
	print_vect(&v1);
	t_ray ray;
	t_trig triangle;

	ray.origin.x = 0.;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	ray.direction.x = 0.; 
	ray.direction.y = 0.; 
	ray.direction.z = -1.;	
	triangle.current_pt1.x = -1.;
	triangle.current_pt1.y = -1.;
	triangle.current_pt1.z = -1.;
	triangle.current_pt2.x = 1.;
	triangle.current_pt2.y = -1.;
	triangle.current_pt2.z = -1.;
	triangle.current_pt3.x = 0.;
	triangle.current_pt3.y = 1.;
	triangle.current_pt3.z = -1.;
	sub_vect(&triangle.current_pt2, &triangle.current_pt1, &triangle.current_edge1);
	sub_vect(&triangle.current_pt3, &triangle.current_pt1, &triangle.current_edge2);
	printf("intersection 0: %d\n", intersect_triangle(&ray, triangle));
	//1)
	ray.origin.x = -0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 1: %d\n", intersect_triangle(&ray, triangle));
	//2)
	ray.origin.x = -0.25;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 2: %d\n", intersect_triangle(&ray, triangle));
	//3)
	ray.origin.x = 0.;
	ray.origin.y = -0.75;
	ray.origin.z = 0.;
	printf("intersection 3: %d\n", intersect_triangle(&ray, triangle));
	//4)
	ray.origin.x = 0.;
	ray.origin.y = -1.25;
	ray.origin.z = 0.;
	printf("intersection 4: %d\n", intersect_triangle(&ray, triangle));
	//5)
	ray.origin.x = 0.25;
	ray.origin.y = -0.25;
	ray.origin.z = 0.;
	printf("intersection 5: %d\n", intersect_triangle(&ray, triangle));
	//6)
	ray.origin.x = 0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 6: %d\n", intersect_triangle(&ray, triangle));
	//7)
	ray.origin.x = -0.75;
	ray.origin.y = 0.;
	ray.origin.z = 1.;
	printf("intersection 7: %d\n", intersect_triangle(&ray, triangle));
	//8)
	ray.origin.x = -0.25;
	ray.origin.y = 0.;
	ray.origin.z = 1.;
	printf("intersection 8: %d\n", intersect_triangle(&ray, triangle));
	//9)
	ray.origin.x = 0.;
	ray.origin.y = -0.75;
	ray.origin.z = 1.;
	printf("intersection 9: %d\n", intersect_triangle(&ray, triangle));
	//10)
	ray.origin.x = 0.;
	ray.origin.y = -1.25;
	ray.origin.z = 1.;
	printf("intersection 10: %d\n", intersect_triangle(&ray, triangle));
	//11)
	ray.origin.x = 0.25;
	ray.origin.y = -0.25;
	ray.origin.z = 1.;
	printf("intersection 11: %d\n", intersect_triangle(&ray, triangle));
	//12)
	ray.origin.x = 0.75;
	ray.origin.y = 0.;
	ray.origin.z = 1.;
	printf("intersection 12: %d\n", intersect_triangle(&ray, triangle));
	//13)
	triangle.current_pt3.x = 1.;
	triangle.current_pt3.y = -1.;
	triangle.current_pt3.z = -1.;
	triangle.current_pt2.x = 0.;
	triangle.current_pt2.y = 1.;
	triangle.current_pt2.z = -1.;
	sub_vect(&triangle.current_pt2, &triangle.current_pt1, &triangle.current_edge1);
	sub_vect(&triangle.current_pt3, &triangle.current_pt1, &triangle.current_edge2);
	ray.origin.x = -0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 13: %d\n", intersect_triangle(&ray, triangle));
	//14)
	ray.origin.x = -0.25;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 14: %d\n", intersect_triangle(&ray, triangle));
	//15)
	ray.origin.x = 0.;
	ray.origin.y = -0.75;
	ray.origin.z = 0.;
	printf("intersection 15: %d\n", intersect_triangle(&ray, triangle));
	//16)
	ray.origin.x = 0.;
	ray.origin.y = -1.25;
	ray.origin.z = 0.;
	printf("intersection 16: %d\n", intersect_triangle(&ray, triangle));
	//17)
	ray.origin.x = 0.25;
	ray.origin.y = -0.25;
	ray.origin.z = 0.;
	printf("intersection 17: %d\n", intersect_triangle(&ray, triangle));
	//18)
	ray.origin.x = 0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 18: %d\n", intersect_triangle(&ray, triangle));
	//19)
	ray.origin.x = 0.;	
	ray.origin.y = 0.;	
	ray.origin.z = -2.;	
	ray.direction.x = 0.;	
	ray.direction.y = 0.;	
	ray.direction.z = 1.;	
	printf("intersection 19: %d\n", intersect_triangle(&ray, triangle));
	//20)
	ray.origin.x = 0.;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	ray.direction.x = 0.; 
	ray.direction.y = 0.; 
	ray.direction.z = -1.;	
	triangle.current_pt2.x = -1.;
	triangle.current_pt2.y = -1.;
	triangle.current_pt2.z = -1.;
	triangle.current_pt3.x = 1.;
	triangle.current_pt3.y = -1.;
	triangle.current_pt3.z = -1.;
	triangle.current_pt1.x = 0.;
	triangle.current_pt1.y = 1.;
	triangle.current_pt1.z = -1.;
	sub_vect(&triangle.current_pt2, &triangle.current_pt1, &triangle.current_edge1);
	sub_vect(&triangle.current_pt3, &triangle.current_pt1, &triangle.current_edge2);
	//21)
	ray.origin.x = -0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 21: %d\n", intersect_triangle(&ray, triangle));
	//22)
	ray.origin.x = -0.25;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 22: %d\n", intersect_triangle(&ray, triangle));
	//23)
	ray.origin.x = 0.;
	ray.origin.y = -0.75;
	ray.origin.z = 0.;
	printf("intersection 23: %d\n", intersect_triangle(&ray, triangle));
	//24)
	ray.origin.x = 0.;
	ray.origin.y = -1.25;
	ray.origin.z = 0.;
	printf("intersection 24: %d\n", intersect_triangle(&ray, triangle));
	//25)
	ray.origin.x = 0.25;
	ray.origin.y = -0.25;
	ray.origin.z = 0.;
	printf("intersection 25: %d\n", intersect_triangle(&ray, triangle));
	//26)
	ray.origin.x = 0.75;
	ray.origin.y = 0.;
	ray.origin.z = 0.;
	printf("intersection 26: %d\n", intersect_triangle(&ray, triangle));
*/
}
