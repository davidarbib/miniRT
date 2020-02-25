/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:09:20 by darbib            #+#    #+#             */
/*   Updated: 2020/02/25 17:45:27 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include "libft.h"

/*
** ---------------
*/

# include "camera.h"
# include "cylinder.h"
# include "omnilight.h"
# include "plane.h"
# include "sphere.h"
# include "square.h"
# include "triangle.h"

/*
** ---------------
*/

# define TITLE		"RT scene"
# define SAVEARG	"-save"
# define FILEEXT	".rt"

/*
** ---------------
*/

# define UNIRES		2
# define UNIAMB		1

/*
** ---------------
*/

# define MAXNBLHEAD 100

/*
** ---------------
*/

# define OBJS		"R,A,c,l,pl,sp,sq,cy,tr"
# define SEP		','
# define NB_OBJS	9	

/*
** ---------------
*/

# define BUFFSIZE	1024

/*
** ---------------
*/

typedef struct		s_mlx
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
	int				bits_per_pixel;
	int				size_line;
	int				endian;
}					t_mlx;

typedef struct		s_rt
{
	char[BUFFSIZE]	buf;
	char			**labels_tab;
	int				resx;
	int				resy;
	float			ambient_ratio;
	t_list			*objs;
	unsigned char	ambient_rgb[3];
	int				linenb;
	uint8_t			data;
	uint8_t			save;
	uint8_t			uniobj;
}					t_rt;

/*
** vector type
*/
typedef struct		s_vect
{
	float			x;
	float			y;
	float			z;
}					t_vect;


int				init_graphics(t_mlx *mlx_cfg, t_rt *rt_cfg);
int				create_img(t_mlx *mlx_cfg, t_rt *rt_cfg);
int 			refresh_img(t_mlx *mlx_cfg, t_rt *rt_cfg);

int				client_endian(void);
unsigned int	adapt_endian(unsigned int color);

void			alter_pixel(t_mlx *cfg, int color, int x, int y);

void			parsing(int ac, char **av, t_rt *cfg);

int				label_chr(char **tab, char *label);

#endif
