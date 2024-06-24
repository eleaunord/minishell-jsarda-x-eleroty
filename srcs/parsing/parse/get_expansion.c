#include "../../../includes/minishell.h"

// Get the index of a key in the environment list
int get_the_key(t_env *env, char *key)
{
    int index = 0;
    while (env)
    {
        if (env->key && ft_strcmp(env->key, key) == 0)
            return index;
        env = env->next;
        index++;
    }
    return -1;
}

// Get the value of a key in the environment list
char *get_key_value(t_minishell *data, char *key)
{
    int index;
    t_env *env = data->env;
    index = get_the_key(env, key);
    if (index == -1)
        return NULL;
    for (int i = 0; i < index; i++)
        env = env->next;
    return env->value;
}

// Construct the result string with preserved parts before and after the key
char *construct_result(char *key_expansion, char *start, char *end, char *path_value)
{
    size_t leading_length = start - key_expansion;
    size_t key_length = strlen(path_value);
    size_t trailing_length = strlen(end);
    size_t result_length = leading_length + key_length + trailing_length;

    char *result = (char *)malloc(result_length + 1);
    if (!result)
        return NULL;

    // Copy leading part
    strncpy(result, key_expansion, leading_length);
    result[leading_length] = '\0';

    // Append expanded key
    strcat(result, path_value);

    // Append trailing part
    strcat(result, end);

    return result;
}

// Extract the key from the key expansion string
char *extract_the_key(char *start, char *end, char *dollar_pos)
{
    size_t key_length = end - start;
    return strndup(start + (dollar_pos ? 1 : 0), key_length - (dollar_pos ? 1 : 0));
}

// Find the start and end of the key in the key expansion string
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

// Main function to get the expansion of a key in the key expansion string
char *get_expansion(t_minishell *data, char *key_expansion)
{
    char *path_value;
    char *result;
    char *start;
    char *end;
    char *dollar_pos;

    find_key_start_end(key_expansion, &start, &end);

    dollar_pos = strchr(key_expansion, '$');
    char *key = extract_the_key(start, end, dollar_pos);

    path_value = get_key_value(data, key);
    free(key);

    if (!path_value)
        return NULL;

    result = construct_result(key_expansion, start, end, path_value);

    return result;
}
