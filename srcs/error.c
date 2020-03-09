/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:50:26 by darbib            #+#    #+#             */
/*   Updated: 2020/03/09 19:13:34 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "rt_errors.h"
#include "ft_printf.h"

void	parse_error(char *msg, t_rt *cfg)
{
	if (cfg->data)
		ft_printf("Error line %d : %s\n", cfg->linenb, msg);
	else
		ft_printf("Error : %s\n", msg);
	//destruct(cfg);
	exit(EXIT_FAILURE);
}

void	sys_error(t_rt *cfg)
{
	(void)cfg;
	perror("Error : ");
	//destruct(cfg);
	exit(EXIT_FAILURE);
}
