/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   turn.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:39:51 by darbib            #+#    #+#             */
/*   Updated: 2020/05/08 23:10:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "general.h"
#include "print.h"

void	turn_left(void *param)
{
	((t_param *)param)->scene->phi += to_radian(ANGLE_SIZE); 
}

void	turn_right(void *param)
{
	((t_param *)param)->scene->phi -= to_radian(ANGLE_SIZE); 
}
