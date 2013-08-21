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

int error = 0;

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
void flex_free(void);

extern FILE *yyin;

typedef struct instr_list_s instr_list;
typedef struct instr_s instr;
typedef struct block_s block;
typedef struct param_list_s param_list;

typedef enum
{
    PARAM_CONST,
} param_type;

struct param_list_s
{
    /* The parameter */
    param_type type;

    /* The next parameter */
    param_list *next;
};

struct instr_s
{
    /* The name of the instruction */
    char *instr_name;

    /* The blocks of code that contains the instruction */
    block *blk;

    /* The next instruction */
    instr *next;
};

struct block_s
{
    /* The list of instruction parameters */
    param_list *params;

    /* The code associated to the block */
    char *code;

    /* The next block */
    block *next;
};

param_list *cgen_new_param_list(param_type type);
void cgen_free_param_list(param_list *l);

block *cgen_new_block(param_list *l, char *code);
void cgen_free_block(block *b);

instr *cgen_new_instr(char *name, block *b);
void cgen_free_instr(instr *b);

void cgen_print_instr(FILE *f, instr *i);
void cgen_print_block(FILE *f, block *b);
void cgen_print_param_list(FILE *f, param_list *l);
}

%code
{
instr *code = NULL;
}

%union
{
    char *str;
    param_list *plist;
    param_type param;
    instr *instr;
    block *blk;
}

%token          END     0       "end_of_file"
%token          ARROW           "->"
%token          L_BRACKET       "["
%token          R_BRACKET       "]"
%token          COMA            ","
%token          CONST           "const"

%token<str>     INSTRUCTION     "instruction"
%token<str>     CODE_BLOCK      "code"

%type<blk>      args_block
                args_block_list

%type<instr>    instr
                instr_list

%type<plist>    args_list
%type<param>    args
%%

codegen:
       | instr_list { code = $1; }
       ;

args: "const" { $$ = PARAM_CONST; }
    ;

args_list: args { $$ = cgen_new_param_list($1); }
         | args_list "," args
         {
            param_list *tmp = $1;

            while (tmp->next)
                tmp = tmp->next;

            tmp->next = cgen_new_param_list($3);

            $$ = $1;
         }
         ;

args_block: "[" args_list "]" CODE_BLOCK
          {
            $$ = cgen_new_block($2, $4);
          }
          ;

args_block_list: args_block { $$ = $1; }
               | args_block_list args_block
               {
                block *tmp = $1;

                while (tmp->next)
                    tmp = tmp->next;

                tmp->next = $2;

                $$ = $1;
               }
               ;

instr: "instruction" "->" args_block_list
     {
        $$ = cgen_new_instr($1, $3);
     }
     ;

instr_list: instr { $$ = $1; }
          | instr_list instr
          {
            instr *tmp = $1;

            while (tmp->next)
                tmp = tmp->next;

            tmp->next = $2;

            $$ = $1;
          }
          ;

%%

int main(int argc, char *argv[])
{
    FILE *output = NULL;

    if (argc != 3)
    {
        printf("%s src dst\n", argv[0]);
        return 1;
    }

    yyin = fopen(argv[1], "r");

    if (!yyin)
    {
        fprintf(stderr, "Cant open input file : %s\n", argv[1]);
        return 2;
    }

    yyparse();
    flex_free();

    if (error)
    {
        cgen_free_instr(code);
        fclose(yyin);
        return 4;
    }
    else
    {
        output = fopen(argv[2], "w");

        if (!output)
        {
            fprintf(stderr, "Cant open output file : %s\n", argv[2]);
            fclose(yyin);
            return 3;
        }
    }

    cgen_print_instr(output, code);
    cgen_free_instr(code);

    fclose(output);
    fclose(yyin);

    return 0;
}

void yyerror(const char *str)
{
    fprintf(stderr, str);
    error = 1;
}

param_list *cgen_new_param_list(param_type type)
{
    param_list *l = NULL;

    if ((l = malloc(sizeof(param_list))) == NULL)
        return NULL;

    l->type = type;
    l->next = NULL;

    return l;
}
void cgen_free_param_list(param_list *l)
{
    if (!l)
        return;

    cgen_free_param_list(l->next);
    free(l);
}

block *cgen_new_block(param_list *l, char *code)
{
    block *b = NULL;

    if ((b = malloc(sizeof(block))) == NULL)
        return NULL;

    b->params = l;
    b->code = code;
    b->next = NULL;

    return b;
}

void cgen_free_block(block *b)
{
    if (!b)
        return;

    cgen_free_param_list(b->params);
    free(b->code);
    cgen_free_block(b->next);
    free(b);
}

instr *cgen_new_instr(char *name, block *b)
{
    instr *i = NULL;

    if ((i = malloc(sizeof(instr))) == NULL)
        return NULL;

    i->instr_name = name;
    i->blk = b;
    i->next = NULL;

    return i;
}

void cgen_free_instr(instr *i)
{
    if (!i)
        return;

    free(i->instr_name);
    cgen_free_block(i->blk);
    cgen_free_instr(i->next);
    free(i);
}

void cgen_print_instr(FILE *f, instr *i)
{
    instr *tmp = i;

    while (tmp)
    {
        fprintf(f, "case %s:\n", tmp->instr_name);
        cgen_print_block(f, tmp->blk);

        tmp = tmp->next;
    }
}

void cgen_print_block(FILE *f, block *b)
{
    block *tmp = b;

    while (tmp)
    {
        cgen_print_param_list(f, tmp->params);
        fprintf(f, "{%s}\n", tmp->code);

        tmp = tmp->next;
    }
}

void cgen_print_param_list(FILE *f, param_list *l)
{
    param_list *tmp = l;
    int count = 1;

    fprintf(f, "if (");

    while (tmp)
    {
        if (count > 1)
            fprintf(f, " && ");

        switch (tmp->type)
        {
            case PARAM_CONST:
                fprintf(f, "instr->op%i->is_cst", count);
                break;
        }

        ++count;
        tmp = tmp->next;
    }

    fprintf(f, ")\n");
}
