#include "../../../includes/minishell.h"

/*

Environment Variables
=> key-value pairs maintained by the OS and used by processes to configure their behavior.
e.g : PATH, HOME, USER, and PWD.

OLDPWD
	Purpose: OLDPWD holds the path of the previous current working directory.
			This allows users and programs to reference the last directory they were in before changing to the current directory.
	Usage: It's particularly useful in shell environments.
			For example, in the Bash shell, you can use the command cd
				- to change back to the previous directory,
				and it uses OLDPWD to know where to go.

=> duplicate the string "OLDPWD" and then add it to the environment list soo that if env initially
empty at least "OLDPWD" available

*/

// If no environment exists we create a minimal env OR return 0 ?

int	env_init(t_minishell *mini, char **env_array)
{
	t_env	*env;
	t_env	*new;
	int		i;

	// Allocate memory for the first node of the linked list
	if (!(env = malloc(sizeof(t_env))))
		return (1);
	// value for env_array[0] => SHELL=/bin/zsh
	env->value = ft_strdup(env_array[0]);
	env->next = NULL;
	mini->env = env;
	i = 1; // Start from the second element in the env_array
	while (env_array && env_array[0] && env_array[i])
	{
		// Allocate memory for a new node
		if (!(new = malloc(sizeof(t_env))))
			return (1);
		// Copy the current environment variable into the new node
		new->value = ft_strdup(env_array[i]);
		new->next = NULL;
		// Link the new node to the end of the list
		env->next = new;
		env = new; // Move to the new end of the list
		i++; // Move to the next environment variable in the array
	}
	return (0);
}
