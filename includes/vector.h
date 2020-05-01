/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 15:03:37 by darbib            #+#    #+#             */
/*   Updated: 2020/05/01 21:10:18 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_H
# define VECTOR_H

typedef struct		s_vect
{
	double			x;
	double			y;
	double			z;
}					t_vect;


void	ortho_projection(t_vect *v_initial, t_vect *v_support, t_vect *v_out);
void	sub_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out);
void	add_vect(t_vect *vect1, t_vect *vect2, t_vect *vect_out);
void	normalize(t_vect *vect, t_vect *vect_out);
double	vect_norm(t_vect *vect);
double	dot(t_vect *vect1, t_vect *vect2);
void	cross(t_vect *vect1, t_vect *vect2, t_vect *vect_out);
void	scale(double scalar, t_vect *vect, t_vect *vect_out);

#endif
