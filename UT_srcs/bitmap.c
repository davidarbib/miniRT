/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:18:06 by darbib            #+#    #+#             */
/*   Updated: 2020/05/27 17:25:02 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include "libft.h"
#include "mlx.h"
#include "graphic.h"
#include <stdio.h>

void	put_img(t_bmp *bmp, char *img, int fd)
{
	int		j;
	int		i;
	char	*buf;
	char	*p_buf;
	
	//a proteger qd les gestions derreurs seront faites
	buf = (char *)ft_calloc(bmp->sizeimg, sizeof(char));
	p_buf = buf;
	j = bmp->height - 1;
	while (j >= 0)
	{
		i = 0;
		while (i < bmp->width)
		{			
			ft_memmove(p_buf, img + ((i + (j * bmp->width)) * 4), BYTES_N);
			p_buf += BYTES_N;
			i++;
		}
		j--;
	}
	printf("buf[0] = %x\n", buf[0]);
	write(fd, buf, bmp->sizeimg);
	free(buf);
}

void	put_header(t_bmp *bmp, int fd)
{
	unsigned char	buf[HEADERSIZE];
	int 			i;
	
	ft_bzero(buf, HEADERSIZE);
	i = 0;
	ft_memmove(buf + i, (unsigned char *)&bmp->type, 2);
	i += 2;
	ft_memmove(buf + i, (unsigned char *)&bmp->size, 4);
	i += 8;
	ft_memmove(buf + i, (unsigned char *)&bmp->headersize, 4); 
	i += 4;
	ft_memmove(buf + i, (unsigned char *)&bmp->infosize, 4); 
	i += 4;
	ft_memmove(buf + i, (unsigned char *)&bmp->width, 4); 
	i += 4;
	ft_memmove(buf + i, (unsigned char *)&bmp->height, 4); 
	i += 4;
	ft_memmove(buf + i, (unsigned char *)&bmp->planes, 2); 
	i += 2;
	ft_memmove(buf + i, (unsigned char *)&bmp->bitcount, 2); 
	i += 2;
	ft_memmove(buf + i, (unsigned char *)&bmp->compression, 4); 
	i += 4;
	ft_memmove(buf + i, (unsigned char *)&bmp->sizeimg, 4); 
	write(fd, buf, HEADERSIZE);
}

void		bitmap_output(t_bmp *bmp, char *img)
{
	int fd;
	//int ret_write;

	(void)img;
	bmp->headersize = HEADERSIZE;
	bmp->infosize = INFOSIZE;
	bmp->sizeimg = bmp->width * bmp->height * BYTES_N;
	bmp->size = bmp->sizeimg + HEADERSIZE + INFOSIZE;
	//if ((fd = open(BMPNAME, O_WRONLY | O_CREAT, S_IRWXU)) < 0)
		//output_sys_error(scene);
	fd = open(BMPNAME, O_WRONLY | O_CREAT, S_IRWXU);
	// if ((ret_write = putstr_fd(file_header, fd)) < 0)
		//output_error(scene);
	put_header(bmp, fd);
	put_img(bmp, img, fd);
	//write(fd, img, bmp->sizeimg);
	close(fd);
}

int main()
{

	#define IMGSIZE 400
	char			img[IMGSIZE];
	int				color = 0xFF0000;
	t_mlx			mlx;
	char			*img_p;
	t_bmp			bmp;
	
	ft_bzero(img, IMGSIZE);
	bmp.type[0] = 'B';
	bmp.type[1] = 'M';
	bmp.width = 100;
	bmp.height = 100;
	bmp.planes = 1;
	bmp.bitcount = 24;
	bmp.compression = 0;
	init_graphics(&mlx, 100, 100);
	printf("color : %x\n", color);
	printf("mlx color : %x\n", mlx_get_color_value(mlx.mlx_ptr, color));
	apply_color((unsigned char *)&color, &mlx, 0, 0);
	img_p = mlx_get_data_addr(mlx.img_ptr, &mlx.bits_per_pixel, &mlx.size_line,
			&mlx.endian);
	bitmap_output(&bmp, img_p);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.win_ptr, mlx.img_ptr, 0, 0);
	mlx_loop(mlx.mlx_ptr);
	//int fd = open(BMPNAME, O_WRONLY | O_CREAT, S_IRWXU);
	//write(fd, img_p, 40000);
}
