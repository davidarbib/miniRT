/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 15:55:19 by darbib            #+#    #+#             */
/*   Updated: 2020/03/10 11:56:38 by darbib           ###   ########.fr       */
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
	t_vect			*pos;
	double			diam;
	unsigned char	rgb[3];
}					t_sphere;

void	parse_sphere(t_rt *cfg, char *line);
void	destroy_sphere(void *obj);
void	print_sphere(void *obj);

#endif
