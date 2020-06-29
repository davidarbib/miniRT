/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:54:47 by darbib            #+#    #+#             */
/*   Updated: 2020/06/29 16:48:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rotation.h"
#include "parsing.h"
#include "print.h"
#include "spheric.h"
#include "matrix.h"

void	compute_triangles_edges(t_trig *triangles, int n)
{
	while (--n >= 0)
	{
		sub_vect(&triangles[n].current_pt2, &triangles[n].current_pt1,
				&triangles[n].current_edge1);
		sub_vect(&triangles[n].current_pt3, &triangles[n].current_pt1,
				&triangles[n].current_edge2);
	}
}

int		make_array(t_rt *rt, t_scene *scene)
{
	if ((scene->planes = ft_lsttotab(rt->planes, sizeof(t_plane), 
			&scene->planes_n))
		&& (scene->spheres = ft_lsttotab(rt->spheres, sizeof(t_sphere), 
			&scene->spheres_n))
		&& (scene->triangles = ft_lsttotab(rt->trigs, sizeof(t_trig), 
			&scene->triangles_n))
		&& (scene->squares = ft_lsttotab(rt->squares, sizeof(t_square), 
			&scene->squares_n))
		&& (scene->cylinders = ft_lsttotab(rt->cyls, sizeof(t_cyld), 
			&scene->cylinders_n))
		&& (scene->cams = ft_lsttotab(rt->cams, sizeof(t_cam), 
			&scene->cams_n))
		&& (scene->olights = ft_lsttotab(rt->olights, sizeof(t_olight), 
			&scene->olights_n)))
		return (1);
	return (0);
}

void	place_objs(t_scene *scene)
{
	t_vect	translation;
	t_vect	*cam_orient;
	double 	rot_matrix[9];

	set_triangles(scene->triangles, scene->triangles_n);
	set_spheres(scene->spheres, scene->spheres_n);
	set_squares(scene->squares, scene->squares_n)
	cam_orient = &scene->active_cam->current_orient;
	normalize(cam_orient, cam_orient);
	scale(-1, &scene->active_cam->current_pos, &translation);
	move_scene(scene, &translation);
	printf("         -----------------\n");
	t_vect v = (t_vect){0., 0., -1.};
	printf("test vector before transformation:\n");
	print_vect(&v);
	if (!(same_vect(cam_orient, &scene->ref_orient)))
	{
		if (opposite_vect(cam_orient, &scene->ref_orient))
			rot_from_anti_ref_orient(rot_matrix);
		else 
			extract_scene_rotation(cam_orient, &scene->ref_orient, rot_matrix);
		rotate_scene(scene, rot_matrix);
		rotate_point(rot_matrix, &v, &v);
	}
}

void	init_scene(t_scene *scene, t_rt *rt)
{
	scene->aabbs = NULL;
	scene->planes = NULL;
	scene->squares = NULL;
	scene->triangles = NULL;
	scene->cylinders = NULL;
	scene->spheres = NULL;
	scene->olights = NULL;
	scene->cams = NULL;
	scene->active_cam = NULL;
	scene->ref_orient.x = 0.;
	scene->ref_orient.y = 0.;
	scene->ref_orient.z = -1.;
	ft_memmove(scene->background_rgb, rt->ambient_rgb, 3);
	make_array(rt, scene);
	set_squares_edges(scene->squares, scene->squares_n);
	set_cams(scene->cams, scene->cams_n);
	scene->active_cam = scene->cams;
	assign_turn_matrices(scene->left_matrix, scene->right_matrix);
	assign_turn_matrices2(scene->up_matrix, scene->down_matrix);
	place_objs(scene);
	compute_triangles_edges(scene->triangles, scene->triangles_n);
}
