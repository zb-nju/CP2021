%{
    #include"syntax.tab.h"
    #include"node.h"
    #include<assert.h>

    char* deepCopy(char* text);

    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
%}

%option yylineno
%x comment

number [1-9][0-9]*
ws [ \t]

ID [_a-zA-Z][_a-zA-Z0-9]*
INT [+-]?(({number}([eE][+-]?{number})?)|0)
FLOAT [+-]?([0-9]*\.?[0-9]+|[0-9]+\.)([eE][+-]?{number})?
DOT "."
SEMI ";"
COMMA ","
ASSIGNOP "="
RELOP >|<|>=|<=|==|!=
PLUS "+"
MINUS "-"
STAR "*"
DIV "/"
AND "&&"
OR "||"
NOT "!"
LP "("
RP ")"
LB "["
RB "]"
LC "{"
RC "}"
IF "if"
ELSE "else"
WHILE "while"
STRUCT "struct"
RETURN "return"
TYPE "int"|"float"
%%
<*>\n { yycolumn = 1;}

"//" {
    char c = input();
    while(c != '\n') c = input();
}

"/*" { BEGIN(comment); }
<comment>[^*]
<comment>"/"+"*"
<comment>"*"+[^/]*
<comment>"*"+"/" { BEGIN(INITIAL); }

[ \t] { ; }

{IF} { yylval.pnode = createNode(yylineno, "IF", yytext, true, 0); return IF; }
{ELSE} { yylval.pnode = createNode(yylineno, "ELSE", yytext, true, 0); return ELSE; }
{TYPE} { yylval.pnode = createNode(yylineno, "TYPE", yytext, true, 0); return TYPE; }
{WHILE} { yylval.pnode = createNode(yylineno, "WHILE", yytext, true, 0); return WHILE; }
{STRUCT} { yylval.pnode = createNode(yylineno, "STRUCT", yytext, true, 0); return STRUCT; }
{RETURN} { yylval.pnode = createNode(yylineno, "RETURN", yytext, true, 0); return RETURN; }

{SEMI} { yylval.pnode = createNode(yylineno, "SEMI", yytext, true, 0); return SEMI; }
{COMMA} { yylval.pnode = createNode(yylineno, "COMMA", yytext, true, 0); return COMMA; }
{ASSIGNOP} { yylval.pnode = createNode(yylineno, "ASSIGNOP", yytext, true, 0); return ASSIGNOP; }
{RELOP} { yylval.pnode = createNode(yylineno, "RELOP", yytext, true, 0); return RELOP; }
{PLUS} { yylval.pnode = createNode(yylineno, "PLUS", yytext, true, 0); return PLUS; }
{MINUS} { yylval.pnode = createNode(yylineno, "MINUS", yytext, true, 0); return MINUS; }
{STAR} { yylval.pnode = createNode(yylineno, "STAR", yytext, true, 0); return STAR; }
{DIV} { yylval.pnode = createNode(yylineno, "DIV", yytext, true, 0); return DIV; }
{AND} { yylval.pnode = createNode(yylineno, "AND", yytext, true, 0); return AND; }
{OR} { yylval.pnode = createNode(yylineno, "OR", yytext, true, 0); return OR; }
{DOT} { yylval.pnode = createNode(yylineno, "DOT", yytext, true, 0); return DOT; }
{NOT} { yylval.pnode = createNode(yylineno, "NOT", yytext, true, 0); return NOT; }
{LP} { yylval.pnode = createNode(yylineno, "LP", yytext, true, 0); return LP; }
{RP} { yylval.pnode = createNode(yylineno, "RP", yytext, true, 0); return RP; }
{LB} { yylval.pnode = createNode(yylineno, "LB", yytext, true, 0); return LB; }
{RB} { yylval.pnode = createNode(yylineno, "RB", yytext, true, 0); return RB; }
{LC} { yylval.pnode = createNode(yylineno, "LC", yytext, true, 0); return LC; }
{RC} { yylval.pnode = createNode(yylineno, "RC", yytext, true, 0); return RC; }
{ID} { yylval.pnode = createNode(yylineno, "ID", yytext, true, 0);  return ID; }
{INT} { yylval.pnode = createNode(yylineno, "INT", yytext, true, 0);  return INT; }
{FLOAT} { yylval.pnode = createNode(yylineno, "FLOAT", yytext, true, 0);  return FLOAT; }

. { printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext); }

%%
char* deepCopy(char* text){
    int length = strlen(text) + 1;

    char* newText = (char*)malloc(sizeof(char)  * length);

    assert(newText != NULL);

    strncpy(newText, text, length);

    return newText;
}