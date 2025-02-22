NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

SRCS = srcs/main.c \
       srcs/lexer/lexer.c \
       srcs/lexer/lexer_util.c \
	   srcs/parser/parser.c \
	   srcs/parser/parser_util.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LDFLAGS) -o $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT_DIR)

clean:
	@make clean -C $(LIBFT_DIR)
	rm -f $(OBJS)

fclean: clean
	@make fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
