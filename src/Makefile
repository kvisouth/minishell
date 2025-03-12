# Test Makefile for Parser

NAME = parser_test

SRC =	parser.c \
		parser_functions.c \
		parser_utils.c \
		parser_utils2.c \
		token_validator.c \
		token_validator_2.c \
		lexer.c \
		lexer_insert_spaces.c \
		lexer_split.c \
		test_parser.c

OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

LIBFT_PATH = ../libft
LIBFT = $(LIBFT_PATH)/libft.a

.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) -o $@ $^ -lreadline

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(LIBFT):
	make -C $(LIBFT_PATH)

clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_PATH) clean

fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_PATH) fclean

re: fclean all