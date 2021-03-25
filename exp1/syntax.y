%{
    #include"lex.yy.c"
%}

%union {
    int type_int;
    float type_float;
    double type_double;
    char* type_char_star;
}

%token <type_int> INT
%token <type_float> FLOAT
%token <type_char_star> ID
%token ADD SUB MUL DIV
%token DOT SEMI COMMA ASSIGNOP RELOP
%token AND OR NOT
%token LP RP LB RB LC RC
%token IF ELSE WHILE STRUCT RETURN TYPE

%%
Calc:
%%