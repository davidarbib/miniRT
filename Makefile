# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2020/03/10 15:08:58 by darbib           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT 
CC = gcc
#CFLAGS = -Wall -Wextra -Werror -framework OpenGL -framework AppKit
CFLAGS = -Wall -Wextra -Werror

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

HEADERS = $(INC_DIR)libft.h 
HEADERS += $(INC_DIR)minirt.h 

MLX_DIR = ./minilibx_macos/
MLX = libmlx.dylib
LIBFT_DIR = ./libft/
LIBFT = libft.a
LIBS = $(MLX_DIR)$(MLX)
LIBS += $(LIBFT_DIR)$(LIBFT)

CFLAGS += -I $(INC_DIR)

OBJ = $(SRC:%.c=%.o)

SRC = camera.c \
	cylinder.c \
	data_visu.c \
	destroy.c \
	endian.c \
	error.c \
	graphic.c \
	minirt.c \
	obj_utils.c \
	omnilight.c \
	parse_utils.c \
	parse_utils2.c \
	parsing.c \
	plane.c \
	rt_buffer.c \
	sphere.c \
	square.c \
	triangle.c

# ------------------------------------------------------------------------------

vpath %.c $(SRC_DIR)
vpath %.o $(OBJ_DIR)

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(LIBS)
	$(CC) $(CFLAGS) -dylib $(MLX_DIR)$(MLX) $(LIBFT_DIR)$(LIBFT) $(OBJ) -o $(NAME) 

$(OBJ_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -c -o $@ $< 

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
