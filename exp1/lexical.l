%{
    #include"syntax.tab.h"

    int yycolumn = 1;
    #define YY_USER_ACTION \
        yylloc.first_line = yylloc.last_line = yylineno; \
        yylloc.first_column = yycolumn; \
        yylloc.last_column = yycolumn + yyleng - 1; \
        yycolumn += yyleng;
%}

%option yylineno

number [1-9][0-9]*
ws [ \t]

ID [_a-zA-z][_a-zA-Z0-9]*
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
"//" {
    char c = input();
    while(c != '\n') c = input();
}

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
{ID} { yylval = deepCopy(yytext); return ID; }
{INT} { yylval = atoi(yytext); return INT; }
{FLOAT} { yylval = atof(yytext); return FLOAT; }

\n { yycolumn = 1;}

. {
    printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);
}

%%
char* deepCopy(char* text){
    int length = strlen(text) + 1;

    char* newText = (char*)malloc(sizeof(char)  * length);

    assert(newText != NULL);

    strncpy(newText, text, length);

    return newText;
}

int main(int argc, char** argv){
    int i;
    if(argc < 2){
        yylex();
        return 0;
    }
    for(i = 1; i < argc; i++){
        FILE *f = fopen(argv[i], "r");
        if(!f){
            perror(argv[i]);
            return 1;
        }
        yyrestart(f);
        yylex();
        fclose(f);
    }
    return 0;
}