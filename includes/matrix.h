/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/27 17:04:10 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 14:58:35 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

# include "vector.h"
# include <math.h>

# define DN 3

void			matrix_by_vect(double *m, t_vect *v_in, t_vect *v_out);
void			matrix_product(double *m1, double *m2, double *m_out);
void			inverse(double *m_in, double *m_out);
void			x_matrix(double theta, double *m);
void			y_matrix(double theta, double *m);
void			z_matrix(double theta, double *m);

#endif
