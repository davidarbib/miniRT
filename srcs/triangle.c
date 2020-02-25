/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangle.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:38:44 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 18:49:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
