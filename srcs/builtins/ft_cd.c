

#include "../../includes/minishell.h"

void				ft_cd(t_minishell *data, char **args)
{
	int		cd_ret;

	if (!args[0])
		cd_ret = chdir(get_path_value(data, "HOME"));
	else
	{
		cd_ret = chdir(args[0]);
		if (cd_ret < 0)
			cd_ret *= -1;
		if (cd_ret != 0)
			perror("minishell: cd:");
	}
}
