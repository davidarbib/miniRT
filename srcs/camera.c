/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 16:33:07 by darbib            #+#    #+#             */
/*   Updated: 2020/04/15 19:58:23 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "ft_printf.h"

void	destroy_camera(void *obj)
{
	t_cam *camera;
	
	camera = (t_cam *)obj;
	free(camera->pos);
	free(camera->ort);
	camera->pos = NULL;
	camera->ort = NULL;
	free(camera);
	camera = NULL;
}

static void	check_camera(t_rt *cfg, t_cam *cam)
{
	if (!is_orientation_vect(cam->ort))
		parse_error(E_ORIENT, cfg);	
	if (cam->fov < 0 || cam->fov > 180)	
		parse_error(E_FOVRANGE, cfg);	
}

void	parse_camera(t_rt *cfg, char *line)
{
	t_cam	*cam;
	
	check_data(line, cfg);
	if (!(cam = (t_cam *)malloc(sizeof(t_cam))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)cam;
	cam->pos = NULL;
	cam->ort = NULL;
	cfg->flags |= CAM;
	line = ft_pass_spaces(line);
	if (!(cam->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(cam->ort = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	cam->fov = ft_atoi_mv(&line);	
	line = ft_pass_spaces(line);
	check_camera(cfg, cam);
	if (cfg->cams)
		ft_lstadd_back(&(cfg->cams), ft_lstnew(cam));
	else
		cfg->cams = ft_lstnew(cam);
}

void	print_cam(void *obj)
{
	t_cam	*cam;

	cam = (t_cam *)obj;
	printf("Pos : %f, %f, %f\n", cam->pos->x, cam->pos->y,
			cam->pos->z);
	printf("Orientation : %f, %f, %f\n", cam->ort->x, cam->ort->y,
			cam->ort->z);
	printf("Fov : %d\n", cam->fov);
	printf("\n");
}
