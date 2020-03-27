/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/27 17:14:28 by darbib            #+#    #+#             */
/*   Updated: 2020/03/27 17:16:41 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "general.h"

void	init_lst(t_rt *cfg)
{
	cfg->cyls = NULL;
	cfg->cams = NULL;
	cfg->olights = NULL;
	cfg->planes = NULL;
	cfg->spheres = NULL;
	cfg->trigs = NULL;
	cfg->squares = NULL;
}
