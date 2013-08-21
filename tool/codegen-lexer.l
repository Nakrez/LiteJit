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
%{
#include "codegen-parser.h"

char *read_code_block(void);

%}

%option noyywrap nounput

%x code

%%

"const"         { return CONST; }
[A-Z][A-Z_]*    { yylval.str = strdup(yytext); return INSTRUCTION; }
->              { return ARROW; }
"["             { return L_BRACKET; }
"]"             { return R_BRACKET; }
","             { return COMA; }
"{"             { yylval.str = read_code_block(); return CODE_BLOCK; }
"\n"
.               { yyerror("Scan error\n"); }
%%

char *read_code_block(void)
{
    int count = 1;
    char c;
    int pos = 0;
    int max_size = 32;
    char *buf = malloc(32);

    while (1)
    {
        c = input();

        if (c == '{')
            ++count;
        if (c == '}')
        {
            --count;
            if (count <= 0)
                break;
        }

        if (pos == max_size)
        {
            max_size *= 2;
            buf = realloc(buf, max_size);
        }

        buf[pos++] = c;
    }

    buf[pos] = 0;

    return buf;
}
