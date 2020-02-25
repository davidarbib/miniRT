/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:43:21 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 18:46:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	destroy_sphere(void *obj)
{
	t_sphere *sphere;
	
	sphere = (t_sphere *)obj;
	free(sphere->pos);
	sphere->pos = NULL;
}
