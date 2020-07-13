/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_move2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/22 13:20:11 by darbib            #+#    #+#             */
/*   Updated: 2020/07/13 12:59:38 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "print.h"

void	move_olights(t_olight *olights, int n, t_vect *translation)
{
	while (n--)
		add_vect(&olights[n].current_pos, translation, &olights[n].current_pos);
}
