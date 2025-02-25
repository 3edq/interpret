#include "../include/minishell.h"

void	judge_command_list(t_command *cmd_list, char ***envp, int *status)
{
	t_command	*cur;
	char		*cmd_path;

	cur = cmd_list;
	while (cur)
	{
		if (is_builtin(cur->args[0]))
			*status = execute_builtin(cur, envp);
		else
		{
			cmd_path = find_path(cur->args[0], *envp);
			if (cmd_path)
			{
				execute_command(cur, envp, status);
				free(cmd_path);
			}
			else
			{
				ft_putstr_fd(cur->args[0], STDERR_FILENO);
				ft_putstr_fd(": command not found\n", STDERR_FILENO);
				*status = 127;
			}
		}
		cur = cur->next;
	}
}

void	execute_command(t_command *cmd, char ***envp, int *status)
{
	char	*path;
	pid_t	pid;
	int		exit_code;

	if (!cmd->args || !cmd->args[0])
	{
		ft_putstr_fd("Command not found\n", STDERR_FILENO);
		*status = 127;
		return;
	}
	path = find_path(cmd->args[0], *envp);
	if (!path)
	{
		ft_putstr_fd(cmd->args[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		*status = 127;
		return;
	}
	pid = fork();
	if (pid == 0)
	{
		execve(path, cmd->args, *envp);
		perror(cmd->args[0]);
		free(path);
		exit(EXIT_FAILURE);
	}
	else if (pid > 0)
	{
		waitpid(pid, &exit_code, 0);
		if (WIFEXITED(exit_code))
			*status = WEXITSTATUS(exit_code);
		else
			*status = 1;
	}
	free(path);
}


