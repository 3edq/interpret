#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "../include/lexer.h"

void free_lexer_list(t_lexer *lexer)
{
    t_lexer *tmp;
    
    while (lexer)
    {
        tmp = lexer;
        lexer = lexer->next;
        if (tmp->str)
            free(tmp->str);
        free(tmp);
    }
}

int main(void)
{
    char    *input;
    t_tools tools;
    t_lexer *current;

    input = readline("minishell> ");
    if (!input)
    {
        fprintf(stderr, "入力エラー\n");
        return (1);
    }
    if (*input)
        add_history(input);

    tools.args = input;
    tools.lexer_list = NULL;

    if (!token_reader(&tools))
    {
        fprintf(stderr, "トークン解析エラー\n");
        free(input);
        return (1);
    }
    current = tools.lexer_list;
    while (current)
    {
        if (current->str)
            printf("token = %d, str = \"%s\", i = %d\n", current->token, current->str, current->i);
        else
            printf("token = %d, i = %d\n", current->token, current->i);
        current = current->next;
    }
    free_lexer_list(tools.lexer_list);
    free(input);
    return (0);
}
