/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:33:19 by darbib            #+#    #+#             */
/*   Updated: 2020/08/05 14:56:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ACTIONS_H
# define ACTIONS_H

# include "general.h"

# define STEP_SIZE 0.5
# define ANGLE_SIZE 5
# define MAX_KEYCODE 65536

int				loop_hook(void *param);
int				key_pressed_hook(int keycode, void *param);
void			assign_key_fts(void);
void			move_forward(void *param);
void			move_backward(void *param);
void			move_left(void *param);
void			move_right(void *param);
void			move_up(void *param);
void			move_down(void *param);
void			turn_left(void *param);
void			turn_right(void *param);
void			turn_up(void *param);
void			turn_down(void *param);
void			roll(void *param);
void			inv_roll(void *param);
void			cam_switch(void *param);
void			normal_exit(void *param);
int				normal_exit2(void *param);
void			res_switch(void *param);
#endif
