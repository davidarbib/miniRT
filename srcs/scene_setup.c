/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:54:47 by darbib            #+#    #+#             */
/*   Updated: 2020/06/19 14:32:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rotation.h"
#include "parsing.h"
#include "print.h"
#include "spheric.h"

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

	cam_orient = &scene->active_cam->current_orient;
	scale(-1, &scene->active_cam->current_pos, &translation);
	move_scene(scene, &translation);
	if (!(same_vect(cam_orient, &scene->ref_orient)))
	{
		if (opposite_vect(cam_orient, &scene->ref_orient))
			rot_from_anti_ref_orient(rot_matrix);
		else 
			extract_scene_rotation(cam_orient, &scene->ref_orient, rot_matrix);
		rotate_scene(scene, rot_matrix);
	}
}

void	init_scene(t_scene *scene)
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
	
	printf("/*---------------*/\n");
	t_spheric sph;
	to_spherical(&scene->ref_orient, &sph);
	printf("initial orientation\n");
	print_vect_sph(&sph);
	print_angle(sph.phi, sph.theta);

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	scene->active_cam = malloc(sizeof(t_cam));
	printf("position camera: ");
	scanf("%lf%lf%lf", &scene->active_cam->current_pos.x, 
			&scene->active_cam->current_pos.y,
			&scene->active_cam->current_pos.z);
	printf("orientation camera: ");
	scanf("%lf%lf%lf", &scene->active_cam->current_orient.x, 
			&scene->active_cam->current_orient.y,
			&scene->active_cam->current_orient.z);

	printf("fov camera: ");
	scanf("%d", &scene->active_cam->fov);
	
	printf("phi : ");
	scanf("%lf", &scene->phi);
	scene->phi = to_radian(scene->phi);
	scene->theta = 0;

	/*
	scene->planes = malloc(sizeof(t_plane));

	scene->planes->pos.x = 0;
	scene->planes->pos.y = 0;
	scene->planes->pos.z = 2;
	scene->planes->orient.x = 1;
	scene->planes->orient.y = 0;
	scene->planes->orient.z = 0;
	scene->planes->rgb[0] = 0x2d;
	scene->planes->rgb[1] = 0x1e;
	scene->planes->rgb[2] = 0x2f;
	*/
	scene->cams_n = 1;
	scene->triangles = malloc(2 * sizeof(t_trig));
	scene->triangles[0].pt1.x = -1.; 
	scene->triangles[0].pt1.y = -1.; 
	scene->triangles[0].pt1.z = -1.; 
	scene->triangles[0].pt2.x = 1.; 
	scene->triangles[0].pt2.y = -1.; 
	scene->triangles[0].pt2.z = -1.; 
	scene->triangles[0].pt3.x = 0.; 
	scene->triangles[0].pt3.y = 1.; 
	scene->triangles[0].pt3.z = -1.; 
	scene->triangles[0].rgb[0] = 0x2d;
	scene->triangles[0].rgb[1] = 0x1e;
	scene->triangles[0].rgb[2] = 0x2f;

	scene->triangles[1].pt1.x = 0.5; 
	scene->triangles[1].pt1.y = 0.5; 
	scene->triangles[1].pt1.z = -1.; 
	scene->triangles[1].pt2.x = 0.75; 
	scene->triangles[1].pt2.y = 0.5; 
	scene->triangles[1].pt2.z = -1.; 
	scene->triangles[1].pt3.x = 0.75; 
	scene->triangles[1].pt3.y = 0.75; 
	scene->triangles[1].pt3.z = -1.; 
	scene->triangles[1].rgb[0] = 0xa7;
	scene->triangles[1].rgb[1] = 0xd4;
	scene->triangles[1].rgb[2] = 0x9b;
	scene->triangles_n = 2;

	set_triangles(scene->triangles, scene->triangles_n);

	scene->planes_n = 0;
	assign_turn_matrices(scene->left_matrix, scene->right_matrix);
	assign_turn_matrices2(scene->up_matrix, scene->down_matrix);
	place_objs(scene);
}
