#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include "lexer.h"

void print_tokens(t_lexer *lexer_list)
{
    t_lexer *current = lexer_list;

    if (!current)
    {
        printf("Error: lexer_list is empty!\n");
        return;
    }

    printf("\n--- Tokenized Input ---\n");
    while (current)
    {
        printf("Token: %-10s Type: %d\n", current->str ? current->str : "(NULL)", current->token);
        current = current->next;
    }
    printf("------------------------\n");
}

int main(void)
{
    char *input;
    t_tools tools;

    while (1)
    {
        input = readline("minishell> ");
        if (!input)
        {
            printf("exit\n");
            break;
        }
        if (*input)
            add_history(input);

        tools.args = input;
        tools.lexer_list = NULL;

        printf("Debug: Running token_reader()...\n");
        if (!token_reader(&tools))
        {
            printf("Lexer error: invalid tokenization.\n");
        }
        else
        {
            printf("Debug: token_reader() finished successfully.\n");
            print_tokens(tools.lexer_list);
        }

        free(input);
    }
    return 0;
}
