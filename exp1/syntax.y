%locations

%{
    #include"lex.yy.c"
    #include<stdio.h>
    void printerror(char* msg);
    void yyerror(char* msg);
    int errorNum=0;
    int errorLine=0;
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
%token PLUS MINUS STAR DIV
%token DOT SEMI COMMA ASSIGNOP RELOP
%token AND OR NOT
%token LP RP LB RB LC RC
%token IF ELSE WHILE STRUCT RETURN TYPE

%right ASSIGNOP
%left OR 
%left AND 
%left RELOP
%left PLUS MINUS
%left STAR DIV
%right NOT
%left LP RP LB RB DOT

%nonassoc LOWER_THAN_ELSE
%nonassoc ELSE

%%
Program : ExtDefList
    ;
ExtDefList : ExtDef ExtDefList
    | /* empty */
    ;
ExtDef : Specifier ExtDecList SEMI
    | Specifier SEMI
    | Specifier FunDec CompSt
    | error SEMI { printError("ExtDef---Syntax error."); }
    ;
ExtDecList : VarDec
    | VarDec COMMA ExtDecList
    ;


Specifier : TYPE    
    | StructSpecifier
    ;
StructSpecifier : STRUCT OptTag LC DefList RC
    | STRUCT Tag
    ;
OptTag : ID
    | /* empty */
    ;
Tag : ID
    ;


VarDec : ID
    | VarDec LB INT RB
    | VarDec LB error RB { printError("Missing \"]\"."); }
    ;
FunDec : ID LP VarList RP
    | ID LP RP
    | error RP { printError("FunDec---Syntax error."); }
    ;
VarList : ParamDec COMMA VarList
    | ParamDec
    ;
ParamDec : Specifier VarDec
    | error COMMA { printError("Formal parameter definition error."); }
    | error RP { printError("Formal parameter definition error."); }
    ;


CompSt : LC DefList StmtList RC
    | LC error RC { printError("CompSt---Syntax error."); }
    ;
StmtList : Stmt StmtList
    | /* empty */
    ;
Stmt : Exp SEMI
    //| error '\n' { printError("Stmt---Syntax error."); }
    | CompSt
    | RETURN Exp SEMI
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE
    | IF LP Exp RP Stmt ELSE Stmt
    | IF LP Exp RP error ELSE Stmt { printError("Missing \";\"."); }
    | WHILE LP Exp RP Stmt
    //| error SEMI { printError("Stmt---Syntax error."); }
    ;


DefList : Def DefList
    | /* empty */
    ;
Def : Specifier DecList SEMI
    | error SEMI { printError("Def---Syntax error."); }
    ;
DecList : Dec
    | Dec COMMA DecList
    ;
Dec : VarDec
    | VarDec ASSIGNOP Exp
    ;


Exp : Exp ASSIGNOP Exp
    | Exp AND Exp
    | Exp OR Exp
    | Exp RELOP Exp
    | Exp PLUS Exp
    | Exp MINUS Exp
    | Exp STAR Exp
    | Exp DIV Exp
    | LP Exp RP
    | LP error RP { printError("Exp1---Syntax error."); }
    | MINUS Exp
    | NOT Exp
    | ID LP Args RP
    | ID LP error RP { printError("Exp2---Syntax error."); }
    | ID LP RP
    | Exp LB Exp RB
    | Exp LB error RB { printError("Missing \"]\"."); }
    | Exp DOT ID
    | ID
    | INT
    | FLOAT
    ;
Args : Exp COMMA Args
    | Exp
    ;





%%

void printError(char* msg){
    errorNum++;
    if(errorLine!=yylineno){
        errorLine=yylineno;
        fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, msg);
    }
}

void yyerror(char* msg){
    /*errorNum++;
    if(errorLine!=yylineno){
        errorLine=yylineno;
        fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, msg);
    }*/
}