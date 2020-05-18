/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   aabb.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 20:19:28 by darbib            #+#    #+#             */
/*   Updated: 2020/05/16 15:31:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "aabb.h"
#include <stdio.h>

void	move_aabb(t_aabb *aabb, t_vect *translation)
{
	add_vect(aabb->corner, translation, aabb->corner);
	add_vect(aabb->corner + 1, translation, aabb->corner + 1);
}
