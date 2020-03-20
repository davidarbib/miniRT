/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_get_data_addr.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 00:16:31 by ol                #+#    #+#             */
/*   Updated: 2020/01/29 00:17:24 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx_int.h"

char	*mlx_get_data_addr(t_img *img, int *bits_per_pixel,
							int *size_line, int *endian)
{
	*bits_per_pixel = img->bpp;
	*size_line = img->size_line;
	*endian = img->image->byte_order;
	return (img->data);
}
