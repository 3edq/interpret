enum e_token_type
{
    TOKEN_PIPE = 1,
    REDIR_OUT,
    REDIR_IN,
    APPEND_OUT,
    HEREDOC
};

typedef struct s_cmd
{
    char **args;
    int is_pipe;
    int input_fd;
    int output_fd;
    struct s_cmd *next;
} t_cmd;

typedef struct s_lexer
{
    char *str;
    int token;
    struct s_lexer *next;
} t_lexer;