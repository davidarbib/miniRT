/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/17 18:41:08 by darbib            #+#    #+#             */
/*   Updated: 2020/05/17 18:46:46 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UPDATE_H
# define UPDATE_H

# include "scene.h"
# include "graphic.h"
# include "raytrace.h"
# include "mlx.h"

int				update_display(t_scene *scene, t_mlx *cfg);

#endif
