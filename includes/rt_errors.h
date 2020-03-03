/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_errors.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: darbib <darbib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/15 19:07:27 by darbib            #+#    #+#             */
/*   Updated: 2020/03/03 16:53:58 by darbib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_ERRORS_H
# define RT_ERRORS_H

# define E_ARGFILE	"a .rt file url must be specified"
# define E_INVFILE	"invalid file"
# define E_SCNDARG 	"second arg must be '-save'"
# define E_BADEXT	"the file must be a .rt"
# define E_BADOBJ	"unknown object"
# define E_BADATB	"attribute syntax error for this object"
# define E_FILERD	"file read exception"
# define E_MEMALC	"memory allocation exception"
# define E_BADCHAR	"forbidden char"
# define E_BADVECT	"vector syntax error"

void	parse_error(char *msg, t_rt *cfg);
void	sys_error(t_rt *cfg);

#endif
