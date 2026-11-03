#include "headers/lexer.h"

typedef enum AST_component
{
    VAR_DECLARATION,
    
    //ect...
}AST_component;

typedef struct AST
{
    AST_component t;
    struct AST* right;
    struct AST* left;
}AST;



AST parser (token_stream input)
{
    AST output;

    return output;
}
