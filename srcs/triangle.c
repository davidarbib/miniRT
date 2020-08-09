/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:38:44 by darbib            #+#    #+#             */
/*   Updated: 2020/08/09 14:03:14 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"

void	destroy_triangle(void *obj)
{
	t_trig *triangle;

	triangle = (t_trig *)obj;
	free(triangle);
	triangle = NULL;
}

void	parse_triangle(t_rt *cfg, char *line)
{
	t_trig	*triangle;

	check_data(line, cfg);
	if (!(triangle = (t_trig *)malloc(sizeof(t_trig))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)triangle;
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &triangle->pt1);
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &triangle->pt2);
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &triangle->pt3);
	line = ft_pass_spaces(line);
	if (!(get_rgb(triangle->rgb, &line)))
		parse_error(E_BADRGB, cfg);
	trailing_char_detect(line, cfg);
	if (cfg->trigs)
		ft_lstadd_back(&(cfg->trigs), ft_lstnew(triangle));
	else
		cfg->trigs = ft_lstnew(triangle);
}
