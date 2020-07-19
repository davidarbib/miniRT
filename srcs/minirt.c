/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/07/19 21:56:00 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "graphic.h"
#include "scene.h"
#include "raytrace.h"
#include "eventscode.h"
#include "actions.h"
#include "print.h"
#include "bitmap.h"

int		main(int ac, char **av)
{
	t_mlx	mlx_cfg;
	t_rt	rt_cfg;
	t_scene	scene;
	t_param param;
	
	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	init_cfg(&rt_cfg);
	parsing(ac, av, &rt_cfg);
	data_visu(&rt_cfg);
	init_scene(&scene, &rt_cfg, &mlx_cfg);
	init_graphics(&mlx_cfg);
	raytrace(&scene, &mlx_cfg);
	if (rt_cfg.flags & SAVE_REQUESTED)
	{
		if (!(bitmap_output(create_bitmap(&param), mlx_cfg.img_data)))
			bmp_sys_error(&scene);
		normal_exit(&param);
	}
//	printf("%p\n", mlx_cfg.mlx_ptr);
//	printf("%p\n", mlx_cfg.img_ptr);
	mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr, mlx_cfg.img_ptr, 
			0, 0);
	mlx_hook(mlx_cfg.win_ptr, KEYPRESS, KEYPRESSMASK, key_pressed_hook, &param);
	mlx_hook(mlx_cfg.win_ptr, DESTROYNOTIFY, DESTROYNOTIFYMASK, normal_exit2,
			&param);
	mlx_loop(mlx_cfg.mlx_ptr);
}

void end(void)__attribute__((destructor));
void end(void)
{
	printf("in end\n");
	system("leaks miniRT");
}
