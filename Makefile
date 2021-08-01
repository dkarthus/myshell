DIR_HEADERS	= ./includes/

DIR_SRCS	= ./srcs/

SRC			=	minishell.c \
				parser.c \
				env_utils.c \
				env_utils1.c \
				parser_err_handler.c \
				parser_utils.c \
				parser_utils1.c \
				parser_utils2.c \
				parser_utils_etc.c \
				token_util.c \
				token_utils1.c \
				token_utils2.c \
				tokenizer.c \
				executor/cd.c \
				executor/pwd.c \
				error_exit.c

SRCS		= $(addprefix $(DIR_SRCS), $(SRC))

OBJS		= $(SRCS:.c=.o)

NAME		= minishell

LIBFT		= libft.a

GCC			= gcc

RM			= rm -f

CFLAGS		= -Wall -Werror -Wextra -g

%.o:%.c
			$(GCC) $(CFLAGS) -I$(DIR_HEADERS) -c $< -o $@

$(NAME):	$(OBJS)
			make -C ./libft
			cp ./libft/libft.a .
			$(GCC) $(CFLAGS) -L. $(LIBFT) -lreadline -I./$(DIR_HEADERS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C ./libft
			$(RM) $(LIBFT)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
