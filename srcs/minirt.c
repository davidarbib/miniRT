/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/08/07 15:43:17 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
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
	t_img	img;
	t_scene	scene;
	t_param param;

	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	param.img = &img;
	init_cfg(&rt_cfg);
	parsing(ac, av, &rt_cfg);
	data_visu(&rt_cfg);
	init_img(&img, &rt_cfg, &scene);
	init_scene(&scene, &rt_cfg, &mlx_cfg);
	raytrace(&scene, &img);
	printf("img : %d,%d,%d\n", img.buf[0], img.buf[1], img.buf[2]);
	if (rt_cfg.flags & SAVE_REQUESTED)
	{
		if (!(bitmap_output(create_bitmap(&param), mlx_cfg.img_data)))
			bmp_sys_error(&scene);
		normal_exit(&param);
	}
	init_graphics(&mlx_cfg, &rt_cfg);
	img_to_mlx(&img, &mlx_cfg);
	mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr, mlx_cfg.img_ptr,
			0, 0);
	mlx_hook(mlx_cfg.win_ptr, KEYPRESS, KEYPRESSMASK, key_pressed_hook, &param);
	mlx_hook(mlx_cfg.win_ptr, DESTROYNOTIFY, STRUCTURENOTIFYMASK, normal_exit2,
			&param);
	mlx_loop(mlx_cfg.mlx_ptr);
}

void end(void)__attribute__((destructor));
void end(void)
{
	system("leaks miniRT");
}
