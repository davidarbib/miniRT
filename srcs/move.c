/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:23:52 by darbib            #+#    #+#             */
/*   Updated: 2020/05/08 23:11:10 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h" 
#include "general.h"
#include "print.h"

void	move_forward(void *param)
{
	((t_param *)param)->scene->cam_pos->z += STEP_SIZE; 
}

void	move_backward(void *param)
{
	((t_param *)param)->scene->cam_pos->z -= STEP_SIZE; 
}

void	move_left(void *param)
{
	((t_param *)param)->scene->cam_pos->x += STEP_SIZE; 
}

void	move_right(void *param)
{
	((t_param *)param)->scene->cam_pos->x -= STEP_SIZE; 
}
