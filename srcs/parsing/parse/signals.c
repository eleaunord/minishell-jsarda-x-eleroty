#include "../../../includes/minishell.h"

void	sigint_handler(int sig)
{
	(void)sig;
	g_status = 130;
	rl_on_new_line();
	printf("\n");
	rl_replace_line("", 1);
	rl_redisplay();
	return ;
}
void	setup_signal_handlers(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, sigint_handler);
}
