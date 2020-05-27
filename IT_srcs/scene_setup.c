/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_setup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 21:54:47 by darbib            #+#    #+#             */
/*   Updated: 2020/05/22 13:42:07 by darbib           ###   ########.fr       */
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

	scale(-1, scene->active_cam->current_pos, &translation);
	move_scene(scene, &translation);
	//extract_scene_rotation(scene->active_cam->current_orient, scene->ref_orient, 
	//		&scene->phi, &scene->theta);
	rotate_scene(scene, scene->phi, scene->theta);
}

void	init_scene(t_scene *scene)
{
	/*
	double		posaabbx1;
	double		posaabby1;
	double		posaabbz1;
	double		posaabbx2;
	double		posaabby2;
	double		posaabbz2;
	double		posaabbx3;
	double		posaabby3;
	double		posaabbz3;
	*/
	scene->resx = 800;
	scene->resy = 600;

	scene->ref_orient = malloc(sizeof(t_vect));
	scene->ref_orient->x = 0.;
	scene->ref_orient->y = 0.;
	scene->ref_orient->z = 1.;

	scene->background_rgb[0] = 0xd6; 
	scene->background_rgb[1] = 0xd9; 
	scene->background_rgb[2] = 0xce; 
	
	scene->active_cam = malloc(sizeof(t_cam));
	scene->active_cam->current_pos = malloc(sizeof(t_vect));
	scene->active_cam->current_orient = malloc(sizeof(t_vect));
	printf("position camera: ");
	scanf("%lf%lf%lf", &scene->active_cam->current_pos->x, 
			&scene->active_cam->current_pos->y,
			&scene->active_cam->current_pos->z);
	printf("\n");
	/*
	printf("orientation camera: ");
	scanf("%lf%lf%lf", &scene->cam_orient->x, &scene->cam_orient->y,
			&scene->cam_orient->z);
	printf("\n");
	*/
	double phi_degree;

	printf("phi : ");
	scanf("%lf", &phi_degree);
	scene->phi = to_radian(phi_degree);
	scene->aabbs = malloc(sizeof(t_aabb) * 3);
/*
	printf("position cube bleu: ");
	scanf("%lf%lf%lf", &posaabbx1, &posaabby1, &posaabbz1);
	printf("\n");
	printf("position cube orange : ");
	scanf("%lf%lf%lf", &posaabbx2, &posaabby2, &posaabbz2);
	printf("\n");
	printf("position cube vert: ");
	scanf("%lf%lf%lf", &posaabbx3, &posaabby3, &posaabbz3);
	printf("\n");
*/
	scene->planes = malloc(sizeof(t_plane));
	scene->planes->pos = malloc(sizeof(t_plane));
	scene->planes->orient = malloc(sizeof(t_plane));
	scene->planes->pos->x = 0;
	scene->planes->pos->y = 0;
	scene->planes->pos->z = 2;
	scene->planes->orient->x = 1;
	scene->planes->orient->y = 0;
	scene->planes->orient->z = 0;
	scene->planes->rgb[0] = 0x2d;
	scene->planes->rgb[1] = 0x1e;
	scene->planes->rgb[2] = 0x2f;
	printf("plane pos");
	print_vect(scene->planes->pos);
	printf("plane orient");
	print_vect(scene->planes->orient);
/*
	posaabbx1 = 100;
	posaabby1 = -50;
	posaabbz1 = 560;
	posaabbx2 = -50;
	posaabby2 = -200;
	posaabbz2 = 560;
	posaabbx3 = -200;
	posaabby3 = -50;
	posaabbz3 = 560;

	//cube bleu
	scene->aabb1->corner[0].x = posaabbx1 + 0;
	scene->aabb1->corner[0].y = posaabby1 + 0;
	scene->aabb1->corner[0].z = posaabbz1 + 0; 
	scene->aabb1->corner[1].x = posaabbx1 + 100;
	scene->aabb1->corner[1].y = posaabby1 + 100;
	scene->aabb1->corner[1].z = posaabbz1 + 100; 
	scene->aabb1->rgb[0] = 0x71; 
	scene->aabb1->rgb[1] = 0xa9; 
	scene->aabb1->rgb[2] = 0xf7; 
	
	//cube orange
	scene->aabb2->corner[0].x = posaabbx2 + 0;
	scene->aabb2->corner[0].y = posaabby2 + 0;
	scene->aabb2->corner[0].z = posaabbz2 + 0; 
	scene->aabb2->corner[1].x = posaabbx2 + 100;
	scene->aabb2->corner[1].y = posaabby2 + 100;
	scene->aabb2->corner[1].z = posaabbz2 + 100; 
	scene->aabb2->rgb[0] = 0xef; 
	scene->aabb2->rgb[1] = 0x8a; 
	scene->aabb2->rgb[2] = 0x17; 
	
	//cube vert
	scene->aabb3->corner[0].x = posaabbx3 + 0;
	scene->aabb3->corner[0].y = posaabby3 + 0;
	scene->aabb3->corner[0].z = posaabbz3 + 0; 
	scene->aabb3->corner[1].x = posaabbx3 + 100;
	scene->aabb3->corner[1].y = posaabby3 + 100;
	scene->aabb3->corner[1].z = posaabbz3 + 100; 
	scene->aabb3->rgb[0] = 0x4c; 
	scene->aabb3->rgb[1] = 0x9f; 
	scene->aabb3->rgb[2] = 0x70; 
*/
	scene->cams_n = 1;
	scene->planes_n = 1;
	//set_cams(scene->cams, scene->cams_n);
	//scene->active_cam = scene->cams;
	scene->theta = 0;
	set_planes(scene->planes, scene->planes_n);
	print_vect(scene->planes->current_pos);
	print_vect(scene->planes->current_orient);
	place_objs(scene);
}
