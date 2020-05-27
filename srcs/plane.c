/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:32:42 by darbib            #+#    #+#             */
/*   Updated: 2020/05/22 13:21:59 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "ft_printf.h"
#include <assert.h>

void	destroy_plane(void *obj)
{
	t_plane *plane;
	
	plane = (t_plane *)obj;
	free(plane->pos);
	free(plane->orient);
	free(plane->current_pos);
	free(plane->current_orient);
	plane->pos = NULL;
	plane->orient = NULL;
	plane->current_pos = NULL;
	plane->current_orient = NULL;
	free(plane);
	plane = NULL;
}

static void	check_plane(t_rt *cfg, t_plane *plane)
{
	if (!(is_orientation_vect(plane->orient)))
		parse_error(E_ORIENT, cfg);
}

static void	init_plane(t_plane *plane)
{
	plane->pos = NULL;
	plane->orient = NULL;
	plane->current_pos = NULL;
	plane->current_orient = NULL;
}

void	parse_plane(t_rt *cfg, char *line)
{
	t_plane	*plane;
	
	check_data(line, cfg);
	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)plane;
	init_plane(plane);
	line = ft_pass_spaces(line);
	if (!(plane->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(plane->orient = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(plane->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	check_plane(cfg, plane);
	if (cfg->planes)
		ft_lstadd_back(&(cfg->planes), ft_lstnew(plane));
	else
		cfg->planes = ft_lstnew(plane);
}

void	print_plane(void *obj)
{
	t_plane *plane;
	
	plane = (t_plane *)obj;
	printf("Pos : %f, %f, %f\n", plane->pos->x, plane->pos->y,
	 	plane->pos->z);
	printf("Orientation : %f, %f, %f\n", plane->orient->x, plane->orient->y,
	 	plane->orient->z);
	printf("RGB : %d,%d,%d\n", plane->rgb[0], plane->rgb[1],
	 		plane->rgb[2]);
	printf("\n");
}
