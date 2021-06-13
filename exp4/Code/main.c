//Generate parser
#include<stdio.h>
#include"Node.h"
#include"syntax.tab.h"
#include"Semantic.h"
#include"InterCode.h"
#include"ObjectCode.h"


extern void yyrestart(FILE *);
extern int yyparse();

extern Node root;
//extern int yydebug;

extern int errorNums;

FILE* fp;
InterCode head = NULL;
InterCode tail = NULL;

int main(int argc, char** argv) {
	if(argc <= 1) return 1;

	FILE* f = fopen(argv[1], "r");
	fp = fopen(argv[2], "w");
	if(!f){
		perror(argv[1]);
		return 1;
	}
	yyrestart(f);
	//yydebug=1;
	yyparse();
	// printTree(root, 0);
	Program(root);
	translate_Program(root);
	// printIR(head);
	OCMain(head);

	return 0;
}
