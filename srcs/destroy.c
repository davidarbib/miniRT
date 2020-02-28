/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 17:35:17 by darbib            #+#    #+#             */
/*   Updated: 2020/02/28 14:52:25 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	destroy_labels(char **labels)
{
	while (*labels)
	{
		free(*labels);
		*labels = NULL;
		labels++;
	}
}

void		destroy(t_rt *cfg)
{
	if (cfg->labels_tab)
	{
		destroy_labels(cfg->labels_tab);
		cfg->labels_tab = NULL;
	}
	ft_lstclear(cfg->cyls, destroy_cylinder);
	ft_lstclear(cfg->cams, destroy_camera);
	ft_lstclear(cfg->olights, destroy_olight);
	ft_lstclear(cfg->planes, destroy_plane);
	ft_lstclear(cfg->spheres, destroy_sphere);
	ft_lstclear(cfg->trigs, destroy_triangle);
	ft_lstclear(cfg->squares, destroy_square);
}
