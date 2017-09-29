#include "shell.h"

void	reset_cmdsiginted(t_cmd *cmd)
{
	clear_cmd(cmd);
	*cmd = init_cmd(return_prompt());
	init_screen(cmd);
	cmd->stop = 1;
	is_sigint(1);
}

int			can_sigint(int sigint)
{
	static int	s_sigint = 0;
	int			i;

	if (sigint > 0)
		s_sigint = sigint;
	else
	{
		i = s_sigint;
		s_sigint = sigint;
		return (i);
	}
	return (s_sigint);
}

int			is_sigint(int sigint)
{
	static int	s_sigint = 0;
	int			i;

	if (sigint > 0)
		s_sigint = sigint;
	else
	{
		i = s_sigint;
		s_sigint = sigint;
		return (i);
	}
	return (s_sigint);
}

void		signal_do_nothing(int n)
{
	n = 0;
}

void		get_signal(int n)
{
	if (g_is_child)
		return ;
	if (n == SIGINT)
	{
		ft_putchar('\n');
		print_prompt();
		is_sigint(1);
	}
	else if (n == SIGSEGV)
		ft_putstr_fd(" Segmentation fault: 11\n", 2);
	else if (n == SIGABRT)
		ft_putstr_fd(" Abort trap: 6\n", 2);
	else if (n == SIGBUS)
		ft_putstr_fd(" Bus error: 10\n", 2);
}