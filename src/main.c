#include <stdio.h>
#include "../headers/lexer.h"
#include <string.h>
int main()
{
    char *code = "int main(){"
                 "int a = 2 + b;"
                 "}";
    int len;

    static symbolTable* table;

    token tokenStream = lexer(code , len, table);

    return 0;
}
