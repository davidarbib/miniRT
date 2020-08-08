/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:51:25 by darbib            #+#    #+#             */
/*   Updated: 2020/08/08 17:12:21 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include "general.h"

# define BMPNAME 	"RT.bmp"
# define HEADERSIZE 0x36
# define INFOSIZE 	0x28
# define BYTES_N	3
# define COLORDEPTH	24

typedef struct		s_bmp
{
	unsigned char	type[2];
	int				size;
	int				sl;
	int				width;
	int				height;
	int				planes;
	int				bitcount;
	int				compression;
	int				sizeimg;
	int				bpp;
	int				headersize;
	int				infosize;
}					t_bmp;

void				bmp_sys_error(t_scene *scene);
t_bmp				create_bitmap(t_param *pm);
int					put_img(t_bmp *bmp, unsigned char *img, int fd);
int					bitmap_output(t_bmp bmp, t_img *img, int mode);

#endif
