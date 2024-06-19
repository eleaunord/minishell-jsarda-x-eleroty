#include "../../../includes/minishell.h"

int get_the_key(t_env *env, char *key)
{
    int index;

    index = 0;
    while (env)
    {
        if (env->key && ft_strcmp(env->key, key) == 0)
            return (index);
        env = env->next;
        index++;
    }
    return (-1);
}

char *get_key_value(t_minishell *data, char *key)
{
    int index;
    t_env *env;

    env = data->env;
    index = get_the_key(env, key);
    if (index == -1)
        return (NULL);
    for (int i = 0; i < index; i++)
        env = env->next;
    return (env->value);
}
char *construct_result(char *key_expansion, char *start, char *end, char *path_value)
{
    size_t result_length = strlen(key_expansion) - (end - start) + strlen(path_value);
    char *result = (char *)malloc(result_length + 1);
    if (!result)
        return NULL;

    strncpy(result, key_expansion, start - key_expansion);
    result[start - key_expansion] = '\0';
    strcat(result, path_value);
    strcat(result, end);

    return result;
}
char *extract_key(char *start, char *end, char *dollar_pos)
{
    size_t key_length = end - start;
    return strndup(start + (dollar_pos ? 1 : 0), key_length - (dollar_pos ? 1 : 0));
}
void find_key_start_end(char *key_expansion, char **start, char **end)
{
    char *dollar_pos = strchr(key_expansion, '$');
    if (dollar_pos)
    {
        *start = dollar_pos;
        *end = dollar_pos + 1;
        while (is_alpha_underscore(**end))
            (*end)++;
    }
    else
    {
        *start = key_expansion;
        *end = key_expansion;
        while (is_alpha_underscore(**end))
            (*end)++;
    }
}




