# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yachoi <yachoi@student.42seoul.kr>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/11/28 09:50:01 by yachoi            #+#    #+#              #
#    Updated: 2022/11/28 09:50:03 by yachoi           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lm -lft -lmlx -L$(LIBFT_DIR) -L$(MLX_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_DIR)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

MLX			= $(MLX_DIR)libmlx.dylib
MLX_DIR		= ./minilibx/
MLX_HDRS	= $(minilibx)/ 

HDRS_LIST	= minirt.h	\
			  parse.h	\
			  vector.h	\
			  draw.h	\
			  edit.h	\
			  utils.h

HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./source/
P_DIR		= parse/
V_DIR		= vector/
D_DIR		= draw/
E_DIR		= edit/
U_DIR		= utils/

SRCS_LIST	= minirt.c							\
			  $(P_DIR)parse.c					\
			  $(P_DIR)parse_description.c		\
			  $(P_DIR)parse_convert.c			\
			  $(P_DIR)parse_type_lights_cam.c	\
			  $(P_DIR)parse_type_sphere.c		\
			  $(P_DIR)parse_type_plane.c		\
			  $(P_DIR)parse_type_cylinder.c		\
			  $(V_DIR)vector_cal1.c				\
			  $(V_DIR)vector_cal2.c				\
			  $(V_DIR)vector_cal3.c				\
			  $(V_DIR)ray_cal.c					\
			  $(D_DIR)draw.c					\
			  $(D_DIR)draw_hit.c				\
			  $(D_DIR)draw_hit_cylinder.c		\
			  $(D_DIR)draw_light.c				\
			  $(D_DIR)draw_shadow.c				\
			  $(D_DIR)draw_shadow_cylinder.c	\
			  $(E_DIR)edit.c					\
			  $(E_DIR)edit_light_camera.c		\
			  $(E_DIR)edit_object.c				\
			  $(E_DIR)edit_utils.c				\
			  $(U_DIR)error.c					\
			  $(U_DIR)free.c					\
			  $(U_DIR)get_next_line.c			\
			  $(U_DIR)check.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= objects/
OBJS_LIST	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS	= $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)$(P_DIR)
	mkdir -p $(OBJS_DIR)$(V_DIR)
	mkdir -p $(OBJS_DIR)$(D_DIR)
	mkdir -p $(OBJS_DIR)$(E_DIR)
	mkdir -p $(OBJS_DIR)$(U_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX) :
	$(MAKE) -C $(MLX_DIR)
	cp $(MLX) .

clean :
	$(RM) $(RMFLAGS) $(OBJS_DIR) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean

fclean : clean
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)
	$(RM) $(RMFLAGS) $(MLX)
	$(RM) $(RMFLAGS) libmlx.dylib

re : fclean $(NAME)

.PHONY : all clean fclean re
