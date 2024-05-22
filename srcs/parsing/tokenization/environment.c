#include "../../../includes/minishell.h"


/*

Environment Variables 
=> key-value pairs maintained by the OS and used by processes to configure their behavior. 
e.g : PATH, HOME, USER, and PWD.

OLDPWD
    Purpose: OLDPWD holds the path of the previous current working directory. 
            This allows users and programs to reference the last directory they were in before changing to the current directory.
    Usage: It's particularly useful in shell environments. 
            For example, in the Bash shell, you can use the command cd - to change back to the previous directory, and it uses OLDPWD to know where to go.

=> duplicate the string "OLDPWD" and then add it to the environment list soo that if env initially
empty at least "OLDPWD" available

*/

// Set up a minimal env when no initial env vars are given
int create_env(t_minishell *minishell)
{
	char path[PATH_MAX];
	char *tmp;

	// SET OLDPWD : env var that stores the previous working directory
	tmp = ft_strdup("OLDPWD");

	return (0);
}

int free_list(t_list *list)
{
	//
}
int init_env(char **env, t_minishell *minishell)
{
	int i;
	t_list *lst;
	char *tmp;

	// If no environment exists we create a minimal env
	if (!(*env))
		return (create_env(minishell));
	i = 0;
	lst = NULL;
	// Loop over each env string in env array
	while (env[i])
	{
		// Duplicate each env string
		tmp = ft_strdup(env[i]);
		if (!tmp)
			return(free_list(&lst));
		// Append the env strings to the list
		if (!append(&lst, tmp))
			return(free_list(&lst));
		i++;
	}
	minishell->env = lst;
	return (1)
}