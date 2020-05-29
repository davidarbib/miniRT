/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:55:19 by darbib            #+#    #+#             */
/*   Updated: 2020/05/27 18:08:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SPHERE_H
# define SPHERE_H

# include "vector.h"
# include "minirt.h"

/*
** --- sphere ---
** pos : position vector
** diam : sphere diameter
** rgb : rgb color
*/
typedef struct		s_sphere
{
	t_vect			pos;
	t_vect			current_pos;
	double			diam;
	unsigned char	rgb[3];
}					t_sphere;

void	destroy_sphere(void *obj);
void	print_sphere(void *obj);

#endif
