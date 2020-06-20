/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/06/20 18:46:47 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "graphic.h"
#include "scene.h"
#include "raytrace.h"
#include "macos_codes.h"
#include "actions.h"

int		main(int ac, char **av)
{
	t_mlx	mlx_cfg;
	t_rt	rt_cfg;
	t_scene	scene;
	t_param param;
	
	param.scene = &scene;
	param.mlx_cfg = &mlx_cfg;
	assign_key_fts();
	init_cfg(&rt_cfg);
	parsing(ac, av, &rt_cfg);
	init_scene(&scene, &rt_cfg);
	//data_visu(&rt_cfg);
	init_graphics(&mlx_cfg);
	raytrace(&scene, &mlx_cfg);
	mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0);
	mlx_hook(mlx_cfg.win_ptr, KeyPress, KeyPressMask, key_pressed_hook,
			&param);
	mlx_loop(mlx_cfg.mlx_ptr);
}

void end(void)__attribute__((destructor));
void end(void)
{
	printf("in end\n");
	//system("leaks miniRT");
}
