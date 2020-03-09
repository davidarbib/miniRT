/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/03/08 18:51:24 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "colors.h"

int		main(int ac, char **av)
{
	t_mlx	mlx_cfg;
	t_rt	rt_cfg;
	t_sphere *sphere;
	
	(void)ac;
	(void)av;
	parsing(ac, av, &rt_cfg);
	rt_cfg.resx = 1024;
	rt_cfg.resy = 780;
	init_graphics(&mlx_cfg, &rt_cfg);
	sphere = rt_cfg.spheres->content;
	printf("sphere coord : %f,%f,%f\n", sphere->pos->x, sphere->pos->y, sphere->pos->z);
	printf("sphere diam : %f\n", sphere->diam);
	printf("sphere rgb : %u,%u,%u\n", sphere->rgb[0], sphere->rgb[1], sphere->rgb[2]);
	alter_pixel(&mlx_cfg, RED, 10, 10);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
	mlx_loop(mlx_cfg.mlx_ptr);
}

void end(void)__attribute__((destructor));
void end(void)
{
	printf("in end\n");
	system("leaks miniRT");
}
