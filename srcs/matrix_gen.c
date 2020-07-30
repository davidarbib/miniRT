/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_gen.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/30 14:10:20 by darbib            #+#    #+#             */
/*   Updated: 2020/07/30 15:23:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix.h"
#include <math.h>
#include "print.h"


void	x_matrix(double theta, double *m)
{
	printf("theta x = %lf\n", to_degree(theta));
	double costheta;
	double sintheta;
	
	costheta = cos(theta);
	sintheta = sin(theta);
	m[0] = 1; 
	m[1] = 0; 
	m[2] = 0; 
	m[3] = 0; 
	m[4] = costheta;
	m[5] = -sintheta; 
	m[6] = 0;
	m[7] = sintheta;
	m[8] = costheta;
}

void	y_matrix(double theta, double *m)
{
	printf("theta y = %lf\n", to_degree(theta));
	double costheta;
	double sintheta;
	
	costheta = cos(theta);
	sintheta = sin(theta);
	m[0] = costheta;
	m[1] = 0; 
	m[2] = sintheta;
	m[3] = 0; 
	m[4] = 1; 
	m[5] = 0; 
	m[6] = -sintheta; 
	m[7] = 0;
	m[8] = costheta;
}

void	z_matrix(double theta, double *m)
{
	printf("theta z = %lf\n", to_degree(theta));
	double costheta;
	double sintheta;
	
	costheta = cos(theta);
	sintheta = sin(theta);
	m[0] = costheta;
	m[1] = -sintheta; 
	m[2] = 0; 
	m[3] = sintheta;
	m[4] = costheta;
	m[5] = 0; 
	m[6] = 0; 
	m[7] = 0;
	m[8] = 1; 
}
