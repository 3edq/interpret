#include "parser.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

t_cmd	*init_cmd(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 1024);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->args[0] = NULL;
	cmd->is_pipe = 0;
	cmd->input_fd = 0;
	cmd->output_fd = 1;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_redirection(t_lexer **lexer)
{
	t_cmd	*redir;

	redir = init_cmd();
	redir->args = malloc(sizeof(char *) * 2);
	redir->args[0] = strdup((*lexer)->str);
	redir->args[1] = NULL;
	if ((*lexer)->token == REDIR_IN || (*lexer)->token == HEREDOC)
		redir->input_fd = -1;
	else if ((*lexer)->token == REDIR_OUT || (*lexer)->token == APPEND_OUT)
		redir->output_fd = -1;
	*lexer = (*lexer)->next;
	return (redir);
}

t_cmd	*parse_single_cmd(t_lexer **lexer)
{
	t_cmd	*cmd;
	t_cmd	*redir;
	t_cmd	*last;
	int		i;
	t_cmd	*pipe_cmd;

	cmd = init_cmd();
	redir = NULL;
	last = cmd;
	i = 0;
	while (*lexer && (*lexer)->token != TOKEN_PIPE)
	{
		if ((*lexer)->token >= REDIR_OUT && (*lexer)->token <= HEREDOC)
		{
			redir = parse_redirection(lexer);
			last->next = redir;
			last = redir;
		}
		else
		{
			cmd->args[i] = strdup((*lexer)->str);
			i++;
			cmd->args[i] = NULL;
		}
		*lexer = (*lexer)->next;
	}
	if (*lexer && (*lexer)->token == TOKEN_PIPE)
	{
		pipe_cmd = init_cmd();
		pipe_cmd->is_pipe = 1;
		last->next = pipe_cmd;
		*lexer = (*lexer)->next;
	}
	return (cmd);
}

t_cmd	*parse_cmd(t_lexer *lexer_list)
{
	t_cmd	*cmd_list;
	t_lexer	*current;
	t_cmd	*cmd;
	t_cmd	**last;

	cmd_list = NULL;
	current = lexer_list;
	while (current)
	{
		cmd = parse_single_cmd(&current);
		if (!cmd)
			return (NULL);
		last = &cmd_list;
		while (*last)
			last = &(*last)->next;
		*last = cmd;
	}
	return (cmd_list);
}

void	execute_cmd(t_cmd *cmd_list)
{
	t_cmd	*current;
	int		fd[2];

	current = cmd_list;
	while (current)
	{
		if (current->args)
		{
			if (current->input_fd != 0)
				dup2(current->input_fd, STDIN_FILENO);
			if (current->output_fd != 1)
				dup2(current->output_fd, STDOUT_FILENO);
			execvp(current->args[0], current->args);
		}
		else if (current->is_pipe)
		{
			pipe(fd);
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
		}
		current = current->next;
	}
}
