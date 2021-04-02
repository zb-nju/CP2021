//Generate parser
#include<stdio.h>
#include"node.h"
#include"syntax.tab.h"

extern void yyrestart(FILE *);
extern int yyparse();

extern node* root;
//extern int yydebug;

extern int errorNums;

int main(int argc, char** argv) {
	if(argc <= 1) return 1;
	FILE* f = fopen(argv[1], "r");
	if(!f){
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	//yydebug=1;
	yyparse();

	printf("errorNum = %d\n", errorNums);
	if(errorNums==0){ //No errors
		printTree(root, 0);
	}
	return 0;
}

//Generate scanner
/*#include<stdio.h>
extern FILE* yyin;
extern int yylex();
int main(int argc, char** argv) {
	if (argc > 1) {
		if (!(yyin = fopen(argv[1], "r"))) {
			perror(argv[1]);
			return 1;
		}
	}
	while (yylex() != 0);
	return 0;
}*/
