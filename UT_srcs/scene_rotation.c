/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_rotation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:25:44 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 13:45:11 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "print.h"
#include "matrix.h"
#include <stdio.h>

static void	to_spherical(t_vect *cartesian, t_spheric *spherical)
{
	double rho;

	rho = vect_norm(cartesian);
	spherical->rho = rho; 
	spherical->phi = acos(cartesian->z / rho);  
	spherical->theta = atan2(cartesian->y, cartesian->x);
}

void		to_cartesian(t_spheric *spherical, t_vect *cartesian)
{
	cartesian->x = spherical->rho * sin(spherical->phi) * cos(spherical->theta); 	
	cartesian->y = spherical->rho * sin(spherical->phi) * sin(spherical->theta); 	
	cartesian->z = spherical->rho * cos(spherical->phi); 	
}

static void	get_inv_f_matrix(double dot_ab, t_vect *a, t_vect *b, double *inv_f)
{
	t_vect baba;
	t_vect aba;
	t_vect cross_ba;

	scale(dot_ab, a, &aba);
	sub_vect(b, &aba, &baba);
	normalize(&baba, &baba);
	cross(b, a, &cross_ba);
	inv_f[0] = a->x;
	inv_f[1] = baba.x;
	inv_f[2] = cross_ba.x;
	inv_f[3] = a->y;
	inv_f[4] = baba.y;
	inv_f[5] = cross_ba.y;
	inv_f[6] = a->z;
	inv_f[7] = baba.z;
	inv_f[8] = cross_ba.z;
}

void	extract_scene_rotation(t_vect *cam_orient, t_vect *ref_orient,
		double *rot_matrix)
{
	t_vect normal;
	double g_matrix[9];
	double f_matrix[9];
	double inv_f_matrix[9];
	double tmp_matrix[9];

	cross(cam_orient, ref_orient, &normal);
	g_matrix[0] = dot(cam_orient, ref_orient); 
	g_matrix[1] = -vect_norm(&normal); 
	g_matrix[2] = 0; 
	g_matrix[3] = -g_matrix[1]; 
	g_matrix[4] = g_matrix[0]; 
	g_matrix[5] = 0; 
	g_matrix[6] = 0; 
	g_matrix[7] = 0; 
	g_matrix[8] = 1;

	printf("----------g_matrix------------\n");
	print_matrix(g_matrix);
	printf("-----------------------------\n");
	get_inv_f_matrix(g_matrix[0], cam_orient, ref_orient, inv_f_matrix);
	inverse(inv_f_matrix, f_matrix);
	printf("----------f_matrix------------\n");
	print_matrix(f_matrix);
	printf("-----------------------------\n");
	printf("----------inv_f_matrix------------\n");
	print_matrix(inv_f_matrix);
	printf("-----------------------------\n");
	//matrix_product(inv_f_matrix, g_matrix, tmp_matrix);
	//matrix_product(tmp_matrix, f_matrix, rot_matrix);
//	matrix_product(g_matrix, f_matrix, tmp_matrix);
//	matrix_product(inv_f_matrix, tmp_matrix, rot_matrix);
	matrix_product(f_matrix, g_matrix, tmp_matrix);
	matrix_product(tmp_matrix, inv_f_matrix, rot_matrix);
}

void		rotate_point(double phi, double theta, t_vect *v_in, t_vect *v_out)
{
	t_spheric spherical_in;

	if (!vect_norm(v_in))
	{
		v_out->x = v_in->x; 
		v_out->y = v_in->y; 
		v_out->z = v_in->z; 
	}
	else
	{
		to_spherical(v_in, &spherical_in);
		spherical_in.phi += phi;
		spherical_in.theta += theta;
		to_cartesian(&spherical_in, v_out);
	}
}

int main()
{
	t_vect v;
	t_vect ref;
	t_vect pt;
	t_vect res;
	double matrix[9];

	v.x = 1;
	v.y = 0;
	v.z = 0;
	ref.x = 0;
	ref.y = 0;
	ref.z = -1;
	extract_scene_rotation(&v, &ref, matrix);
	printf("---------\n");
	print_matrix(matrix);
	pt.x = 0;
	pt.y = -1;
	pt.z = 0;
	matrix_by_vect(matrix, &pt, &res);
	printf("---------\n");
	print_vect(&res);
	/*
	print_vect(&v);
	rotate_point(to_radian(90), 0, &v, &v);
	print_vect(&v);
	rotate_point(0, to_radian(90), &v, &v);
	print_vect(&v);
	*/
	return (0);
}
