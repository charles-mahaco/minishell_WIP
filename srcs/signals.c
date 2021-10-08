#include "minishell.h"

void	set_signals(int context)
{
	if (context)
		signal(SIGINT, handle_interrupt);
	else
		signal(SIGINT, handle_interrupt_while_exec);
	signal(SIGQUIT, SIG_IGN);
}

void	handle_interrupt(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	return ;
}

void	handle_interrupt_while_exec(int sig_num)
{
	(void)sig_num;
	write(1, "\n", 1);
	return ;
}
