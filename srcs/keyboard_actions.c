/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard_actions.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/09 16:23:29 by darbib            #+#    #+#             */
/*   Updated: 2020/05/09 18:02:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "actions.h"
#include "keys_linux.h"
#include "general.h"
#include "print.h"
#include "mlx.h"

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
	//g_key_pressed_ft[KEY_UP] = parse_plane;  
	//g_key_pressed_ft[KEY_DOWN] = parse_sphere;  
	//g_key_pressed_ft[KEY_LEFT] = turn_left;  
	//g_key_pressed_ft[KEY_RIGHT] = turn_right;  
}

int		key_pressed_hook(int keycode, void *param)
{
	t_scene *scene;
	t_mlx	*cfg;

	g_key_pressed_ft[keycode](param);
	scene = ((t_param *)param)->scene;
	cfg = ((t_param *)param)->mlx_cfg;
	//	scene->phi += M_PI/10000;
	refresh_img(cfg, scene->resx, scene->resy);
	print_angle(scene->phi, scene->theta);
	raytrace(scene, cfg);
	print_vect(scene->cam_pos);
	printf("mouvement applique\n");
	if (!(mlx_put_image_to_window(cfg->mlx_ptr, cfg->win_ptr,
		cfg->img_ptr, 0, 0)))
		return (0);
	return (1);
}
