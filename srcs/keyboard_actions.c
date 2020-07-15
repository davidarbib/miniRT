/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 16:23:29 by darbib            #+#    #+#             */
/*   Updated: 2020/07/14 17:37:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
//#include "keys_linux.h"
#include "macos_codes.h"
#include "general.h"
#include "print.h"
#include "mlx.h"
#include "update.h"
#include <stdio.h>

void	(*g_key_pressed_ft[MAX_KEYCODE + 1])(void *param);

static void	null_action(void *param)
{
	(void)param;
	return ;
}

void assign_key_fts(void)
{
	int		i;

	i = -1;
	while (++i <= MAX_KEYCODE)
		g_key_pressed_ft[i] = null_action;
	g_key_pressed_ft[KEY_W] = move_forward;
	g_key_pressed_ft[KEY_S] = move_backward;
	g_key_pressed_ft[KEY_A] = move_left;
	g_key_pressed_ft[KEY_D] = move_right;
	g_key_pressed_ft[KEY_UP] = turn_up;  
	g_key_pressed_ft[KEY_DOWN] = turn_down;  
	g_key_pressed_ft[KEY_LEFT] = turn_left;  
	g_key_pressed_ft[KEY_RIGHT] = turn_right;  
	g_key_pressed_ft[KEY_TAB] = cam_switch;  
}

int		key_pressed_hook(int keycode, void *param)
{
	g_key_pressed_ft[keycode](param);
	return (1);
}
