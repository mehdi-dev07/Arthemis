#include <stdio.h>
#include <stdlib.h>
#include "../headers/lexer.h"

int main(int argc, char* argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s file.txt\n", argv[0]);
        return 1;
    }

    FILE* file = fopen(argv[1], "r");

    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    char code[10000];

    size_t len = fread(code, 1, sizeof(code) - 1, file);
    code[len] = '\0';

    fclose(file);

    token_stream stream = lexer(code, len);

    for (size_t i = 0; i < stream.size; i++)
        print_token(stream.tokens[i]);

    free_token_stream(&stream);

    return 0;
}
