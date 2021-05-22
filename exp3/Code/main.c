//Generate parser
#include<stdio.h>
#include"Node.h"
#include"syntax.tab.h"
#include"Semantic.h"
#include"InterCode.h"

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

	Program(root);

	translate_Program(root);
	printIR(head);

	// if(errorNums==0){ //No errors
	// 	printTree(root, 0);
	// }
	return 0;
}

// Test the struct InterCode and the function printIR
/*#include<stdio.h>
#include"InterCode.h"

FILE* fp;
InterCode head = NULL;
InterCode tail = NULL;

int main(int argc, char** argv) {
	if(argc <= 1) return 1;
	fp = fopen(argv[1], "w+");
	
	Operand t1 = newOperand(TEMP_VAR, "t1");
	Operand v1 = newOperand(VARIABLE, "v1");
	Operand t2 = newOperand(TEMP_VAR, "t2");
	Operand t3 = newOperand(TEMP_VAR, "t3");
	Operand t6 = newOperand(TEMP_VAR, "t6");
	Operand label1 = newOperand(LABEL_OP, "label1");
	Operand label2 = newOperand(LABEL_OP, "label2");
	Operand label3 = newOperand(LABEL_OP, "label3");

	InterCode a[18];

	a[1] = newIR(FUNCTION_IR, newOperand(FUNCTION_OP, "main"));
	a[2] = newIR(READ_IR, t1);
	a[3] = newIR(ASSIGN_IR, v1, t1);
	a[4] = newIR(ASSIGN_IR, t2, newOperand(CONSTANT, 0));
	a[5] = newIR(RELOP_GOTO_IR, v1, ">", t2, label1);
	a[6] = newIR(RELOP_GOTO_IR, v1, "<", t2, label2);
	a[7] = newIR(WRITE_IR, t2);
	a[8] = newIR(GOTO_IR, label3);
	a[9] = newIR(LABEL_IR, label1);
	a[10] = newIR(ASSIGN_IR, t3, newOperand(CONSTANT, 1));
	a[11] = newIR(WRITE_IR, t3);
	a[12] = newIR(GOTO_IR, label3);
	a[13] = newIR(LABEL_IR, label2);
	a[14] = newIR(ASSIGN_IR, t6, newOperand(CONSTANT, -1));
	a[15] = newIR(WRITE_IR, t6);
	a[16] = newIR(LABEL_IR, label3);
	a[17] = newIR(RETURN_IR, t2);

	for(int i=1;i<18;++i){
		addIR(a[i]);
	}

	printIR(head);
	return 0;
}*/

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
