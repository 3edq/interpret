#include "lexer.h"
#include "parser.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

int	main(void)
{
	char *input;
	t_tools tools;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			printf("exit\n");
			break ;
		}
		if (*input)
			add_history(input);
		tools.args = input;
		tools.lexer_list = NULL;
		if (!token_reader(&tools))
		{
			printf("Lexer error: invalid tokenization.\n");
		}
		else
		{
			t_lexer *current = tools.lexer_list;
			printf("Lexer tokens:\n");
			while (current)
			{
				printf("Token: %s (Type: %d)\n", current->str, current->token);
				current = current->next;
			}
		}
		free(input);
	}
}
