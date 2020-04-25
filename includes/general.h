/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   general.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 17:27:22 by darbib            #+#    #+#             */
/*   Updated: 2020/04/25 15:48:23 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GENERAL_H
# define GENERAL_H

# include "libft.h"
# include "vector.h"
# include <stdint.h>

/*
** ---------------
*/

# define TITLE		"RT scene"
# define SAVEARG	"-save"
# define FILEEXT	".rt"

/*
** ---------------
*/

# define SAVE_REQUESTED 16
# define IN_PARSING		8
# define CAM			4
# define RES			2
# define AMB			1

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
	int				bits_per_pixel;
	int				size_line;
	int				endian;
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	char			*img_data;
}					t_mlx;

/*
** ---------------
*/
typedef struct		s_rt
{
	int				resx;
	int				resy;
	int				linenb;
	int				current_obj_type;
	void			*current_obj_addr;
	float			ambient_ratio;
	char			**labels_tab;
	char			*line;
	t_list			*cyls;
	t_list			*cams;
	t_list			*olights;
	t_list			*planes;
	t_list			*spheres;
	t_list			*trigs;
	t_list			*squares;
	char			buf[BUFFSIZE];
	unsigned char	ambient_rgb[3];
	uint8_t			flags;
}					t_rt;

int				init_graphics(t_mlx *mlx_cfg, int resx, int resy);
void			init_cfg(t_rt *cfg);
int				create_img(t_mlx *mlx_cfg, int resx, int resy);
int				refresh_img(t_mlx *mlx_cfg, int resx, int resy);

int				client_endian(void);
unsigned int	adapt_endian(unsigned int color);

void			alter_pixel(t_mlx *cfg, int color, int x, int y);

void			parsing(int ac, char **av, t_rt *cfg);
void			handle_line(t_rt *cfg);

int				label_chr(char **tab, char *label);

void			cpy_next_word(char **s, char *buf);

int				get_rgb(unsigned char *rgb, char **line);
t_vect			*get_vector(char **line, t_rt *cfg);
void			check_data(char *line, t_rt *cfg);

void			parse_amb(t_rt *cfg, char *line);
void			parse_res(t_rt *cfg, char *line);

void			data_visu(t_rt *cfg);

void			destroy(t_rt *cfg);

int				is_ratio(float ratio);
int				is_orientation_vect(t_vect *vect);

#endif
