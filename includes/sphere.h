/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:55:19 by darbib            #+#    #+#             */
/*   Updated: 2020/02/28 15:07:43 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vector.h"
/*
** --- sphere ---
** pos : position vector
** diam : sphere diameter
** rgb : rgb color
*/
typedef struct		s_sphere
{
	t_vect			*pos;
	float			diam;
	unsigned char	rgb[3];
}					t_sphere;

#endif
