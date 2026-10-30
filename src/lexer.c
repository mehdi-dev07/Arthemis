#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

typedef enum KEYWORD
{
    INTEGER_TOKEN,
    BOOL_TOKEN,
    FLOAT_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    GOTO_TOKEN,
    MAIN,
    INPUT_TOKEN,
    OUTPUT_TOKEN
}KEYWORD;

typedef enum OPERATION
{
    ADD_TOKEN,
    SUB_TOKEN,
    MULT_TOKEN,
    DIV_TOKEN,
    ASSIGNMENT_TOKEN,
    EQUALS_TOKEN,
    GREATER_TOKEN,
    GREATEREQUAL_TOKEN,
    LESS_TOKEN,
    LESSEQUAL_TOKEN
}OPERATION;

typedef enum PUNCTUALTION
{
    SEMICOL_TOKEN,
    RPAREN_TOKEN,
    LPAR_TOKEN,
    COMMA_TOKEN,
    SEMICOLON_TOKEN,
    COLON_TOKEN,
    LBRACE_TOKEN,
    RBRACE_TOKEN
}PUNCTUATION;

typedef enum category
{
    keywords,
    punctuation,
    operation,
    constant,
    identifier
}category;

typedef union tokenVal
{
    KEYWORD keyword;
    PUNCTUATION punctuation;
    OPERATION operation;
    char* identifier;
    int constant;
}tokenVal;

typedef struct token
{
    category tokenType;
    tokenVal val;
}token;

typedef struct token_stream
{
    size_t capacity;
    size_t size;
    token* tokens;
}token_stream;

typedef enum kind_of_id
{
    FUNC_NAME,
    VAR_NAME
}kind_of_id;

typedef struct symbolTable
{
    kind_of_id type;
    char* nameID;
}symbolTable;

void init_token_stream(token_stream *stream)
{
    stream->tokens = NULL;
    stream->capacity = 0;
    stream->size = 0;
}

void free_token_stream(token_stream *stream)
{
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

void add_letter(char** temp, char c)
{
    size_t len = strlen(*temp);

    char* new_temp = realloc(*temp, len + 2);

    if (new_temp == NULL)
        return;

    *temp = new_temp;
    (*temp)[len] = c;
    (*temp)[len + 1] = '\0';
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

OPERATION get_operator(char c)
{
    switch (c)
    {
        case '+': return ADD_TOKEN;
        case '-': return SUB_TOKEN;
        case '*': return MULT_TOKEN;
        case '/': return DIV_TOKEN;
        case '=': return ASSIGNMENT_TOKEN;
        case '>': return GREATER_TOKEN;
        case '<': return LESS_TOKEN;

        default:
            fprintf(stderr, "Unknown operator: %c\n", c);
            exit(EXIT_FAILURE);
    }
}

PUNCTUATION get_punctuation(char c)
{
    switch (c)
    {
        case ';': return SEMICOLON_TOKEN;
        case '(': return LPAR_TOKEN;
        case ')': return RPAREN_TOKEN;
        case ',': return COMMA_TOKEN;
        case ':': return COLON_TOKEN;
        case '{': return LBRACE_TOKEN;
        case '}': return RBRACE_TOKEN;

        default:
            fprintf(stderr, "Unknown punctuation: %c\n", c);
            exit(EXIT_FAILURE);
    }
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
    int len = strlen(temp);
    if(isAlpha(temp[0]) || isDigit(temp[0]))
    {
        return true;
    }
    for (int i = 0;i<=len;i++)
    {
        if( isAlpha(temp[i]) || isDigit(temp[i]) )
        {
            return true;
        }
    }
    return false;
}

token_stream lexer(const char* input, size_t len)
{
    token_stream stream_of_tokens;
    init_token_stream(&stream_of_tokens);
    char* temp = calloc(1, sizeof(char));
    int i = 0;

    while(i < len)
    {

        if(input[i] == ' ' || input[i] == '\t' || input[i] == '\n' || input[i] == '\r')
        {
            i++;
            continue;
        }
        
        while(!isDelimiter(input[i]) && i < len)
        {
            add_letter(&temp, input[i]);
            i++;
        }
       //now we have our lexeme
        switch temp:
        case 
        i++;        
    }

    return stream_of_tokens;
}
