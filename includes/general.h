/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:27:22 by darbib            #+#    #+#             */
/*   Updated: 2020/03/04 17:57:09 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "libft.h"
# include "vector.h"

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

/*
** ---------------
*/
typedef struct		s_rt
{
	char			buf[BUFFSIZE];
	char			**labels_tab;
	int				resx;
	int				resy;
	float			ambient_ratio;
	t_list			*cyls;
	t_list			*cams;
	t_list			*olights;
	t_list			*planes;
	t_list			*spheres;
	t_list			*trigs;
	t_list			*squares;
	unsigned char	ambient_rgb[3];
	int				linenb;
	uint8_t			data;
	uint8_t			save;
	uint8_t			uniobj;
}					t_rt;

int				init_graphics(t_mlx *mlx_cfg, t_rt *rt_cfg);
int				create_img(t_mlx *mlx_cfg, t_rt *rt_cfg);
int 			refresh_img(t_mlx *mlx_cfg, t_rt *rt_cfg);

int				client_endian(void);
unsigned int	adapt_endian(unsigned int color);

void			alter_pixel(t_mlx *cfg, int color, int x, int y);

void			parsing(int ac, char **av, t_rt *cfg);

int				label_chr(char **tab, char *label);

void			cpy_next_word(char **s, char *buf);

int				get_rgb(unsigned char *rgb, char **line);
t_vect			*get_vector(char **line, t_rt *cfg);
void			check_data(char *line, t_rt *cfg);

#endif
