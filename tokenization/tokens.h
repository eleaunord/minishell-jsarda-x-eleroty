
#ifndef TOKEN_H
# define TOKEN_H

typedef enum e_token_type
{
    TOKEN_WORD,

} t_token_type;

typedef struct s_token
{
    t_token_type *type;
    char    *value;
    struct s_token *next;
} t_token;

#endif TOKEN_H