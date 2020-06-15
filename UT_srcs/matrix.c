/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 16:45:28 by darbib            #+#    #+#             */
/*   Updated: 2020/06/15 16:24:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include "vector.h"
#include "print.h"

static double	get_object_value(double *m1, double *m2, int i, int j)
{
	int z;
	double sum;
	
	sum = 0;
	z = 0;
	while (z < DN)
	{
		sum += m1[z + DN * j] * m2[i + DN * z];
		z++;
	}
	return (sum);	
}

void			matrix_product(double *m1, double *m2, double *m_out)
{
	int i;
	int j;
	
	j = 0;
	while (j < DN)
	{
		i = 0;
		while (i < DN)
		{
			m_out[i + j * DN] = get_object_value(m1, m2, i, j);
			i++;
		}
		j++;
	}
}

void			matrix_by_vect(double *m, t_vect *v_in, t_vect *v_out)
{
	v_out->x = v_in->x * m[0] + v_in->y * m[1] + v_in->z * m[2];
	v_out->y = v_in->x * m[3] + v_in->y * m[4] + v_in->z * m[5];
	v_out->z = v_in->x * m[6] + v_in->y * m[7] + v_in->z * m[8];
}

void	rotate_point(double *matrix, t_vect *v_in, t_vect *v_out)
{
	if (!vect_norm(v_in))
	{
		v_out->x = v_in->x; 
		v_out->y = v_in->y; 
		v_out->z = v_in->z; 
	}
	else
		matrix_by_vect(matrix, v_in, v_out);
}

void			print_matrix(double *m)
{
	int i;
	int j;
	
	j = 0;
	while (j < DN)
	{
		i = 0;
		while (i < DN)
		{
			printf("%lf ", m[i + DN * j]);
			i++;
		}
		j++;
		printf("\n");
	}
}

int main()
{
	double costheta; 
	double sintheta; 
	double right[9];
	
#define ANGLE_SIZE 90
	costheta = cos(to_radian(ANGLE_SIZE));
	sintheta = sin(to_radian(ANGLE_SIZE));
	right[0] = costheta;
	right[1] = 0;
	right[2] = -sintheta;
	right[3] = 0;
	right[4] = 1;
	right[5] = 0;
	right[6] = sintheta;
	right[7] = 0;
	right[8] = costheta;
	//double m1[DN * DN] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
	//double m2[DN * DN] = {2, 4, 8, 11, 9, 3, 1, 3, 5};
	//double m_out[DN * DN];
	t_vect v_in = (t_vect){.x=0, .y=0, .z=-2};
	t_vect v_out;
	print_matrix(right);
	printf("\n");
	print_vect(&v_in);
	printf("----------------------\n");
/*
	matrix_product(m2, m1, m_out);	
*/
	matrix_by_vect(right, &v_in, &v_out);
	print_vect(&v_out);
}
