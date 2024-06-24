#include "../../../includes/minishell.h"

static void init_variables(int *i, int *j, char *quote, int *len, char **result,
						   char *word)
{
	*i = -1;
	*j = 0;
	*quote = 0;
	*len = strlen(word);
	*result = (char *)malloc(*len + 1);
	if (!(*result))
		return;
}
static int process_single_quotes(const char *word, int *i, int len,
								 char *result, int j)
{
	while (word[++(*i)] != '\'' && *i < len)
	{
		result[j++] = word[*i];
	}
	return (j);
}

char *remove_quotes_from_word(char *word)
{
	int len;
	char *result;
	int i;
	int j;
	char quote;

	if (!word)
		return (NULL);
	init_variables(&i, &j, &quote, &len, &result, word);
	while (++i < len)
	{
		if (word[i] == '\'' && quote == 0)
			j = process_single_quotes(word, &i, len, result, j);
		else if (word[i] == '"' && quote == 0)
			quote = '"';
		else if (word[i] == '"' && quote == '"')
			quote = 0;
		else if (quote == '"' && (word[i] == '\\' || word[i] == '$' || word[i] == '`'))
			result[j++] = word[i];
		else
			result[j++] = word[i];
	}
	result[j] = '\0';
	return (result);
}
