/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:41:08 by darbib            #+#    #+#             */
/*   Updated: 2020/08/06 22:09:26 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "general.h"
# include "raytrace.h"
# include "mlx.h"

int		update_display(t_scene *scene, t_mlx *cfg, t_img *img);

#endif
