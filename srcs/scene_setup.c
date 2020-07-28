/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:54:47 by darbib            #+#    #+#             */
/*   Updated: 2020/07/28 14:19:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rotation.h"
#include "parsing.h"
#include "print.h"
#include "spheric.h"
#include "matrix.h"
#include "raytrace.h"
#include "actions.h"
#include "mlx.h"

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
		&& (scene->cylinders = ft_lsttotab(rt->cyls, sizeof(t_cylinder), 
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
	//double 	test_matrix[9];

	set_planes(scene->planes, scene->planes_n);
	set_triangles(scene->triangles, scene->triangles_n);
	set_spheres(scene->spheres, scene->spheres_n);
	set_squares(scene->squares, scene->squares_n);
	set_cylinders(scene->cylinders, scene->cylinders_n);
	set_olights(scene->olights, scene->olights_n);
	cam_orient = &scene->active_cam->current_orient;
	normalize(cam_orient, cam_orient);
	scale(-1, &scene->active_cam->current_pos, &translation);
	move_scene(scene, &translation);
	if (!(same_vect(cam_orient, &scene->ref_orient)))
	{
		if (opposite_vect(cam_orient, &scene->ref_orient))
			rot_from_anti_ref_orient(rot_matrix);
		else 
			extract_scene_rotation(cam_orient, &scene->ref_orient, rot_matrix);
		rotate_scene(scene, rot_matrix);
		printf("------------------\n");
		print_matrix(rot_matrix);
		printf("------------------\n");
		/*
		printf("---------------------------\n");
		t_vect v1 = (t_vect) {4.5, 29., -2.};
		t_vect v_out1;
		t_vect v_out2;
		rotate_point(test_matrix, &v1, &v_out1); 
		rotate_point(rot_matrix, &v1, &v_out2); 
		printf("v1 after exact rotation : \n");
		print_vect(&v_out1);
		printf("v1 after computed rotation : \n");
		print_vect(&v_out2);
		printf("---------------------------\n");
		*/
	}
	set_current_edges(scene->squares, scene->squares_n);
}

static void	init_objs_fts(t_scene *scene)
{
	assign_key_fts();
	scene->planes = NULL;
	scene->squares = NULL;
	scene->triangles = NULL;
	scene->cylinders = NULL;
	scene->spheres = NULL;
	scene->olights = NULL;
	scene->cams = NULL;
	scene->active_cam = NULL;
	scene->ref_orient = (t_vect) {0., 0., -1.};
	scene->background_rgb[0] = 0.;
	scene->background_rgb[1] = 0.;
	scene->background_rgb[2] = 0.;
}

void	init_scene(t_scene *scene, t_rt *rt, t_mlx *mlx_cfg)
{
	init_objs_fts(scene);
	scene->lowres = 0;
	scene->resx = mlx_cfg->sizex;
	scene->resy = mlx_cfg->sizey;	
	to_rgb_ratio(rt->ambient_rgb, &scene->ambient_rgb);
	scene->ambient_ratio = rt->ambient_ratio;
	make_array(rt, scene);
	set_quadrics_radius(scene->cylinders, scene->cylinders_n,
						scene->spheres, scene->spheres_n);
	set_cams(scene->cams, scene->cams_n);
	scene->active_cam = scene->cams;
	assign_turn_matrices(scene->left_matrix, scene->right_matrix);
	assign_turn_matrices2(scene->up_matrix, scene->down_matrix);
	assign_roll_matrices(scene->roll_matrix, scene->invroll_matrix);
	place_objs(scene);
	compute_triangles_edges(scene->triangles, scene->triangles_n);
}
