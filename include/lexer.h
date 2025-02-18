#ifndef TOKENS_H
# define TOKENS_H

# define TOKEN_PIPE 1
# define REDIR_OUT 2
# define REDIR_IN 3
# define APPEND_OUT 4
# define HEREDOC 5

typedef struct s_lexer
{
    char *str;
    int token;
    int i;
    struct s_lexer *next;
    struct s_lexer *prev;
} t_lexer;

enum	e_token_type
{
	TOKEN_PIPE = 1,
	REDIR_OUT,
	REDIR_IN,
	APPEND_OUT,
	HEREDOC
};

#endif