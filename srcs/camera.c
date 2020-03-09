/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:33:07 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 18:12:47 by darbib           ###   ########.fr       */
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
	t_cam	*cam;
	
	check_data(line, cfg);
	if (!(cam = (t_cam *)malloc(sizeof(t_cam))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(cam->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(cam->ort = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	cam->fov = ft_atoi_mv(&line);	
	line = ft_pass_spaces(line);
	if (cfg->cams)
		ft_lstadd_back(&(cfg->cams), ft_lstnew(cam));
	else
		cfg->cams = ft_lstnew(cam);
}

void	print_cam(t_cam *cam)
{
	ft_printf("Pos : %f, %f, %f\n", cam->pos->x, cam->pos->y,
			cam->pos->z);
	ft_printf("Orientation : %f, %f, %f\n", cam->ort->x, cam->ort->y,
			cam->ort->z);
	ft_printf("Fov : %d\n", cam->fov);
	ft_printf("\n");
}
