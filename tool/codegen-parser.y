%{
/*
    Copyright (C) 2013 Baptiste COVOLATO <b.covolato@gmail.com>

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to
    deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
    sell copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
    IN THE SOFTWARE.
*/
%}
%require "2.4"

%defines
%debug
%verbose
%error-verbose

%code requires
{
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void yyrestart(FILE *f);
void yyerror(const char *str);
int yylex();
}

%code
{
int error = 0;

int max_size = 256;
char *output_txt = NULL;
}

%union
{
    char *str;
}

%token      END     0       "end_of_file"
%token      INSTRUCTION     "instruction"
%token      ARROW           "->"
%token      L_BRACKET       "["
%token      R_BRACKET       "]"
%token      COMA            ","
%token      CONST           "const"
%token<str> CODE_BLOCK      "code"

%%

codegen:
       | instr_list
       ;

args: "const"
    ;

args_list: args
         | args_list "," args
         ;

args_block: "[" args_list "]" CODE_BLOCK
          ;

args_block_list: args_block
               | args_block_list args_block
               ;

instr: "instruction" "->" args_block_list
     ;

instr_list: instr
          | instr_list instr
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

    if (!input)
    {
        fprintf(stderr, "Cant open input file : %s\n", argv[1]);
        return 2;
    }

    output_txt = calloc(1, sizeof(char) * max_size);

    yyrestart(input);
    yyparse();

    if (error)
    {
        fclose(input);
        return 4;
    }
    else
    {
        output = fopen(argv[2], "w");

        if (!output)
        {
            fprintf(stderr, "Cant open output file : %s\n", argv[2]);
            fclose(input);
            return 3;
        }

        fprintf(output, output_txt);
    }

    fclose(output);
    fclose(input);

    return 0;
}

void yyerror(const char *str)
{
    fprintf(stderr, str);
    error = 1;
}
