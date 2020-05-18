/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:08:02 by darbib            #+#    #+#             */
/*   Updated: 2020/05/16 15:24:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYTRACE_H
# define RAYTRACE_H

# include "scene.h"
# include "graphic.h"
# include "aabb.h"
# include "plane.h"
# include <math.h>

# define EPSILON	0.000001

typedef struct	s_ray
{
	t_vect			*origin;
	t_vect			*direction;
	t_vect			*inv_direction;
	int				sign[3];
}				t_ray;

void	raytrace(t_scene *scene, t_mlx *mlx_cfg);
int		intersect_plane(t_plane *plane, t_ray *ray);
int		intersect_aabb(t_aabb *aabb, t_ray *ray);
#endif
