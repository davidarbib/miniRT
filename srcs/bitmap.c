/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:18:06 by darbib            #+#    #+#             */
/*   Updated: 2020/07/15 19:56:30 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bitmap.h"
#include "libft.h"
#include "mlx.h"
#include "graphic.h"

static int		put_img(t_bmp *bmp, char *img, int fd)
{
	int		j;
	int		i;
	char	*buf;
	char	*p_buf;
	
	if (!(buf = (char *)ft_calloc(bmp->sizeimg, sizeof(char))))
		return (0);
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
	if ((write(fd, buf, bmp->sizeimg) != (ssize_t)bmp->sizeimg))
		return (0);
	free(buf);
	return (1);
}

static int		put_header(t_bmp *bmp, int fd)
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
	ft_memmove(buf + i + 2, (unsigned char *)&bmp->compression, 4); 
	ft_memmove(buf + i + 6, (unsigned char *)&bmp->sizeimg, 4); 
	if ((write(fd, buf, HEADERSIZE) != HEADERSIZE))
		return (0);
	return (1);
}

t_bmp			create_bitmap(t_scene *scene)
{
	t_bmp	bmp;

	bmp.type[0] = 'B';
	bmp.type[1] = 'M';
	bmp.width = scene->resx;
	bmp.height = scene->resy;
	bmp.width = WIDTH;
	bmp.height = HEIGHT;
	bmp.planes = 1;
	bmp.bitcount = 24;
	bmp.compression = 0;
	bmp.headersize = HEADERSIZE;
	bmp.infosize = INFOSIZE;
	bmp.sizeimg = bmp.width * bmp.height * BYTES_N;
	bmp.size = bmp.sizeimg + HEADERSIZE + INFOSIZE;
	return (bmp);
}

int				bitmap_output(t_bmp bmp, char *img)
{
	int fd;
	int	ret;

	if ((fd = open(BMPNAME, O_WRONLY | O_CREAT, S_IRWXU)) < 0)
		return (0);
	ret = 1;
	ret &= put_header(&bmp, fd);
	ret &= put_img(&bmp, img, fd);
	close(fd);
	return (ret);
}
