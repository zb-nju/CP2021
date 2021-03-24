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
{IF} {printf("IF: %s\n", yytext);}
{ELSE} {printf("ELSE: %s\n", yytext);}
{TYPE} {printf("TYPE: %s\n", yytext);}
{WHILE} {printf("WHILE: %s\n", yytext);}
{STRUCT} {printf("STRUCT: %s\n", yytext);}
{RETURN} {printf("RETURN: %s\n", yytext);}

{SEMI} {printf("SEMI: %s\n", yytext);}
{COMMA} {printf("COMMA: %s\n", yytext);}
{ASSIGNOP} {printf("ASSIGNOP: %s\n", yytext);}
{RELOP} {printf("RELOP: %s\n", yytext);}
{PLUS} {printf("PLUS: %s\n", yytext);}
{MINUS} {printf("MINUS: %s\n", yytext);}
{STAR} {printf("STAR: %s\n", yytext);}
{DIV} {printf("DIV: %s\n", yytext);}
{AND} {printf("AND: %s\n", yytext);}
{OR} {printf("OR: %s\n", yytext);}
{DOT} {printf("DOT: %s\n", yytext);}
{NOT} {printf("NOT: %s\n", yytext);}
{LP} {printf("LP: %s\n", yytext);}
{RP} {printf("RP: %s\n", yytext);}
{LB} {printf("LB: %s\n", yytext);}
{RB} {printf("RB: %s\n", yytext);}
{LC} {printf("LC: %s\n", yytext);}
{RC} {printf("RC: %s\n", yytext);}

"//" {
    char c = input();
    while(c != '\n') c = input();
}

. {
    printf("Error type A at Line %d: Mysterious characters \'%s\'\n", yylineno, yytext);
}
%%
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