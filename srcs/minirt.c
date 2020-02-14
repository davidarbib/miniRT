/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 21:47:19 by darbib            #+#    #+#             */
/*   Updated: 2020/02/14 16:36:15 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "mlx.h"
#include "colors.h"

int		main (int ac, char **av)
{
	t_mlx	mlx_cfg;
	t_rt	rt_cfg;
	
	(void)ac;
	(void)av;
	rt_cfg.resx = 1024;
	rt_cfg.resy = 780;
	init_graphics(&mlx_cfg, &rt_cfg);
	alter_pixel(&mlx_cfg, RED, 10, 10);
	alter_pixel(&mlx_cfg, GREEN, 20, 20);
	alter_pixel(&mlx_cfg, BLUE, 30, 30);
	mlx_loop(mlx_cfg.mlx_ptr);
}
