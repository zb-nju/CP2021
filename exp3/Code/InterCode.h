#ifndef _INTERCODE_H_
#define _INTERCODE_H_

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




#endif