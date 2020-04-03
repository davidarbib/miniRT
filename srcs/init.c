/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 17:14:28 by darbib            #+#    #+#             */
/*   Updated: 2020/04/03 21:44:36 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void	init_cfg(t_rt *cfg)
{
	ft_bzero(cfg->buf, BUFFSIZE);
	cfg->labels_tab = NULL;
	cfg->resx = 0;
	cfg->resy = 0;
	cfg->ambient_ratio = 0;
	cfg->cyls = NULL;
	cfg->cams = NULL;
	cfg->olights = NULL;
	cfg->planes = NULL;
	cfg->spheres = NULL;
	cfg->trigs = NULL;
	cfg->squares = NULL;
	cfg->ambient_rgb[0] = 0;
	cfg->ambient_rgb[1] = 0;
	cfg->ambient_rgb[2] = 0;
	cfg->linenb = 0;
	cfg->flags = 0;
}
