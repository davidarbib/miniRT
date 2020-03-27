/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:38:44 by darbib            #+#    #+#             */
/*   Updated: 2020/03/27 18:42:51 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"
#include "ft_printf.h"

void	destroy_triangle(void *obj)
{
	t_trig *triangle;
	
	triangle = (t_trig *)obj;
	free(triangle->pt1);
	free(triangle->pt2);
	free(triangle->pt3);
	triangle->pt1 = NULL;
	triangle->pt2 = NULL;
	triangle->pt3 = NULL;
}

void	parse_triangle(t_rt *cfg, char *line)
{
	t_trig	*triangle;
	
	check_data(line, cfg);
	if (!(triangle = (t_trig *)malloc(sizeof(t_trig))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(triangle->pt1 = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(triangle->pt2 = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(triangle->pt3 = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	if (!(get_rgb(triangle->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	if (cfg->trigs)
		ft_lstadd_back(&(cfg->trigs), ft_lstnew(triangle));
	else
		cfg->trigs = ft_lstnew(triangle);
}

void	print_triangle(void *obj)
{
	t_trig *triangle;

	triangle = (t_trig *)obj;
	printf("Pt1 : %f, %f, %f\n", triangle->pt1->x, triangle->pt1->y,
	 	triangle->pt1->z);
	printf("Pt2 : %f, %f, %f\n", triangle->pt2->x, triangle->pt2->y,
	 	triangle->pt2->z);
	printf("Pt1 : %f, %f, %f\n", triangle->pt3->x, triangle->pt3->y,
	 	triangle->pt3->z);
	printf("RGB : %d,%d,%d\n", triangle->rgb[0], triangle->rgb[1],
	 		triangle->rgb[2]);
	printf("\n");
}
