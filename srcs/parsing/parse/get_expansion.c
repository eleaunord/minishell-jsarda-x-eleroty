#include "../../../includes/minishell.h"

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

// Helper function to get the value of a key in the environment list
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

// Helper function to construct the result string with preserved leading and trailing spaces
char *construct_result(char *key_expansion, char *start, char *end, char *path_value)
{
    // Find leading and trailing spaces
    char *leading = key_expansion;
    char *trailing = end;
    while (leading < start && *leading == ' ')
        leading++;
    while (*trailing == ' ')
        trailing++;

    size_t leading_spaces = leading - key_expansion;
    size_t trailing_spaces = strlen(trailing);
    size_t result_length = leading_spaces + strlen(path_value) + trailing_spaces;

    char *result = (char *)malloc(result_length + 1);
    if (!result)
        return NULL;

    strncpy(result, key_expansion, leading_spaces);
    result[leading_spaces] = '\0';
    strcat(result, path_value);
    strcat(result, trailing);

    return result;
}

// Helper function to extract the key from the key expansion string
char *extract_the_key(char *start, char *end, char *dollar_pos)
{
    size_t key_length = end - start;
    return strndup(start + (dollar_pos ? 1 : 0), key_length - (dollar_pos ? 1 : 0));
}

// Helper function to find the start and end of the key in the key expansion string
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
