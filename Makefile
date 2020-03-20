# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: darbib <darbib@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/11/06 14:53:36 by darbib            #+#    #+#              #
#    Updated: 2020/03/20 16:44:54 by darbib           ###   ########.fr        #
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

HEADERS = $(INC_DIR)libft.h 
HEADERS += $(INC_DIR)minirt.h 

LIBFT_DIR = ./libft/
LIBFT = libft.a
LIBS = $(MLX_DIR)$(MLX)
LIBS += $(LIBFT_DIR)$(LIBFT)

INC =$(addsuffix includes, -I)
OBJ = $(SRC:%.c=%.o)

ifeq ($(UNAME_S),Linux)
	MLX_DIR = ./minilibx_linux/
	MLX = libmlx.a
	INPUT = $(CFLAGS) -lX11 -lXext $(MLX_DIR)$(MLX) $(LIBFT_DIR)$(LIBFT)
else
	MLX_DIR = ./minilibx_macos/
	MLX = libmlx.dylib
	INPUT = $(CFLAGS) -dylib $(MLX_DIR)$(MLX) $(LIBFT_DIR)$(LIBFT)
endif

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

.PHONY: all clean fclean re

# ------------------------------------------------------------------------------

all : $(NAME)

$(NAME): $(OBJ) $(HEADERS) $(LIBS)
	$(CC) $(INPUT) $(OBJ) -o $(NAME) 

#$(OBJ_DIR)%.o : $(SRC_DIR)%.c
#	$(CC) -Iincludes $(CFLAGS) -c -o $@ $< 

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
