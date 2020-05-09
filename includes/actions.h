/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/08 22:33:19 by darbib            #+#    #+#             */
/*   Updated: 2020/05/09 17:15:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#ifndef ACTIONS_H
# define ACTIONS_H


# define STEP_SIZE 1
# define ANGLE_SIZE 1
# define MAX_KEYCODE 65536

void			assign_key_fts(void);
void			move_forward(void *param);  
void			move_backward(void *param);  
void			move_left(void *param);  
void			move_right(void *param);  
void			turn_left(void *param);
void			turn_right(void *param);
#endif
