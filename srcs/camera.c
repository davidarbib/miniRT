/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:33:07 by darbib            #+#    #+#             */
/*   Updated: 2020/02/27 18:31:42 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_camera(void *obj)
{
	t_cam *plane;
	
	camera = (t_cam *)obj;
	free(camera->pos);
	free(camera->ort);
	camera->pos = NULL;
	camera->ort = NULL;
}

int		parse_camera(t_rt *cfg, char *line)
{
}
