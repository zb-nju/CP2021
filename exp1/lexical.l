%{
    #include"syntax.tab.h"
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
<comment>[^*] { ; }
<comment>"*"+[^/]* { ; }
<comment>"*"+"/" { BEGIN(INITIAL); }

[ \t] { ; }

{IF} { return IF; }
{ELSE} { return ELSE; }
{TYPE} { return TYPE; }
{WHILE} { return WHILE; }
{STRUCT} { return STRUCT; }
{RETURN} { return RETURN; }

{SEMI} { return SEMI; }
{COMMA} { return COMMA; }
{ASSIGNOP} { return ASSIGNOP; }
{RELOP} { return RELOP; }
{PLUS} { return PLUS; }
{MINUS} { return MINUS; }
{STAR} { return STAR; }
{DIV} { return DIV; }
{AND} { return AND; }
{OR} { return OR; }
{DOT} { return DOT; }
{NOT} { return NOT; }
{LP} { return LP; }
{RP} { return RP; }
{LB} { return LB; }
{RB} { return RB; }
{LC} { return LC; }
{RC} { return RC; }
{ID} { yylval.type_char_star = deepCopy(yytext); return ID; }
{INT} { yylval.type_int = atoi(yytext); return INT; }
{FLOAT} { yylval.type_float = atof(yytext); return FLOAT; }



%%
char* deepCopy(char* text){
    int length = strlen(text) + 1;

    char* newText = (char*)malloc(sizeof(char)  * length);

    assert(newText != NULL);

    strncpy(newText, text, length);

    return newText;
}