/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bitmap.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/25 18:51:25 by darbib            #+#    #+#             */
/*   Updated: 2020/05/27 15:34:42 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BITMAP_H
# define BITMAP_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

# define BMPNAME 	"RT.bmp"
# define HEADERSIZE 0x36
# define INFOSIZE 	0x28
# define BYTES_N	3

typedef struct		s_bmp
{
	unsigned char	type[2];
	int				size;
	int				width;
	int				height;
	int				planes;
	int				bitcount;
	int				compression;
	int				sizeimg;
	int				headersize;
	int				infosize;
}					t_bmp;

void		bitmap_output(t_bmp *bmp, char *img);
#endif
