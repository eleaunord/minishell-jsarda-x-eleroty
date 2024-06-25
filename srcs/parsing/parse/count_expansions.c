#include "../../../includes/minishell.h"

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
void set_expansions(t_token *tokens, t_node *node)
{
    int expansion_count;

    if (!tokens || !node)
        return;
    expansion_count = count_expansions(tokens);
    node->expansion_count = expansion_count;
}