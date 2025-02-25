#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include "builtin.h"
# include "executer.h"
# include "lexer.h"
# include "parser.h"
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

char	**copy_env(char **envp);
void	free_env(char **envp);
void	free_commands(t_command *cmd);
void	free_lexer_list(t_lexer *lexer);
void	free_tools(t_tools *tools);

#endif
