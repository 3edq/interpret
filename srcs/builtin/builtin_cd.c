#include "minishell.h"

int	builtin_cd(char **args)
{
	if (!args[1])
	{
		ft_putstr_fd("minishell: cd: missing argument\n", STDERR_FILENO);
		return (1);
	}
	if (chdir(args[1]) != 0)
	{
		perror("minishell: cd");
		return (1);
	}
	return (0);
}
