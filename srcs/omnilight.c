/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   omnilight.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 13:37:45 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 17:43:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	destroy_olight(void *obj)
{
	t_olight *olight;
	
	olight = (t_olight *)obj;
	free(olight->pos);
	olight->pos = NULL;
}

int		parse_olight(t_rt *cfg, char *line)
{
	t_olight	*olight;
	
	check_data(line, cfg);
	if (!(olight = (t_olight *)malloc(sizeof(t_olight))))
		sys_error(cfg);
	line = ft_pass_spaces(line);
	if (!(olight->pos = get_vector(&line, cfg)))
		parse_error(E_BADVECT, cfg);
	line = ft_pass_spaces(line);
	olight->ratio = ft_atof_mv(&line);	
	line = ft_pass_spaces(line);
	if (!(get_rgb(olight->rgb, &line)))
		parse_error(E_BADRGB, cfg); 
	if (cfg->olights)
		ft_lstadd_back(&(cfg->olights), ft_lstnew(olight));
	else
		cfg->olights = ft_lstnew(olight);
}

void	print_olight(t_olight *olight)
{
	ft_printf("Pos : %f, %f, %f\n", olight->pos->x, olight->pos->y,
			olight->pos->z);
	ft_printf("Ratio : %f\n", olight->ratio);
	ft_printf("RGB : %d,%d,%d\n", olight->rgb[0], olight->rgb[1],
				olight->rgb[2]);
	ft_printf("\n");
}
