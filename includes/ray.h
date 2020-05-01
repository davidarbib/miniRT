/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:46:59 by darbib            #+#    #+#             */
/*   Updated: 2020/04/30 20:48:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_H
# define RAY_H

#include "vector.h"

typedef struct	s_ray
{
	t_vect			*origin;
	t_vect			*direction;
	t_vect			*inv_direction;
	int				sign[3];
}				t_ray;

#endif
