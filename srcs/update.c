/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:13:48 by darbib            #+#    #+#             */
/*   Updated: 2020/07/20 22:41:13 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "update.h"
#include "print.h"
#include "parsing.h"
#include "scene.h"

void	adapt_scene(t_scene *scene)
{
	t_vect	translation;

	scale(-1, &scene->active_cam->pos, &translation);
	//rotate_scene(t_scene *scene);
	move_scene(scene, &translation);
}

int		update_display(t_scene *scene, t_mlx *cfg)
{
	refresh_img(cfg);
	compute_triangles_edges(scene->triangles, scene->triangles_n);
	set_squares_edges(scene->squares,scene->squares_n);
	if (scene->lowres)
		raytrace_lowres(scene, cfg);
	else
		raytrace(scene, cfg);
	if (!(mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr,
		cfg->img_ptr, 0, 0)))
		return (0);
	return (1);
}
