/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_visu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:42:09 by darbib            #+#    #+#             */
/*   Updated: 2020/03/27 18:45:05 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ft_printf.h"

void	data_visu(t_rt *cfg)
{
	printf("Resolution : %dx%d\n", cfg->resx, cfg->resy);
	printf("Ambient ratio : %f\n", cfg->ambient_ratio);
	printf("Ambient rgb : %d,%d,%d\n", cfg->ambient_rgb[0],
				cfg->ambient_rgb[1],cfg->ambient_rgb[2]);
	ft_printf("---------- Cameras ------------\n");
	ft_lstiter(cfg->cams, print_cam);
	ft_printf("---------- Cylinders ------------\n");
	ft_lstiter(cfg->cyls, print_cyl);
	ft_printf("---------- Omnilights ------------\n");
	ft_lstiter(cfg->olights, print_olight);
	ft_printf("---------- Planes  ------------\n");
	ft_lstiter(cfg->planes, print_plane);
	ft_printf("---------- Spheres  ------------\n");
	ft_lstiter(cfg->spheres, print_sphere);
	ft_printf("---------- Triangles  ------------\n");
	ft_lstiter(cfg->trigs, print_triangle);
	ft_printf("---------- Squares  ------------\n");
	ft_lstiter(cfg->squares, print_square);
}
