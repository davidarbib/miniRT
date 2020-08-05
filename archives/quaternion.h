/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:48:56 by darbib            #+#    #+#             */
/*   Updated: 2020/05/03 12:37:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUATERNION_H
# define QUATERNION_H

#include "vector.h"

#define A 0
#define B 1
#define C 2
#define D 3

void	add_quater(double *q1, double *q2, double *q_out);
void	mult_quater(double *q1, double *q2, double *q_out);
void	conjugate_quater(double *q, double *q_conjugate);
void	to_quater(t_vect *point, double *q_out);
void	to_point(double *q, t_vect *point);
#endif

