NAME		= miniRT

CC			= cc
CFLAGS		= -Wall -Werror -Wextra
LDFLAGS		= -lmlx -lm -L$(LIBFT_DIR) -L$(MLX_DIR)
INCLUDES	= -I$(HDRS_DIR) -I$(LIBFT_DIR) -I$(MLX_HDRS)

RM 			= rm
RMFLAGS		= -rf

LIBFT		= $(LIBFT_DIR)libft.a
LIBFT_DIR	= ./libft/

MLX			= $(MLX_DIR)libmlx.dylib
MLX_DIR		= ./minilibx/
MLX_HDRS	= $(minilibx)/ 

HDRS_LIST	= minirt.h	\
			  parse.h	\
			  utils.h

HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./source/
P_DIR		= parse/
V_DIR		= vector/
U_DIR		= utils/

SRCS_LIST	= minirt.c						\
			  $(P_DIR)parse.c				\
			  $(P_DIR)parse_description.c	\
			  $(U_DIR)error.c				\
			  $(U_DIR)get_next_line.c

SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))

OBJS_DIR	= objects/
OBJS_LIST	= $(patsubst %.c, %.o, $(SRCS_LIST))
OBJS	= $(addprefix $(OBJS_DIR), $(OBJS_LIST))

all : $(NAME)

$(NAME) : $(LIBFT) $(MLX) $(OBJS_DIR) $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(INCLUDES) $(OBJS) -o $(NAME)

$(OBJS_DIR) :
	mkdir -p $(OBJS_DIR)
	mkdir -p $(OBJS_DIR)$(V_DIR)
	mkdir -p $(OBJS_DIR)$(E_DIR)
	mkdir -p $(OBJS_DIR)$(B_DIR)
	mkdir -p $(OBJS_DIR)$(U_DIR)

$(OBJS_DIR)%.o : $(SRCS_DIR)%.c $(HDRS)
	$(CC) $(CFLAGS) -c $(INCLUDES) $< -o $@

$(LIBFT) :
	$(MAKE) bonus -C $(LIBFT_DIR)

$(MLX) :
	$(MAKE) -C $(MLX_DIR)

clean :
	$(RM) $(RMFLAGS) $(OBJS_DIR) $(OBJS)
	$(MAKE) -C $(LIBFT_DIR) clean
fclean : clean
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
