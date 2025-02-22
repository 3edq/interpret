#include "../include/lexer.h"
#include "../include/parser.h"
#include <readline/history.h>
#include <readline/readline.h>
#include <stdio.h>
#include <stdlib.h>

void	free_commands(t_command *cmd)
{
	t_command	*tmp;
	int			i;

	while (cmd)
	{
		tmp = cmd;
		cmd = cmd->next;
		if (tmp->args)
		{
			i = 0;
			while (tmp->args[i])
			{
				free(tmp->args[i]);
				i++;
			}
			free(tmp->args);
		}
		if (tmp->input_file)
			free(tmp->input_file);
		if (tmp->output_file)
			free(tmp->output_file);
		free(tmp);
	}
}

void	print_commands(t_command *cmd)
{
	int	i;
	int	cmd_no;

	cmd_no = 1;
	while (cmd)
	{
		printf("Command %d:\n", cmd_no);
		if (cmd->args)
		{
			i = 0;
			while (cmd->args[i])
			{
				printf("  Arg[%d]: %s\n", i, cmd->args[i]);
				i++;
			}
		}
		if (cmd->input_file)
			printf("  Input: %s\n", cmd->input_file);
		if (cmd->output_file)
		{
			printf("  Output: %s ", cmd->output_file);
			if (cmd->append == 1)
				printf("(append)\n");
			else
				printf("(overwrite)\n");
		}
		cmd = cmd->next;
		cmd_no++;
	}
}

void	free_lexer_list(t_lexer *lexer)
{
	t_lexer	*tmp;

	while (lexer)
	{
		tmp = lexer;
		lexer = lexer->next;
		if (tmp->str)
			free(tmp->str);
		free(tmp);
	}
}

void	free_tools(t_tools *tools)
{
	free_lexer_list(tools->lexer_list);
	free(tools->args);
}

int	main(void)
{
	char		*input;
	t_tools		tools;
	t_command	*cmd_list;

	while (1)
	{
		input = readline("minishell> ");
		if (!input)
		{
			fprintf(stderr, "入力エラー\n");
			return (1);
		}
		if (*input)
			add_history(input);
		tools.args = input;
		tools.lexer_list = NULL;
		if (!token_reader(&tools))
		{
			fprintf(stderr, "トークン解析エラー\n");
			free(input);
			continue ;
		}
		cmd_list = parse_tokens(tools.lexer_list);
		if (!cmd_list)
		{
			fprintf(stderr, "パースエラー\n");
			free_tools(&tools);
			continue ;
		}
		print_commands(cmd_list);
		free_commands(cmd_list);
		free_tools(&tools);
	}
	return (0);
}
