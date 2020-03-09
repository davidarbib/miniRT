/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:32:42 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 23:32:14 by darbib           ###   ########.fr       */
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
	t_plane	*plane;
	
	check_data(line, cfg);
	if (!(plane = (t_plane *)malloc(sizeof(t_plane))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(plane->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(plane->ort = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(plane->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	if (cfg->planes)
		ft_lstadd_back(&(cfg->planes), ft_lstnew(plane));
	else
		cfg->planes = ft_lstnew(plane);
}

void	print_plane(t_plane *plane)
{
	ft_printf("Pos : %f, %f, %f\n", plane->pos->x, plane->pos->y,
			plane->pos->z);
	ft_printf("Orientation : %f, %f, %f\n", plane->ort->x, plane->ort->y,
			plane->ort->z);
	ft_printf("RGB : %d,%d,%d\n", plane->rgb[0], plane->rgb[1],
				plane->rgb[2]);
	ft_printf("\n");
}
