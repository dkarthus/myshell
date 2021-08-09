DIR_HEADERS	= ./includes/

DIR_SRCS	= ./srcs/

LDFLAGS		= -L/Users/wanisha/.brew/opt/readline/lib

CPPFLAGS	= -I/Users/wanisha/.brew/opt/readline/include

SRC			=	minishell.c \
				parser/parser.c \
				env_vars/env_utils.c \
				env_vars/env_utils1.c \
				parser/parser_err_handler.c \
				parser/parser_utils.c \
				parser/parser_utils1.c \
				parser/parser_utils2.c \
				parser/parser_utils_etc.c \
				tokens/token_util.c \
				tokens/token_utils1.c \
				tokens/token_utils2.c \
				tokens/tokenizer.c \
				executor/cd/cd.c \
				executor/cd/update_old_pwd.c \
				executor/cd/update.c \
				executor/cd/cd_else.c \
				executor/cd/update_pwd.c \
				executor/cd/check_tilde_plus_minus_path.c \
				executor/pwd.c \
				executor/env.c \
				executor/unset/unset.c \
				executor/unset/unset_utils.c \
				executor/unset/unset_utils_1.c \
				executor/unset/unset_utils_2.c \
				executor/export/export.c \
				executor/export/if_for_export.c \
				executor/export/export_utils.c \
				executor/export/export_utils_1.c \
				executor/export/export_utils_2.c \
				executor/export/export_utils_3.c \
				executor/export/export_utils_4.c \
				executor/export/export_utils_5.c \
				executor/export/print_export.c \
				executor/export/print_export_1.c \
				executor/bin_finder.c \
				executor/command_executor/command_executor.c \
				executor/command_executor/command_executor_1.c \
				executor/command_executor/command_executor_2.c \
				executor/executor_v2.c \
				executor/executor_etc.c \
				executor/here_doc.c \
				executor/echo/echo.c \
				executor/exit/exit.c \
				error_exit.c \
				signals/signal.c \

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
			$(GCC) $(CFLAGS) -L. $(LIBFT) $(LDFLAGS) -lreadline -I./$(DIR_HEADERS) $(CPPFLAGS) $(OBJS) -o $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			make fclean -C ./libft
			$(RM) $(LIBFT)
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
