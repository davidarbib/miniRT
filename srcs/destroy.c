/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:17 by darbib            #+#    #+#             */
/*   Updated: 2020/07/20 15:36:16 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

void	(*g_destroy_ft[NB_OBJS])(void *obj);

static void assign_fts(void)
{
	g_destroy_ft[0] = NULL;  
	g_destroy_ft[1] = NULL;  
	g_destroy_ft[2] = destroy_camera;  
	g_destroy_ft[3] = destroy_olight;  
	g_destroy_ft[4] = destroy_plane;  
	g_destroy_ft[5] = destroy_sphere;  
	g_destroy_ft[6] = destroy_square;  
	g_destroy_ft[7] = destroy_cylinder;  
	g_destroy_ft[8] = destroy_triangle;  
}

static void	destroy_labels(char **labels)
{
	while (*labels)
	{
		free(*labels);
		*labels = NULL;
		labels++;
	}
}

void		destroy_cfg(t_rt *cfg)
{
	assign_fts();
	if (cfg->labels_tab)
	{
		destroy_labels(cfg->labels_tab);
		free(cfg->labels_tab);
		cfg->labels_tab = NULL;
	}
	printf("cc1\n");
	if (cfg->flags & IN_PARSING
		&& cfg->current_obj_type > 1
		&& cfg->current_obj_addr)
		g_destroy_ft[cfg->current_obj_type](cfg->current_obj_addr);
	printf("cc2\n");
	if (cfg->flags & IN_PARSING)
	{
		printf("freeline\n");
		free(cfg->line);
	}
	printf("cc3\n");
	data_visu(cfg);
	ft_lstclear(&cfg->cyls, destroy_cylinder);
	ft_lstclear(&cfg->cams, destroy_camera);
	printf("cc4\n");
	ft_lstclear(&cfg->olights, destroy_olight);
	ft_lstclear(&cfg->planes, destroy_plane);
	ft_lstclear(&cfg->spheres, destroy_sphere);
	ft_lstclear(&cfg->trigs, destroy_triangle);
	ft_lstclear(&cfg->squares, destroy_square);
	printf("cc5\n");
}

void		destroy_scene(t_scene *scene)
{
	free(scene->planes);
	free(scene->squares);
	free(scene->triangles);
	free(scene->cylinders);
	free(scene->spheres);
	free(scene->olights);
	free(scene->cams);
}
