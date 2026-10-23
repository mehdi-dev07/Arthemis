typedef enum KEYWORD
{
    INTEGER_TOKEN,
    BOOL_TOKEN,
    FLOAT_TOKEN,
    IF_TOKEN,
    THEN_TOKEN,
    GOTO,TOKEN,
    MAIN
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
    COMA_TOKEN,
    SEMICOLON_TOKEN,
    COLON_TOKEN,
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
    char* lexeme;
}token;

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



token lexer(char* input, int len, symbolTable* table)
{
    token streamTokens;

    return streamTokens;
}
