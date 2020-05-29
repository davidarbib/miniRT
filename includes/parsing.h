/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/15 13:07:23 by darbib            #+#    #+#             */
/*   Updated: 2020/05/27 18:18:08 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "libft.h"
# include <stdint.h>

# define BUFFSIZE		1024

# define SAVE_REQUESTED 16
# define IN_PARSING		8
# define CAM			4
# define RES			2
# define AMB			1

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

void	parsing(int ac, char **av, t_rt *cfg);
void	init_cfg(t_rt *cfg);
void	handle_line(t_rt *cfg);
int		get_rgb(unsigned char *rgb, char **line);
void	get_vector(char **line, t_rt *cfg, t_vect *vect);
int		is_ratio(float ratio);
int		is_orientation_vect(t_vect *vect);
void	check_data(char *line, t_rt *cfg);
void	parse_amb(t_rt *cfg, char *line);
void	parse_res(t_rt *cfg, char *line);
void	parse_camera(t_rt *cfg, char *line);
void	parse_plane(t_rt *cfg, char *line);
void	parse_olight(t_rt *cfg, char *line);
void	parse_square(t_rt *cfg, char *line);
void	parse_triangle(t_rt *cfg, char *line);
void	parse_cylinder(t_rt *cfg, char *line);
void	parse_sphere(t_rt *cfg, char *line);

#endif
