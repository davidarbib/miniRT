/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:17 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 18:51:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"


void	(*g_destroy_ft[NB_OBJS])(void *obj);

static void assign_destroy(void)
{
	g_destroy_ft[2] = destroy_camera;
	g_destroy_ft[3] = destroy_cylinder;
	g_destroy_ft[4] = destroy_olight;
	g_destroy_ft[5] = destroy_plane;
	g_destroy_ft[6] = destroy_sphere;
	g_destroy_ft[7] = destroy_square;
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

static void	destroy_objs(t_list *objs)
{
	while (objs)
	{
		//call specific destructor
		//free
		//current = next
	}
}

void		destroy(t_rt *cfg)
{
	if (cfg->labels_tab)
	{
		destroy_labels(cfg->labels_tab);
		cfg->labels_tab = NULL;
	}
	if (cfg->objs)
	{
		destroy_objs(cfg->objs);
		cfg->objs = NULL;
	}
}
