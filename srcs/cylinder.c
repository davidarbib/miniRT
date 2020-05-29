/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:50:39 by darbib            #+#    #+#             */
/*   Updated: 2020/05/29 13:27:57 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "print.h"
#include "error.h"

void	destroy_cylinder(void *obj)
{
	t_cyld *cylinder;
	
	cylinder = (t_cyld *)obj;
	free(cylinder);
	cylinder = NULL;
}

static void	check_cylinder(t_rt *cfg, t_cyld *cyl)
{
	if (!is_orientation_vect(&cyl->orient))
		parse_error(E_ORIENT, cfg);
}

void	parse_cylinder(t_rt *cfg, char *line)
{
	t_cyld	*cyl;
	
	check_data(line, cfg);
	if (!(cyl = (t_cyld *)malloc(sizeof(t_cyld))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)cyl;
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &cyl->pos);
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &cyl->orient);
	line = ft_pass_spaces(line);
	cyl->diam = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	cyl->height = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	check_cylinder(cfg, cyl);
	if (!(get_rgb(cyl->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	if (cfg->cyls)
		ft_lstadd_back(&(cfg->cyls), ft_lstnew(cyl));
	else
		cfg->cyls = ft_lstnew(cyl);
}

void	print_cyl(void *obj)
{
	t_cyld *cyl;

	cyl = (t_cyld *)obj;
	printf("Pos : ");
	print_vect(&cyl->pos);
	printf("Orientation : ");
	print_vect(&cyl->orient);
	printf("diameter : %f\n", cyl->diam);
	printf("Height : %f\n", cyl->height);
	printf("RGB : %d,%d,%d\n", cyl->rgb[0], cyl->rgb[1], cyl->rgb[2]);
	printf("\n");
}
