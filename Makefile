SRC		= 	src/builtin_cd.c \
			src/builtin_echo.c \
			src/builtin_env.c \
			src/builtin_exit.c \
			src/builtin_export.c \
			src/builtin_pwd.c \
			src/builtin_unset.c \
			src/exec.c \
			src/exec_add_path.c \
			src/exec_builtins.c \
			src/exec_commands.c \
			src/exec_heredoc.c \
			src/exec_pipes.c \
			src/exec_redirections.c \
			src/exec_signals.c \
			src/exec_utils.c \
			src/expander.c \
			src/expander_heredoc.c \
			src/expander_utils.c \
			src/expander_utils_2.c \
			src/expander_utils_3.c \
			src/free.c \
			src/init_env.c \
			src/init_env_2.c \
			src/lexer.c \
			src/lexer_insert_spaces.c \
			src/lexer_split.c \
			src/main.c \
			src/parser.c \
			src/parser_functions.c \
			src/parser_utils.c \
			src/parser_utils2.c \
			src/parser_utils3.c \
			src/token_validator.c \
			src/token_validator_2.c

NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -rf
AR		= ar rcs

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

OBJ		= $(SRC:.c=.o)

%.o: %.c
			$(CC) $(CFLAGS) -c $< -o $@

$(NAME):	$(LIBFT) $(OBJ)
			$(CC) $(CFLAGS) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft -lreadline

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

all:		$(NAME)

clean:
			$(RM) $(OBJ)
			$(MAKE) -C $(LIBFT_DIR) clean

fclean:		clean
			$(RM) $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re:			fclean all

.PHONY:		all clean fclean re
