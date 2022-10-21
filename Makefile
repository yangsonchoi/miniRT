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

HDRS_DIR	= ./include/
HDRS		= $(addprefix $(HDRS_DIR), $(HDRS_LIST))

SRCS_DIR	= ./source/
V_DIR		= vector/
U_DIR		= utils.h/

SRCS_LIST	= minirt.c					\
			  $(U_DIR)utils.c

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
	cd minilibx && $(RM) $(RMFLAGS) *.o
fclean : clean
	$(RM) $(RMFLAGS) $(LIBFT)
	$(RM) $(RMFLAGS) $(MLX)
	$(RM) $(RMFLAGS) $(NAME)

re : fclean $(NAME)

.PHONY : all clean fclean re
