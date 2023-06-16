#include "minishell.h"

extern int	g_is_display;

int	exec_all_loop(t_mini *mini, t_exec *ex, int p[2], int *previous_fd)
{
	int	ret;

	if (!check_redirection(ex))
		return (0);
	if (ex->next)
		ret = pipe(p);
	if (ret == -1)
		return (0);
	ret = fork();
	if (ret == -1)
		return (0);
	if (ret == 0)
		exec_cmd(mini, ex, p, *previous_fd);
    ex->pid = ret;
	if (ex->next)
		close(p[1]);
	if (*previous_fd != 0)
		close(*previous_fd);
	*previous_fd = p[0];
	return (ret);
}

void	wait_exec(t_mini *mini)
{
	int     status;
    t_exec  *current;

    current = mini->ex;
    while (current)
    {
	    waitpid(current->pid, &status, 0);
        current = current->next;
    }
	if (WIFEXITED(status))
		mini->command_ret = WEXITSTATUS(status);
	else
		mini->command_ret = 1;
}

int	exec_all(t_mini *mini)
{
	t_exec	*current;
	int		p[2];
	int		previous_fd;

	printf("\n---------exec----------\n");
	current = mini->ex;
	previous_fd = 0;
	g_is_display = 0;
	if (!heredoc(mini))
		return (ft_printf("heredoc failed\n"), 0);
	if (!current || !current->cmd_name)
		return (1);
	if (builtin_env_modifier(current->cmd_name) && !current->next)
	{
		mini->command_ret = execute_builtin(mini, current, current->cmd_name);
		return (mini->command_ret);
	}
	while (current)
	{
		if (!exec_all_loop(mini, current, p, &previous_fd))
			return (0);
		current = current->next;
	}
	wait_exec(mini);
	g_is_display = 1;
	return (1);
}
