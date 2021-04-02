%locations

%{
    #include"lex.yy.c"
    #include"node.h"
    #include<stdio.h>
    void yyerror(char* msg);
    int errorNums=0;
    int errorLine=0;
    node* root;
%}

%union {
    struct node_* pnode;
}

%token <pnode> INT FLOAT ID
%token <pnode> PLUS MINUS STAR DIV
%token <pnode> DOT SEMI COMMA ASSIGNOP RELOP
%token <pnode> AND OR NOT
%token <pnode> LP RP LB RB LC RC
%token <pnode> IF ELSE WHILE STRUCT RETURN TYPE

%type <pnode> Program ExtDefList ExtDef ExtDecList
%type <pnode> Specifier StructSpecifier OptTag Tag
%type <pnode> VarDec FunDec VarList ParamDec
%type <pnode> CompSt StmtList Stmt
%type <pnode> DefList Def DecList Dec
%type <pnode> Exp Args

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
Program : ExtDefList                            { $$ = createNode(@$.first_line, "Program", "", false, 1, $1); root = $$; }
    ;
ExtDefList : ExtDef ExtDefList                  { $$ = createNode(@$.first_line, "ExtDefList", "", false, 2, $1, $2); }
    | /* empty */                               { $$ = NULL; }
    ;
ExtDef : Specifier ExtDecList SEMI              { $$ = createNode(@$.first_line, "ExtDef", "", false, 3, $1, $2, $3); }
    | Specifier SEMI                            { $$ = createNode(@$.first_line, "ExtDef", "", false, 2, $1, $2); }
    | Specifier FunDec CompSt                   { $$ = createNode(@$.first_line, "ExtDef", "", false, 3, $1, $2, $3); }
    | error SEMI                                { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    ;
ExtDecList : VarDec                             { $$ = createNode(@$.first_line, "ExtDecList", "", false, 1, $1); }
    | VarDec COMMA ExtDecList                   { $$ = createNode(@$.first_line, "ExtDecList", "", false, 3, $1, $2, $3); }
    ;


Specifier : TYPE                                { $$ = createNode(@$.first_line, "Specifier", "", false, 1, $1); }
    | StructSpecifier                           { $$ = createNode(@$.first_line, "Specifier", "", false, 1, $1); }
    ;
StructSpecifier : STRUCT OptTag LC DefList RC   { $$ = createNode(@$.first_line, "StructSpecifier", "", false, 5, $1, $2, $3, $4, $5); }
    | STRUCT Tag                                { $$ = createNode(@$.first_line, "StructSpecifier", "", false, 2, $1, $2); }
    ;
OptTag : ID                                     { $$ = createNode(@$.first_line, "OptTag", "", false, 1, $1); }
    | /* empty */                               { $$ = NULL;}
    ;
Tag : ID                                        { $$ = createNode(@$.first_line, "Tag", "", false, 1, $1); }
    ;


VarDec : ID                                     { $$ = createNode(@$.first_line, "VarDec", "", false, 1, $1); }
    | VarDec LB INT RB                          { $$ = createNode(@$.first_line, "VarDec", "", false, 4, $1, $2, $3, $4); }
    | VarDec LB error RB                        { errorNums++; printf("Error type B at Line %d: Missing ']'.\n", yylineno); }
    ;
FunDec : ID LP VarList RP                       { $$ = createNode(@$.first_line, "FunDec", "", false, 4, $1, $2, $3, $4); }
    | ID LP RP                                  { $$ = createNode(@$.first_line, "FunDec", "", false, 3, $1, $2, $3); }
    | error RP                                  { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    ;
VarList : ParamDec COMMA VarList                { $$ = createNode(@$.first_line, "VarList", "", false, 3, $1, $2, $3); }
    | ParamDec                                  { $$ = createNode(@$.first_line, "VarList", "", false, 1, $1); }
    ;
ParamDec : Specifier VarDec                     { $$ = createNode(@$.first_line, "ParamDec", "", false, 2, $1, $2); }
    | error COMMA                               { errorNums++; printf("Error type B at Line %d: Formal parameter definition error.\n", yylineno); }
    | error RP                                  { errorNums++; printf("Error type B at Line %d: Formal parameter definition error.\n", yylineno); }
    ;


CompSt : LC DefList StmtList RC                 { $$ = createNode(@$.first_line, "CompSt", "", false, 4, $1, $2, $3, $4); }
    | LC error RC                               { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    ;
StmtList : Stmt StmtList                        { $$ = createNode(@$.first_line, "StmtList", "", false, 2, $1, $2); }
    | /* empty */                               { $$ = NULL; }
    ;
Stmt : Exp SEMI                                 { $$ = createNode(@$.first_line, "Stmt", "", false, 2, $1, $2); }
    //| error '\n'                              { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    | CompSt                                    { $$ = createNode(@$.first_line, "Stmt", "", false, 1, $1); }
    | RETURN Exp SEMI                           { $$ = createNode(@$.first_line, "Stmt", "", false, 3, $1, $2, $3); }
    | IF LP Exp RP Stmt %prec LOWER_THAN_ELSE   { $$ = createNode(@$.first_line, "Stmt", "", false, 5, $1, $2, $3, $4, $5); }
    | IF LP Exp RP Stmt ELSE Stmt               { $$ = createNode(@$.first_line, "Stmt", "", false, 7, $1, $2, $3, $4, $5, $6, $7); }
    | IF LP Exp RP error ELSE Stmt              { errorNums++; printf("Error type B at Line %d: Missing ';'.\n", yylineno); }
    | WHILE LP Exp RP Stmt                      { $$ = createNode(@$.first_line, "Stmt", "", false, 5, $1, $2, $3, $4, $5); }
    //| error SEMI                              { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    ;


DefList : Def DefList                           { $$ = createNode(@$.first_line, "DefList", "", false, 2, $1, $2); }
    | /* empty */                               { $$ = NULL; }
    ;
Def : Specifier DecList SEMI                    { $$ = createNode(@$.first_line, "Def", "", false, 3, $1, $2, $3); }
    | STAR DIV                                  { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    | error SEMI                                { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    ;
DecList : Dec                                   { $$ = createNode(@$.first_line, "DecList", "", false, 1, $1); }
    | Dec COMMA DecList                         { $$ = createNode(@$.first_line, "DecList", "", false, 3, $1, $2, $3); }
    ;
Dec : VarDec                                    { $$ = createNode(@$.first_line, "Dec", "", false, 1, $1); }
    | VarDec ASSIGNOP Exp                       { $$ = createNode(@$.first_line, "Dec", "", false, 3, $1, $2, $3); }
    ;


Exp : Exp ASSIGNOP Exp                          { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp AND Exp                               { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp OR Exp                                { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp RELOP Exp                             { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp PLUS Exp                              { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp MINUS Exp                             { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp STAR Exp                              { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp DIV Exp                               { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | LP Exp RP                                 { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | LP error RP                               { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    | MINUS Exp                                 { $$ = createNode(@$.first_line, "Exp", "", false, 2, $1, $2); }
    | NOT Exp                                   { $$ = createNode(@$.first_line, "Exp", "", false, 2, $1, $2); }
    | ID LP Args RP                             { $$ = createNode(@$.first_line, "Exp", "", false, 4, $1, $2, $3, $4); }
    | ID LP error RP                            { errorNums++; printf("Error type B at Line %d: Syntax error.\n", yylineno); }
    | ID LP RP                                  { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | Exp LB Exp RB                             { $$ = createNode(@$.first_line, "Exp", "", false, 4, $1, $2, $3, $4); }
    | Exp LB error RB                           { errorNums++; printf("Error type B at Line %d: Missing ']'.\n", yylineno); }
    | Exp DOT ID                                { $$ = createNode(@$.first_line, "Exp", "", false, 3, $1, $2, $3); }
    | ID                                        { $$ = createNode(@$.first_line, "Exp", "", false, 1, $1); }
    | INT                                       { $$ = createNode(@$.first_line, "Exp", "", false, 1, $1); }
    | FLOAT                                     { $$ = createNode(@$.first_line, "Exp", "", false, 1, $1); }
    ;
Args : Exp COMMA Args                           { $$ = createNode(@$.first_line, "Args", "", false, 3, $1, $2, $3); }
    | Exp                                       { $$ = createNode(@$.first_line, "Args", "", false, 1, $1); }
    ;

%%

void yyerror(char* msg){
    /*errorNums++;
    if(errorLine!=yylineno){
        errorLine=yylineno;
        fprintf(stderr, "Error type B at Line %d: %s\n", yylineno, msg);
    }*/
}