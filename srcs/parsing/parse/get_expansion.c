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

char *get_the_path_value(t_minishell *data, char *key)
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
char *get_expansion(t_minishell *data, char *key_expansion)
{
    char *path_value;

    if (!data || !key_expansion)
        return (NULL);

    path_value = get_path_value(data, key_expansion);
    if (!path_value)
        return (NULL);

    return (path_value);
}

//

int count_expansions(t_token *tokens)
{
    int count;
    t_token *current;

    count = 0;
    current = tokens;
    while (current)
    {
        if (current->key_expansion != NULL)
        {
            count++;
        }
        current = current->next;
    }
    return (count);
}

void fill_expansions(t_token *tokens, t_node *node)
{
    t_token *tok;
    int i;

    tok = tokens;
    if (!tokens || !node)
        return;
    i = -1;
    while (tok)
    {
        if (tok->key_expansion != NULL && !tok->processed)
        {
            node->key_expansion[++i] = ft_strdup(tok->key_expansion);
            if (!node->key_expansion[i])
            {
                while (i > 0)
                    free(node->key_expansion[--i]);
                free(node->key_expansion);
                return;
            }
        }
        tok = tok->next;
    }
}

void set_expansions(t_token *tokens, t_node *node)
{
    int expansion_count;

    if (!tokens || !node)
        return;
    expansion_count = count_expansions(tokens);
    node->key_expansion = (char **)ft_calloc(expansion_count + 1, sizeof(char *));
    node->expansion_count = expansion_count;
    fill_expansions(tokens, node);
}
