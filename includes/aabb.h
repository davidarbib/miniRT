/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 19:56:13 by darbib            #+#    #+#             */
/*   Updated: 2020/04/30 20:48:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef AABB_H
# define AABB_H

#include "vector.h"
#include "ray.h"

typedef struct	s_aabb
{
	t_vect			corner[2];
	unsigned char	rgb[3];
}				t_aabb;

int		intersect_aabb(t_aabb *aabb, t_ray *ray);

#endif

