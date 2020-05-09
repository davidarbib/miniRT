# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2020/05/09 16:56:19 by darbib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT 
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror
UNAME_S = $(shell uname -s)

ifeq ($(DEBUG), 1)
	CFLAGS += -g3
endif

ifeq ($(SANITIZE), 1)
	CFLAGS += -fsanitize=address 
endif

# ------------------------------------------------------------------------------

LIB_DIR = /usr/lib/
INC_DIR = ./includes/
OBJ_DIR = ./objs/
SRC_DIR = ./srcs/

# ------------------------------------------------------------------------------

HEADERS = $(addprefix $(INC_DIR), libft.h)
HEADERS += $(addprefix $(INC_DIR), minirt.h)

LIBFT_DIR = ./libft/
LIBFT = libft.a
LIB_LIBFT += $(addprefix $(LIBFT_DIR), $(LIBFT))

LDFLAGS = $(addprefix -L, $(LIBFT_DIR)) 

INC = $(addprefix -I, includes)
OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

ifeq ($(UNAME_S),Linux)
	MLX_DIR = ./minilibx_linux/
	MLX = libmlx.a
	LIB_MLX = $(addprefix $(MLX_DIR), $(MLX))
	LDFLAGS += $(addprefix -L, $(MLX_DIR)) 
	LDFLAGS += -lm -lmlx -lX11 -lXext -lft
else
	MLX_DIR = ./minilibx_macos/
	MLX = libmlx.dylib
	LIB_MLX = $(addprefix $(MLX_DIR), $(MLX))
	LDFLAGS += -lft -dylib $(LIB_MLX)
endif

LIBS = $(LIB_MLX) $(LIB_LIBFT)

SRC = camera.c \
	cylinder.c \
	data_visu.c \
	destroy.c \
	endian.c \
	error.c \
	init.c \
	graphic.c \
	obj_utils.c \
	omnilight.c \
	parse_utils.c \
	parse_utils2.c \
	vect_product.c \
	vect_projection.c \
	quaternion.c \
	parsing.c \
	handle_line.c \
	scene_rotation.c \
	aabb.c \
	plane.c \
	rt_buffer.c \
	sphere.c \
	square.c \
	print_tools.c \
	turn.c \
	move.c \
	hook.c \
	raytrace.c \
	keyboard_actions.c \
	triangle.c

ifeq ($(DRAFT), 1)
	SRC += draft.c
else
	SRC += minirt.c
endif

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) $(OBJ) -o $@ $(LDFLAGS)

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	@echo "cc"
	@mkdir -p objs
	$(CC) $(INC) $(CFLAGS) -c $< -o $@ 

$(MLX_DIR)$(MLX) : 
	make -C $(MLX_DIR)

$(LIBFT_DIR)$(LIBFT) : 
	make -C $(LIBFT_DIR)

clean :
	rm -rf $(OBJ_DIR)
	rm -f $(LIBS)
	make clean -C $(MLX_DIR)
	make clean -C $(LIBFT_DIR)

fclean : clean
	rm -f $(NAME)
	make fclean -C $(LIBFT_DIR)

re : fclean all
