/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:54:47 by darbib            #+#    #+#             */
/*   Updated: 2020/05/29 13:37:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "rotation.h"
#include "parsing.h"
#include "print.h"

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

	scale(-1, &scene->active_cam->current_pos, &translation);
	move_scene(scene, &translation);
	//extract_scene_rotation(scene->active_cam->current_orient, scene->ref_orient, 
	//		&scene->phi, &scene->theta);
	rotate_scene(scene, scene->phi, scene->theta);
}

void	init_scene(t_scene *scene)
{
	double phi_degree;

	scene->ref_orient = malloc(sizeof(t_vect));
	scene->ref_orient->x = 0.;
	scene->ref_orient->y = 0.;
	scene->ref_orient->z = 1.;

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	scene->active_cam = malloc(sizeof(t_cam));
	printf("position camera: ");
	scanf("%lf%lf%lf", &scene->active_cam->current_pos.x, 
			&scene->active_cam->current_pos.y,
			&scene->active_cam->current_pos.z);

	printf("phi : ");
	scanf("%lf", &phi_degree);
	scene->phi = to_radian(phi_degree);

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
	scene->cams_n = 1;
	scene->planes_n = 1;
	//set_cams(scene->cams, scene->cams_n);
	//scene->active_cam = scene->cams;
	scene->theta = 0;
	set_planes(scene->planes, scene->planes_n);
	print_vect(&scene->planes->current_pos);
	print_vect(&scene->planes->current_orient);
	place_objs(scene);
}
