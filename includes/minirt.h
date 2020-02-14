/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/11 14:09:20 by darbib            #+#    #+#             */
/*   Updated: 2020/02/14 16:37:06 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <fcntl.h>
# include <stdlib.h>
# include "libft.h"

# define TITLE "RT scene"

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
	int				resx;
	int				resy;
	float			ambient_ratio;
	unsigned char	ambient_rgb[3];
	t_list			*objs;
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

/*
** --- camera ---
** pos : position vector
** ort : orientation vector [-1;1]
** fov : sight-field ([0;180] degrees)
*/
typedef struct		s_cam
{
	t_vect			pos;
	t_vect			ort;
	int				fov;
}					t_cam;

/*
** --- light ---
** pos : position vector
** ratio : luminance ratio [0.0;1.0]
** rgb : rgb color
*/
typedef struct		s_light
{
	t_vect			pos;
	float			ratio;
	unsigned char	rgb[3];
}					t_light;

/*
** --- sphere ---
** pos : position vector
** diam : sphere diameter
** rgb : rgb color
*/
typedef struct		s_sphere
{
	t_vect			pos;
	float			diam;
	unsigned char	rgb[3];
}					t_sphere;

/*
** --- plane ---
** pos : position vector
** ort : orientation vector [-1;1]
** rgb : rgb color
*/
typedef struct		s_plane
{
	t_vect			pos;
	t_vect			ort;
	unsigned char	rgb[3];
}					t_plane;

/*
** --- square ---
** pos : position vector
** ort : orientation vector [-1;1]
** height : ...
** rgb : rgb color
*/
typedef struct		s_square
{
	t_vect			pos;
	t_vect			ort;
	float			height;
	unsigned char	rgb[3];
}					t_square;

/*
** --- cylinder ---
** pos : position vector
** ort : orientation vector [-1;1]
** diam : diameter
** height : ...
** rgb : rgb color
*/
typedef struct		s_cyld
{
	t_vect			pos;
	t_vect			ort;
	float			height;
	unsigned char	rgb[3];
}					t_cyld;

/*
** --- triangle ---
** pt1 : 1st point
** pt2 : 2nd point
** pt3 : 3nd point
** rgb : rgb color
** (mb 2 vector only are needed)
*/
typedef struct		s_trig
{
	t_vect			pt1;
	t_vect			pt2;
	t_vect			pt3;
	unsigned char	rgb[3];
}					t_trig;

int				init_graphics(t_mlx *mlx_cfg, t_rt *rt_cfg);
int				create_img(t_mlx *mlx_cfg, t_rt *rt_cfg);
int 			refresh_img(t_mlx *mlx_cfg, t_rt *rt_cfg);

int				client_endian(void);
unsigned int	adapt_endian(unsigned int color);

void			alter_pixel(t_mlx *cfg, int color, int x, int y);
#endif
