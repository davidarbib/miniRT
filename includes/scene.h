/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 14:31:09 by darbib            #+#    #+#             */
/*   Updated: 2020/05/19 18:51:01 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "aabb.h"
# include "plane.h"
# include "square.h"
# include "triangle.h"
# include "cylinder.h"
# include "sphere.h"
# include "omnilight.h"
# include "camera.h"

typedef struct	s_scene
{
	t_vect			*ref_orient;
	t_aabb			*aabbs;
	t_plane			*planes;
	t_square		*squares;
	t_trig			*triangles;
	t_cyld			*cylinders;
	t_sphere		*spheres;
	t_olight		*olights;
	t_cam			*cams;
	t_cam			*active_cam;
	int				aabb_n;
	int				planes_n;
	int				squares_n;
	int				triangles_n;
	int				cylinders_n;
	int				spheres_n;
	int				olights_n;
	int				cams_n;
	unsigned char	background_rgb[3]; 
	int				resx;
	int				resy;
	double			rot_quater[4];
	double			conjugate_rot_quater[4];
	double			theta;
	double			phi;
}				t_scene;

void			adapt_scene(t_scene *scene);


void			move_scene(t_scene *scene, t_vect *translation);
#endif
