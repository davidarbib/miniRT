/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:32:42 by darbib            #+#    #+#             */
/*   Updated: 2020/02/27 18:37:04 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_plane(void *obj)
{
	t_plane *plane;
	
	plane = (t_plane *)obj;
	free(plane->pos);
	free(plane->ort);
	plane->pos = NULL;
	plane->ort = NULL;
}

int		parse_plane(t_rt *cfg, char *line)
{
}
