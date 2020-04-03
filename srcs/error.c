/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 13:50:26 by darbib            #+#    #+#             */
/*   Updated: 2020/04/03 20:55:32 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "error.h"
#include "ft_printf.h"

void	parse_error(char *msg, t_rt *cfg)
{
	if (cfg->flags & IN_PARSING)
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
