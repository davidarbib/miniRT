/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/05/09 19:19:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "colors.h"

int		main(int ac, char **av)
{
	t_mlx	mlx_cfg;
	t_rt	rt_cfg;
	
	init_cfg(&rt_cfg);
	parsing(ac, av, &rt_cfg);
	rt_cfg.resx = 1024;
	rt_cfg.resy = 780;
	//data_visu(&rt_cfg);
	(void)mlx_cfg;
	init_graphics(&mlx_cfg, rt_cfg.resx, rt_cfg.resy);
	raytrace(&scene, &mlx_cfg);
	if (!(mlx_put_image_to_window(mlx_cfg.mlx_ptr, mlx_cfg.win_ptr,
		mlx_cfg.img_ptr, 0, 0)))
		return (1);
	//mlx_loop_hook(mlx_cfg.mlx_ptr, loop_hook, &param);
	//mlx_key_hook(mlx_cfg.win_ptr, key_pressed_hook, &param);
	mlx_hook(mlx_cfg.win_ptr, KeyPress, KeyPressMask, key_pressed_hook,
			&param);
	//alter_pixel(&mlx_cfg, RED, 10, 10);
	//alter_pixel(&mlx_cfg, GREEN, 20, 20);
	//alter_pixel(&mlx_cfg, BLUE, 30, 30);
	mlx_loop(mlx_cfg.mlx_ptr);
}

void end(void)__attribute__((destructor));
void end(void)
{
	printf("in end\n");
	//system("leaks miniRT");
}
