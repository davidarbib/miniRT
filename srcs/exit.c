/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/15 18:58:54 by darbib            #+#    #+#             */
/*   Updated: 2020/08/08 15:03:12 by darbib           ###   ########.fr       */
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

void	bmp_exit(void *param)
{
	destroy_scene(((t_param *)param)->scene);
	free(((t_param *)param)->img->buf);
	exit(EXIT_SUCCESS);
}
