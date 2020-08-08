/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:43:21 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 14:46:37 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "general.h"
#include "sphere.h"
#include "print.h"

void	destroy_sphere(void *obj)
{
	t_sphere *sphere;

	sphere = (t_sphere *)obj;
	free(sphere);
	sphere = NULL;
}

void	parse_sphere(t_rt *cfg, char *line)
{
	t_sphere	*sphere;

	check_data(line, cfg);
	if (!(sphere = (t_sphere *)malloc(sizeof(t_sphere))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)sphere;
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &sphere->pos);
	line = ft_pass_spaces(line);
	sphere->diam = ft_atof_mv(&line);
	line = ft_pass_spaces(line);
	if (*line == SEP)
		parse_error(E_MISSPPTY, cfg);
	if (sphere->diam <= 0)
		parse_error(E_DIAM, cfg);
	if (!(get_rgb(sphere->rgb, &line)))
		parse_error(E_BADRGB, cfg);
	trailing_char_detect(line, cfg);
	if (cfg->spheres)
		ft_lstadd_back(&(cfg->spheres), ft_lstnew(sphere));
	else
		cfg->spheres = ft_lstnew(sphere);
}

void	print_sphere(void *obj)
{
	t_sphere *sphere;

	sphere = (t_sphere *)obj;
	printf("Pos : ");
	print_vect(&sphere->pos);
	printf("Diameter : %f\n", sphere->diam);
	printf("RGB : %d,%d,%d\n", sphere->rgb[0], sphere->rgb[1], sphere->rgb[2]);
	printf("\n");
}
