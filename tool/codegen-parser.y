%require "2.4"

%defines

%code requires
{
#include <stdio.h>

void yyrestart(FILE *f);
void yyerror(char *str);
int yylex();
}

%token  END     0       "end_of_file"

%%

codegen:
       ;

%%

int main(int argc, char *argv[])
{
    FILE *input = NULL;
    FILE *output = NULL;

    if (argc != 3)
    {
        printf("%s src dst\n", argv[0]);
        return 1;
    }

    input = fopen(argv[1], "r");
    output = fopen(argv[2], "w");

    if (!input || !output)
        return 2;

    yyrestart(input);

    if (yyparse())
    {
        fclose(output);
        unlink(output);
    }

    fclose(output);
    fclose(input);

    return 0;
}

void yyerror(char *str)
{
    fprintf(stderr, str);
}
