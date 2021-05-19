#include "InterCode.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

extern FILE* fp;
extern InterCode head;
extern InterCode tail;

void printOp(Operand op){
    switch (op->kind)
    {
    case CONSTANT:
        fprintf(fp, "#%d", op->u.var_no);
        break;
    case ADDRESS:
        fprintf(fp, "&%s", op->u.value);
        break;
    case ADDR_VALUE:
        fprintf(fp, "*%s", op->u.value);
        break;
    default:
        fprintf(fp, "%s", op->u.value);
        break;
    }
}

void printIR(InterCode head){
    while(head != NULL){
        switch (head->kind)
        {
        case LABEL_IR:{
            fprintf(fp, "LABEL %s :\n", head->u.signleop.op->u.value);
            break;
        }
        case FUNCTION_IR:{
            fprintf(fp, "FUNCTION %s :\n", head->u.signleop.op->u.value);
            break;
        }
        case ASSIGN_IR:{
            printOp(head->u.assign.left);
            fprintf(fp, " := ");
            printOp(head->u.assign.right);
            fprintf(fp, "\n");
            break;
        }
        case ADD_IR:{
            printOp(head->u.binop.result);
            fprintf(fp, " := ");
            printOp(head->u.binop.op1);
            fprintf(fp, " + ");
            printOp(head->u.binop.op2);
            fprintf(fp, "\n");
            break;
        }
        case SUB_IR:{
            printOp(head->u.binop.result);
            fprintf(fp, " := ");
            printOp(head->u.binop.op1);
            fprintf(fp, " - ");
            printOp(head->u.binop.op2);
            fprintf(fp, "\n");
            break;
        }
        case MUL_IR:{
            printOp(head->u.binop.result);
            fprintf(fp, " := ");
            printOp(head->u.binop.op1);
            fprintf(fp, " * ");
            printOp(head->u.binop.op2);
            fprintf(fp, "\n");
            break;
        }
        case DIV_IR:{
            printOp(head->u.binop.result);
            fprintf(fp, " := ");
            printOp(head->u.binop.op1);
            fprintf(fp, " / ");
            printOp(head->u.binop.op2);
            fprintf(fp, "\n");
            break;
        }
        case GET_ADDR_IR:{
            printOp(head->u.assign.left);
            fprintf(fp, " := &");
            printOp(head->u.assign.right);
            fprintf(fp, "\n");
            break;
        }
        case GET_VALUE_IR:{
            printOp(head->u.assign.left);
            fprintf(fp, " := *");
            printOp(head->u.assign.right);
            fprintf(fp, "\n");
            break;
        }
        case ASSIGN_ADDR_IR:{
            fprintf(fp, "*");
            printOp(head->u.assign.left);
            fprintf(fp, " := ");
            printOp(head->u.assign.right);
            fprintf(fp, "\n");
            break;
        }
        case GOTO_IR:{
            fprintf(fp, "GOTO ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        case RELOP_GOTO_IR:{
            fprintf(fp, "IF ");
            printOp(head->u.if_goto.x);
            fprintf(fp, " %s ", head->u.if_goto.relop);
            printOp(head->u.if_goto.y);
            fprintf(fp, " GOTO ");
            printOp(head->u.if_goto.label_z);
            fprintf(fp, "\n");

            printf("head->u.if_goto.relop:  %s\n", head->u.if_goto.relop);
            break;
        }
        case RETURN_IR:{
            fprintf(fp, "RETURN ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        case DEC_IR:{
            fprintf(fp, "DEC ");
            printOp(head->u.dec.op);
            fprintf(fp, " %d\n", head->u.dec.size);
            break;
        }
        case ARG_IR:{
            fprintf(fp, "ARG ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        case CALL_IR:{
            printOp(head->u.assign.left);
            fprintf(fp, " := CALL ");
            printOp(head->u.assign.right);
            fprintf(fp, "\n");
            break;
        }
        case PARAM_IR:{
            fprintf(fp, "PARAM ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        case READ_IR:{
            fprintf(fp, "READ ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        case WRITE_IR:{
            fprintf(fp, "WRITE ");
            printOp(head->u.signleop.op);
            fprintf(fp, "\n");
            break;
        }
        default:
            break;
        }
        head = head->next;
    }
}

void addIR(InterCode code){
    if(head == NULL){
        head = code;
        tail = code;
        head->prev = NULL;
        head->next = NULL;
        tail->prev = NULL;
        tail->next = NULL;
    }else{
        tail->next = code;
        code->prev = tail;
        tail = code;
        tail->next = NULL;
    }
}

InterCode newIR(int kind, ...){
    InterCode code = (InterCode)malloc(sizeof(InterCode_));
    code->kind = kind;
    va_list vaList;
    va_start(vaList, kind);

    switch (kind)
    {
    case LABEL_IR:
    case FUNCTION_IR:
    case GOTO_IR:
    case RETURN_IR:
    case ARG_IR:
    case PARAM_IR:
    case READ_IR:
    case WRITE_IR:{
        code->u.signleop.op = va_arg(vaList, Operand);
        break;
    }
    case ASSIGN_IR:
    case GET_ADDR_IR:
    case GET_VALUE_IR:
    case ASSIGN_ADDR_IR:
    case CALL_IR:{
        code->u.assign.left = va_arg(vaList, Operand);
        code->u.assign.right = va_arg(vaList, Operand);
        break;
    }
    case ADD_IR:
    case SUB_IR:
    case MUL_IR:
    case DIV_IR:{
        code->u.binop.result = va_arg(vaList, Operand);
        code->u.binop.op1 = va_arg(vaList, Operand);
        code->u.binop.op2 = va_arg(vaList, Operand);
        break;
    }
    case RELOP_GOTO_IR:{
        code->u.if_goto.x = va_arg(vaList, Operand);
        //printf("va_arg(vaList, char*): %s\n",va_arg(vaList, char*));
        strcpy(code->u.if_goto.relop, va_arg(vaList, char*));
        printf("code->u.if_goto.relop: %s\n",code->u.if_goto.relop);
        code->u.if_goto.y = va_arg(vaList, Operand);
        code->u.if_goto.label_z = va_arg(vaList, Operand);
        break;
    }
    case DEC_IR:{
        code->u.dec.op = va_arg(vaList, Operand);
        code->u.dec.size = va_arg(vaList, int);
        break;
    }
    default:
        break;
    }
    return code;
}

Operand newOperand(int kind, ...){
    Operand op = (Operand)malloc(sizeof(Operand_));
    op->kind = kind;
    va_list vaList;
    va_start(vaList, kind);

    switch (kind)
    {
    case CONSTANT:{
        op->u.var_no = va_arg(vaList, int);
        break;
    }
    case VARIABLE:
    case ADDRESS:
    case TEMP_VAR:
    case ADDR_VALUE:
    case FUNCTION_OP:
    case LABEL_OP:
    case RELOP_OP: {
        strcpy(op->u.value, va_arg(vaList, char*));
        break;
    }
    default:
        break;
    }

    return op;
}