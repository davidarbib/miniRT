/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/02 00:18:30 by darbib            #+#    #+#             */
/*   Updated: 2020/08/04 19:10:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "quaternion.h"

void	add_quater(double *q1, double *q2, double *q_out)
{
	q_out[A] = q1[A] + q2[A];
	q_out[B] = q1[B] + q2[B];
	q_out[C] = q1[C] + q2[C];
	q_out[D] = q1[D] + q2[D];
}

void	mult_quater(double *q1, double *q2, double *q_out)
{
	q_out[A] = q1[A] * q2[A] - q1[B] * q2[B] - q1[C] * q2[C] - q1[D] * q2[D];
	q_out[B] = q1[A] * q2[B] + q1[B] * q2[A] + q1[C] * q2[D] - q1[D] * q2[C];
	q_out[C] = q1[A] * q2[C] + q1[C] * q2[A] - q1[B] * q2[D] + q1[D] * q2[B];
	q_out[D] = q1[D] * q2[A] + q1[A] * q2[D] + q1[B] * q2[C] - q1[C] * q2[B];
}

void	conjugate_quater(double *q, double *q_conjugate)
{
	q_conjugate[A] = q[A];
	q_conjugate[B] = q[B] * -1.;
	q_conjugate[C] = q[C] * -1.;
	q_conjugate[D] = q[D] * -1.;
}

void	to_quater(t_vect *point, double *q_out)
{
	q_out[A] = 0.;
	q_out[B] = point->x;
	q_out[C] = point->y;
	q_out[D] = point->z;
}

void	to_point(double *q, t_vect *point)
{
	 point->x = q[B];
	 point->y = q[C];
	 point->z = q[D];
}
