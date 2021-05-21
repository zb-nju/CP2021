#ifndef _INTERCODE_H_
#define _INTERCODE_H_

#include"Node.h"

typedef struct Operand_* Operand;
typedef struct InterCode_* InterCode;

typedef struct Operand_{
    enum { VARIABLE, CONSTANT, ADDRESS, TEMP_VAR, ADDR_VALUE, FUNCTION_OP, LABEL_OP, RELOP_OP } kind;
    union{
        int var_no;
        char value[32];
    }u;
}Operand_;

typedef struct InterCode_{
    enum { LABEL_IR, FUNCTION_IR, ASSIGN_IR, ADD_IR, SUB_IR, MUL_IR, DIV_IR, GET_ADDR_IR, GET_VALUE_IR, ASSIGN_ADDR_IR,
            GOTO_IR, RELOP_GOTO_IR, RETURN_IR, DEC_IR, ARG_IR, CALL_IR, PARAM_IR, READ_IR, WRITE_IR} kind;
    union{
        struct { Operand right, left;} assign;
        struct { Operand result, op1, op2;} binop;
        struct { Operand op;} signleop;
        struct { Operand x, y, label_z; char relop[32];} if_goto;
        struct { Operand op; int size;} dec;
    }u;
    InterCode prev, next;
}InterCode_;




void printOp(Operand op);           // 打印操作数
void printIR(InterCode head);       // 打印中间代码
void addIR(InterCode code);         // 向双向链表中添加一条中间代码
InterCode newIR(int kind, ...);     // 构造一条中间代码
Operand newOperand(int kind, ...);  // 构造一个操作数
Operand newTemp();                  // 生成一个临时变量
Operand newLabel();                 // 生成一个label


void translate_Cond(Node root, Operand label_true, Operand label_false);

// Translate function
//High-level Definitions
void translate_Program(Node root);

void translate_ExtDefList(Node root);
void translate_ExtDef(Node root);
void translate_ExtDecList(Node root, Type type);

//Specifiers
void translate_Specifier(Node root);
void translate_StructSpecifier(Node root);
char* translate_OptTag(Node root);
char* translate_Tag(Node root);

//For struct
void translate_DefList_Struct(Node root, FieldList alreadyDefined);
void translate_Def_Struct(Node root);
void translate_DecList_Struct(Node root, Type decType);
void translate_Dec_Struct(Node root, Type decType);

//Declarators
void translate_VarDec(Node root, Operand place);
void translate_FunDec(Node root);
void translate_VarList(Node root, Boolean flag);
void translate_ParamDec(Node root, Boolean flag);

//Statements
void translate_CompSt(Node root);
void translate_StmtList(Node root);
void translate_Stmt(Node root);

//Local Definitions
void translate_DefList(Node root);
void translate_Def(Node root);
void translate_DecList(Node root);
void translate_Dec(Node root);

//Expressions
void translate_Exp(Node root, Operand place);
void translate_Args(Node root, TableNode tn);

void translate_Exp_ASSIGNOP(Node root, Operand place);
void translate_Exp_AND_OR(Node root, Operand place);
void translate_Exp_RELOP_CAL(Node root, Operand place);
void translate_Exp_LPRP(Node root, Operand place);
void translate_Exp_MIUNS(Node root, Operand place);
void translate_Exp_NOT(Node root, Operand place);
void translate_Exp_FUNCTION_CALL(Node root, Operand place);
void translate_Exp_ARRAY_VISIT(Node root, Operand place);
void translate_Exp_STRUCT_VISIT(Node root, Operand place);
void translate_Exp_ID(Node root, Operand place);
void translate_Exp_INT(Node root, Operand place);
//void translate_Exp_FLOAT(Node root, Operand place);


#endif