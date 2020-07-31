/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:13:48 by darbib            #+#    #+#             */
/*   Updated: 2020/07/31 16:20:20 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "parsing.h"
#include "scene.h"

int		update_display(t_scene *scene, t_mlx *cfg)
{
	refresh_img(cfg);
	compute_triangles_edges(scene->triangles, scene->triangles_n);
	if (scene->lowres)
		raytrace_lowres(scene, cfg);
	else
		raytrace(scene, cfg);
	if (!(mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr,
		cfg->img_ptr, 0, 0)))
		return (0);
	return (1);
}
