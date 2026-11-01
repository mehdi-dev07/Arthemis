#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <limits.h>
#include <errno.h>
#include "../headers/lexer.h"


void init_token_stream(token_stream *stream)
{
    stream->tokens = NULL;
    stream->capacity = 0;
    stream->size = 0;
}

void free_token_stream(token_stream* stream)
{
    for (size_t i = 0; i < stream->size; i++)
    {
        if (stream->tokens[i].tokenType == identifier)
            free(stream->tokens[i].val.identifier);
    }

    free(stream->tokens);

    stream->tokens = NULL;
    stream->capacity = 0;
    stream->size = 0;
}

bool isDelimiter(char c)
{
    switch (c)
    {
        case ' ': case '\t': case '\n': case '\r':
        case '(': case ')':
        case '{': case '}':
        case ';': case ',':
        case ':':
        case '+': case '-': case '*': case '/':
        case '=': case '<': case '>': case '!':
            return true;
        default:
            return false;
    }
}

bool add_letter(char** temp, char c)
{
    size_t len = strlen(*temp);

    char* new_temp = realloc(*temp, len + 2);

    if (new_temp == NULL)
        return false;

    *temp = new_temp;
    (*temp)[len] = c;
    (*temp)[len + 1] = '\0';

    return true;
}

bool add_token(token t, token_stream* stream)
{
if (stream->size >= stream->capacity)
    {
        size_t new_capacity = stream->capacity == 0
                            ? 8
                            : stream->capacity * 2;

        token* new_tokens = realloc(
            stream->tokens,
            new_capacity * sizeof(token)
        );

        if (new_tokens == NULL)
            return false;

        stream->tokens = new_tokens;
        stream->capacity = new_capacity;
    }

    stream->tokens[stream->size] = t;
    stream->size++;

    return true;
}

bool get_operator(char c, OPERATION* op)
{
    switch (c)
    {
        case '+': *op = ADD_TOKEN; break;
        case '-': *op = SUB_TOKEN; break;
        case '*': *op = MULT_TOKEN; break;
        case '/': *op = DIV_TOKEN; break;
        case '=': *op = ASSIGNMENT_TOKEN; break;
        case '>': *op = GREATER_TOKEN; break;
        case '<': *op = LESS_TOKEN; break;

        default: return false;
    }

    return true;
}

bool get_punctuation(char c, PUNCTUATION* p)
{
    switch (c)
    {
        case ';': *p = SEMICOLON_TOKEN; break;
        case '(': *p = LPAR_TOKEN; break;
        case ')': *p = RPAREN_TOKEN; break;
        case ',': *p = COMMA_TOKEN; break;
        case ':': *p = COLON_TOKEN; break;
        case '{': *p = LBRACE_TOKEN; break;
        case '}': *p = RBRACE_TOKEN; break;

        default: return false;
    }

    return true;
}

bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z');
}

bool isDigit(char c)
{
    return c >= '0' && c <= '9';
}

bool is_identifier(char* temp)
{
    if (!isAlpha(temp[0]) && temp[0] != '_') return false;
    for (size_t i = 1; temp[i] != '\0'; i++)
    {
        if (!isAlpha(temp[i]) &&
            !isDigit(temp[i]) &&
            temp[i] != '_')
            return false;
    }
    return true;
}

bool is_number(const char* temp)
{
    if (!isDigit(temp[0]))
        return false;

    for (size_t i = 1; temp[i] != '\0'; i++)
    {
        if (!isDigit(temp[i]))
            return false;
    }

    return true;
}

bool get_keyword(char* token, KEYWORD* keyword)
{
     if (strcmp(token, "int") == 0) {
        *keyword = INTEGER_TOKEN;
        return true;
    }
    if (strcmp(token, "bool") == 0) {
        *keyword = BOOL_TOKEN;
        return true;
    }
    if (strcmp(token, "float") == 0) {
        *keyword = FLOAT_TOKEN;
        return true;
    }
    if (strcmp(token, "input") == 0) {
        *keyword = INPUT_TOKEN;
        return true;
    }
    if (strcmp(token, "output") == 0) {
        *keyword = OUTPUT_TOKEN;
        return true;
    }
    if (strcmp(token, "if") == 0) {
        *keyword = IF_TOKEN;
        return true;
    }
    if (strcmp(token, "then") == 0) {
        *keyword = THEN_TOKEN;
        return true;
    }
    if (strcmp(token, "goto") == 0) {
        *keyword = GOTO_TOKEN;
        return true;
    }
    if (strcmp(token, "main") == 0) {
        *keyword = MAIN_TOKEN;
        return true;
    }
    return false;
}

token gen_token(category c, tokenVal val)
{
    token t;
    t.tokenType = c;
    t.val = val;
    return t;
}



token_stream lexer(const char* input, size_t len)
{
    token_stream stream;
    init_token_stream(&stream);

    char* temp = calloc(1, sizeof(char));

    if (temp == NULL)
        return stream;

    size_t i = 0;

    while (i < len)
    {
        // 1. Skip whitespace
        if (input[i] == ' ' || input[i] == '\t' ||
            input[i] == '\n' || input[i] == '\r')
        {
            i++;
            continue;
        }

        token t;
        PUNCTUATION p;
        OPERATION o;
        KEYWORD k;

        // 2. Recognize punctuation
        if (get_punctuation(input[i], &p))
        {
            t = gen_token(
                punctuation,
                (tokenVal){ .punctuation = p }
            );

            if (!add_token(t, &stream))
                goto error;

            i++;
            continue;
        }

        // 3. Recognize operators
        if (get_operator(input[i], &o))
        {
            t = gen_token(
                operation,
                (tokenVal){ .operation = o }
            );

            if (!add_token(t, &stream))
                goto error;

            i++;
            continue;
        }

        // 4. Read the next lexeme
        while (i < len && !isDelimiter(input[i]))
        {
            if (!add_letter(&temp, input[i]))
                goto error;

            i++;
        }

        // Handle unrecognized delimiter characters
        if (temp[0] == '\0')
        {
            fprintf(stderr, "Unknown character: %c\n", input[i]);
            goto error;
        }

        // 5. Recognize keywords
        if (get_keyword(temp, &k))
        {
            t = gen_token(
                keywords,
                (tokenVal){ .keyword = k }
            );
        }

        // 6. Recognize integer constants
        else if (is_number(temp))
        {
            errno = 0;
            long value = strtol(temp, NULL, 10);

            if (errno == ERANGE || value > INT_MAX)
            {
                fprintf(stderr, "Integer out of range: %s\n", temp);
                goto error;
            }

            t = gen_token(
                constant,
                (tokenVal){ .constant = (int)value }
            );
        }

        // 7. Recognize identifiers
        else if (is_identifier(temp))
        {
            size_t len_temp = strlen(temp);

            char* copy = malloc(len_temp + 1);

            if (copy == NULL)
                goto error;

            memcpy(copy, temp, len_temp + 1);

            t = gen_token(
                identifier,
                (tokenVal){ .identifier = copy }
            );
        }

        // 8. Invalid lexeme
        else
        {
            fprintf(stderr, "Invalid lexeme: %s\n", temp);
            goto error;
        }

        // 9. Add token to stream
        if (!add_token(t, &stream))
        {
            if (t.tokenType == identifier)
                free(t.val.identifier);

            goto error;
        }

        // Reset temporary buffer
        temp[0] = '\0';
    }

    free(temp);
    return stream;

error:
    free(temp);
    free_token_stream(&stream);
    return stream;
}

void print_token(token t)
{
    switch (t.tokenType)
    {
        case keywords:
        {
            const char* names[] = {
                "INTEGER", "BOOL", "FLOAT", "IF",
                "THEN", "GOTO", "MAIN", "INPUT", "OUTPUT"
            };

            printf("KEYWORD: %s\n", names[t.val.keyword]);
            break;
        }

        case punctuation:
        {
            const char* names[] = {
                "SEMICOL", "RPAREN", "LPAREN", "COMMA",
                "SEMICOLON", "COLON", "LBRACE", "RBRACE"
            };

            printf("PUNCTUATION: %s\n", names[t.val.punctuation]);
            break;
        }

        case operation:
        {
            const char* names[] = {
                "ADD", "SUB", "MULT", "DIV",
                "ASSIGNMENT", "EQUALS", "GREATER",
                "GREATER_EQUAL", "LESS", "LESS_EQUAL"
            };

            printf("OPERATION: %s\n", names[t.val.operation]);
            break;
        }

        case identifier:
            printf("IDENTIFIER: %s\n", t.val.identifier);
            break;

        case constant:
            printf("CONSTANT: %d\n", t.val.constant);
            break;
    }
}
