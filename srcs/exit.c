/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:54 by darbib            #+#    #+#             */
/*   Updated: 2020/07/15 19:28:44 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"

void	normal_exit(void *param)
{
	destroy_scene(((t_param *)param)->scene);
	exit(EXIT_SUCCESS);
}

int		normal_exit2(void *param)
{
	destroy_scene(((t_param *)param)->scene);
	exit(EXIT_SUCCESS);
}
