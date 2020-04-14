/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:07:27 by darbib            #+#    #+#             */
/*   Updated: 2020/04/13 17:14:03 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# include "general.h"

# define E_ARGFILE	"a .rt file url must be specified"
# define E_INVFILE	"invalid file"
# define E_SCNDARG 	"second arg must be '-save'"
# define E_BADEXT	"the file must be a .rt"
# define E_BADOBJ	"unknown object, pick one in : R|A|c|l|pl|sp|sq|cy|tr"
# define E_BADATB	"attribute syntax error for this object"
# define E_FILERD	"file read exception"
# define E_MEMALC	"memory allocation exception"
# define E_BADCHAR	"forbidden char"
# define E_BADVECT	"vector syntax error"
# define E_BADSTX	"syntax error"
# define E_BADRGB	"rgb error"
# define E_BADRATIO	"incorrect ratio"
# define E_BADRES	"incorrect resolution"
# define E_TOOAMB	"only one ambient light specification is allowed"
# define E_TOORES	"only one resolution specification is allowed"
# define E_NORES	"no resolution is specified"
# define E_NOAMB	"no ambient light is specified"
# define E_NOCAM	"one camera at least is needed"
# define E_FOVRANGE	"camera FOV must be comprise in [0;180] range"

void	parse_error(char *msg, t_rt *cfg);
void	sys_error(t_rt *cfg);

#endif
