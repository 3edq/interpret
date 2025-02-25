NAME = minishell

LIBFT_DIR = libft
LIBFT_A = $(LIBFT_DIR)/libft.a

# ソースディレクトリ
SRC_DIR = srcs
LEXER_DIR = $(SRC_DIR)/lexer
PARSER_DIR = $(SRC_DIR)/parser
BUILTIN_DIR = $(SRC_DIR)/builtin
EXECUTER_DIR = $(SRC_DIR)/executer

# ソースファイル
SRCS = $(SRC_DIR)/main.c \
       $(LEXER_DIR)/lexer.c \
       $(LEXER_DIR)/lexer_util.c \
       $(PARSER_DIR)/parser.c \
       $(PARSER_DIR)/parser_util.c \
       $(BUILTIN_DIR)/builtin.c \
       $(BUILTIN_DIR)/builtin_cd.c \
       $(BUILTIN_DIR)/builtin_echo.c \
       $(BUILTIN_DIR)/builtin_env.c \
       $(BUILTIN_DIR)/builtin_exit.c \
       $(BUILTIN_DIR)/builtin_export.c \
       $(BUILTIN_DIR)/builtin_pwd.c \
       $(BUILTIN_DIR)/builtin_unset.c \
       $(EXECUTER_DIR)/executer.c \
       $(EXECUTER_DIR)/path.c

# オブジェクトファイル
OBJS = $(SRCS:.c=.o)

# コンパイラとフラグ
CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude -I$(LIBFT_DIR)
LDFLAGS = -L$(LIBFT_DIR) -lft -lreadline

# ルール
all: $(LIBFT_A) $(NAME)

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
