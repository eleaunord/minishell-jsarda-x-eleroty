
#ifndef TOKEN_H
# define TOKEN_H

// TOKEN LIST

/*

Règles de Tokenisation :

    Redirections :
        < devient le token INPUT (1).
        > devient le token TRUNC (3).
        << devient le token HEREDOC (2).
        >> devient le token APPEND (4).

    Premier Token :
        Le premier token d'une ligne de commande est CMD (6), sauf s'il s'agit d'une redirection.

    Arguments :
        Tous les tokens suivants un CMD ou une redirection (INPUT, TRUNC, HEREDOC, APPEND) sont des ARG (7).

    Pipes :
        | devient le token PIPE (5).
        Après un PIPE, le prochain token est soit une redirection, soit un CMD.

*/

# define INPUT 1
# define HEREDOC 2
# define TRUNC 3
# define APPEND 4
# define PIPE 5 
# define CMD 6 
# define ARG 7 

// TOKEN LINKED LIST

/*

liste chainee de token pour chaque elements de la ligne de commande
-> str et int pour chaque maillon
-> str = WORD aka ce qui est visuel (cat, | ) ; int = token aka type de token (CMD, PIPE)
 create a string of TOKEN and an INT for each node.
*/

typedef struct	s_token
{
	char			*str;
	int				type;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;


#endif TOKEN_H