#ifndef TOKENS_H
#define TOKENS_H
#include <stdio.h>
#include <stdbool.h>


typedef enum KEYWORD
{
    INTEGER_TOKEN,
    BOOL_TOKEN,
    FLOAT_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    GOTO_TOKEN,
    MAIN_TOKEN,
    INPUT_TOKEN,
    OUTPUT_TOKEN,
    GARBAGE
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

void init_token_stream(token_stream* stream);
void free_token_stream(token_stream* stream);

bool add_token(token t, token_stream* stream);
bool get_keyword(char* token, KEYWORD* keyword);
bool get_operator(char c, OPERATION* op);
bool get_punctuation(char c, PUNCTUATION* p);

token gen_token(category c, tokenVal val);
token_stream lexer(const char* input, size_t len);
void print_token(token t);

#endif

