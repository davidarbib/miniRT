/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:37:45 by darbib            #+#    #+#             */
/*   Updated: 2020/07/19 21:52:48 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "error.h"
#include "minirt.h"
#include "print.h"

void			destroy_olight(void *obj)
{
	t_olight *olight;
	
	olight = (t_olight *)obj;
	free(olight);
	olight = NULL;
}

static void		check_olight(t_rt *cfg, t_olight *olight)
{
	if (!is_ratio(olight->ratio))
		parse_error(E_BADRATIO, cfg); 
}

void			parse_olight(t_rt *cfg, char *line)
{
	t_olight	*olight;
	
	check_data(line, cfg);
	if (!(olight = (t_olight *)malloc(sizeof(t_olight))))
		sys_error(cfg);
	cfg->current_obj_addr = (void *)olight;
	line = ft_pass_spaces(line);
	get_vector(&line, cfg, &olight->pos);
	line = ft_pass_spaces(line);
	olight->ratio = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	if (!(get_rgb(olight->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	check_olight(cfg, olight);
	if (cfg->olights)
		ft_lstadd_back(&(cfg->olights), ft_lstnew(olight));
	else
		cfg->olights = ft_lstnew(olight);
}

void			print_olight(void *obj)
{
	t_olight *olight;

	olight = (t_olight *)obj;
	printf("Pos : ");
	print_vect(&olight->pos);
	printf("Ratio : %f\n", olight->ratio);
	printf("RGB : %d,%d,%d\n", olight->rgb[0], olight->rgb[1],
	 		olight->rgb[2]);
	printf("\n");
}
