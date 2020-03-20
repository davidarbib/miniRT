/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_xpm.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pqueiroz <pqueiroz@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 17:53:05 by pqueiroz          #+#    #+#             */
/*   Updated: 2020/01/28 20:31:38 by pqueiroz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <OpenGL/gl3.h>
#include <sys/mman.h>
#include <fcntl.h>

#include "../mlx_rgb_priv.h"
#include "mlx_xpm_priv.h"

/*
** Public functions ============================================================
*/

/*
** INCOMPATIBLE
**
** mlx_int_xpm_set_pixel - This functions arguments are different from the
** original minilibx because the original has five parameters, two of which are
** unused.
**
** Old prototype:
** mlx_int_xpm_set_pixel(mlx_img_list_t *img, char *data, int op, int c, int x)
*/

void
	mlx_int_xpm_set_pixel(char *data, int c, int x)
{
	*((unsigned int *)(data + (4 * x))) = c;
}

/*
** Quick reminder that mlx_int_str_to_wordtab contains pointers to the original
** string and therefore only the array pointer needs to be free'd.
*/

void
	*mlx_int_parse_xpm(mlx_ptr_t *xvar, void *info, int info_size, char *(*f)())
{
	t_xpm_parse_ctx	ctx;

	memset(&ctx, 0, sizeof(ctx));
	ctx.xvar = xvar;
	ctx.info = info;
	ctx.info_size = info_size;
	ctx.f = f;
	if (!mlx_int_parse_xpm_first_step(&ctx) ||
		!mlx_int_parse_xpm_second_step(&ctx) ||
		!mlx_int_parse_xpm_third_step(&ctx) ||
		!mlx_int_parse_xpm_fourth_step(&ctx) ||
		!mlx_int_parse_xpm_fifth_step(&ctx))
		return (NULL);
	return (ctx.img);
}

static void
	mlx_int_file_get_rid_comment(char *ptr, int size)
{
	int	start;
	int	end;

	while ((start = mlx_int_str_str_cote(ptr, "/*", size)) != -1)
	{
		end = mlx_int_str_str(ptr + start + 2, "*/", size - start - 2);
		if (end != -1)
			memset(ptr + start, ' ', end + 4);
	}
	while ((start = mlx_int_str_str_cote(ptr, "//", size)) != -1)
	{
		end = mlx_int_str_str(ptr + start + 2, "\n", size - start - 2);
		if (end != -1)
			memset(ptr + start, ' ', end + 3);
	}
}

void
	*mlx_xpm_file_to_image(mlx_ptr_t *xvar, char *file, int *w, int *h)
{
	int				fd;
	int				size;
	char			*ptr;
	mlx_img_list_t	*img;

	if ((fd = open(file, O_RDONLY)) == -1 ||
		(size = lseek(fd, 0, SEEK_END)) == -1 ||
		(ptr = mmap(0, size, PROT_WRITE | PROT_READ, MAP_PRIVATE, fd, 0)) ==
		(void *)MAP_FAILED)
	{
		if (fd >= 0)
			close(fd);
		return (NULL);
	}
	mlx_int_file_get_rid_comment(ptr, size);
	if ((img = mlx_int_parse_xpm(xvar, ptr, size, mlx_int_get_line)))
	{
		(w) ? (*w = img->width) : 0;
		(h) ? (*h = img->height) : 0;
	}
	munmap(ptr, size);
	close(fd);
	return (img);
}

void
	*mlx_xpm_to_image(mlx_ptr_t *xvar, char **xpm_data, int *width, int *height)
{
	mlx_img_list_t	*img;

	if ((img = mlx_int_parse_xpm(xvar, xpm_data, 0, mlx_int_static_line)))
	{
		(width) ? (*width = img->width) : 0;
		(height) ? (*height = img->height) : 0;
	}
	return (img);
}
