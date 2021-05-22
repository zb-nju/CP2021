#include "InterCode.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

extern FILE* fp;
extern InterCode head;
extern InterCode tail;
int tempNums = 0;
int labelNums = 0;

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
        //printf("code->u.if_goto.relop: %s\n",code->u.if_goto.relop);
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

Operand newTemp(){
    tempNums++;
    char tempName[10] = {0};
    sprintf(tempName, "t%d", tempNums);
    Operand ret = newOperand(TEMP_VAR, tempName);
    return ret;
}

Operand newLabel(){
    labelNums++;
    char labelName[10] = {0};
    sprintf(labelName, "label%d", labelName);
    Operand ret = newOperand(LABEL_OP, labelName);
    return ret;
}

void translate_Cond(Node root, Operand label_true, Operand label_false){
    Node child = root->firstChild;
    if(child->nextBrother->name == Node_RELOP){
        Operand t1 = newTemp();
        Operand t2 = newTemp();
        translate_Exp(child, t1);
        translate_Exp(child->nextBrother->nextBrother, t2);
        // TODO: t1->kind == ADDRESS?   t2->kind == ADDRESS?
        addIR(newIR(RELOP_GOTO_IR, t1, child->nextBrother->val, t2, label_true));
        addIR(newIR(GOTO_IR, label_false));
    }
    else if(child->name == Node_NOT){
        translate_Cond(child->nextBrother, label_false, label_true);
    }
    else if(child->nextBrother->name == Node_AND){
        Operand label1 = newLabel();
        translate_Cond(child, label1, label_false);
        addIR(newIR(LABEL_IR, label1));
        translate_Cond(child->nextBrother->nextBrother, label_true, label_false);
    }
    else if(child->nextBrother->name == Node_OR){
        Operand label1 = newLabel();
        translate_Cond(child, label_true, label1);
        addIR(newIR(LABEL_IR, label1));
        translate_Cond(child->nextBrother->nextBrother, label_true, label_false);
    }
    else{
        Operand t1 = newTemp();
        translate_Exp(root, t1);
        // TODO: t1->kind == ADDRESS?
        Operand const_zero = newOperand(CONSTANT, 0);
        addIR(newIR(RELOP_GOTO_IR, t1, "!=", const_zero, label_true));
        addIR(newIR(GOTO_IR, label_false));
    }
}

void translate_CompSt(Node root){
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);

    if(root->firstChild->nextBrother->name == Node_DefList){
        translate_DefList(root->firstChild->nextBrother);
        translate_StmtList(root->firstChild->nextBrother->nextBrother);
    }else if(root->firstChild->nextBrother->name == Node_StmtList){
        translate_StmtList(root->firstChild->nextBrother);
    }
}

void translate_StmtList(Node root){
    if (root == NULL)
        return;
    if(root->firstChild != NULL){
        translate_Stmt(root->firstChild);
        translate_StmtList(root->firstChild->nextBrother);
    }
}

void translate_Stmt(Node root){
    Node child = root->firstChild;
    if(child->name == Node_Exp){
        translate_Exp(child, NULL);
    }else if(child->name == Node_CompSt){
        translate_CompSt(child);
    }else if(child->name == Node_RETURN){
        Operand t1 = newTemp();
        translate_Exp(child->nextBrother, t1);
        addIR(newOperand(RETURN_IR, t1));
    }else if(child->name == Node_WHILE){
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand label3 = newLabel();
        addIR(newIR(LABEL_IR, label1));
        translate_Cond(root, label2, label3);
        addIR(newIR(LABEL_IR, label2));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(GOTO_IR, label1));
        addIR(newIR(LABEL_IR, label3));
    }else if(root->childNum == 5){      // Stmt → IF LP Exp RP Stmt
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        translate_Cond(root, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(LABEL_IR, label2));
    }else{                              // Stmt → IF LP Exp RP Stmt ELSE Stmt
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand label3 = newLabel();
        translate_Cond(root, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(GOTO_IR, label3));
        addIR(newIR(LABEL_IR, label2));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(LABEL_IR, label3));
    }
}

void translate_DefList(Node root){
    if (root == NULL)
        return;
    assert(root->firstChild != NULL);

    translate_Def(root->firstChild);
    translate_DefList(root->firstChild->nextBrother);
}
void translate_Def(Node root){
    Node secondChild = root->firstChild->nextBrother;
    translate_DecList(secondChild);
}
void translate_DecList(Node root){
    translate_Dec(root->firstChild);
    if (root->childNum == 3)
        translate_DecList(root->firstChild->nextBrother->nextBrother);
}
void translate_Dec(Node root){
    Node child = root->firstChild;
    if (root->childNum == 1){
        translate_VarDec(child, NULL);  //TODO
    }
    else if (root->childNum == 3){
        Operand t1 = newTemp();
        translateVarDec(child, t1);
        Operand t2 = newTemp();
        translateExp(child->nextBrother->nextBrother, t2);
        addIR(newIR(ASSIGN_IR, t1, t2));
    }
}

void translate_Exp(Node root, Operand place){
    Node child = root->firstChild;
    if(root->childNum == 1){
        if(child->name == Node_ID){
            translate_Exp_ID(root, place);
        }else if(child->name == Node_INT){
            translate_Exp_INT(child, place);
        }/*else if(child->name == Node_FLOAT){
            translate_Exp_FLOAT(child, place);
        }*/
    }else if(root->childNum == 2){
        if(child->name == Node_MINUS){
            translate_Exp_MIUNS(root, place);
        }else if(child->name == Node_NOT){
            translate_Exp_NOT(root, place);
        }
    }else if(root->childNum == 3){
        if(child->name == Node_Exp){
            Node secondChild = child->nextBrother;
            if(secondChild->name == Node_ASSIGNOP)
                translate_Exp_ASSIGNOP(root, place);
            else if(secondChild->name == Node_AND || secondChild->name == Node_OR)
                translate_Exp_AND_OR(root, place);
            else if(secondChild->name == Node_DOT)
                translate_Exp_STRUCT_VISIT(root, place);
            else
                translate_Exp_RELOP_CAL(root, place);
        }else if(child->name == Node_LP){
            translate_Exp_LPRP(root, place);
        }else if(child->name == Node_ID){
            translate_Exp_FUNCTION_CALL(root, place);
        }
    }else{
        if(child->name == Node_ID){
            translate_Exp_FUNCTION_CALL(root, place);
        }else if(child->name == Node_Exp){
            translate_Exp_ARRAY_VISIT(root, place);
        }
    }
}

void translate_Exp_ASSIGNOP(Node root, Operand place){
    Operand t1 = newTemp();
    translate_Exp(root->firstChild->nextBrother->nextBrother, t1);
    Operand t2 = newTemp();
    translate_Exp(root->firstChild, t2);
    addIR(newIR(ASSIGN_IR, t2, t1));
}

void translate_Exp_AND_OR(Node root, Operand place){
    Operand label1 = newLabel();
    Operand label2 = newLabel();
    Operand const_zero = newOperand(CONSTANT, 0);
    addIR(newIR(ASSIGN_IR, place, const_zero));
    translate_Cond(root, label1, label2);
    addIR(newIR(LABEL_IR, label1));
    Operand const_one = newOperand(CONSTANT, 1);
    addIR(newIR(ASSIGN_IR, place, const_one));
    addIR(newIR(LABEL_IR, label2));
}

void translate_Exp_RELOP_CAL(Node root, Operand place){
    if(root->firstChild->nextBrother->name == Node_RELOP){
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand const_zero = newOperand(CONSTANT, 0);
        addIR(newIR(ASSIGN_IR, place, const_zero));
        translate_Cond(root, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        Operand const_one = newOperand(CONSTANT, 1);
        addIR(newIR(ASSIGN_IR, place, const_one));
        addIR(newIR(LABEL_IR, label2));
    }else{  // PLUS, MINUS, STAR, DIV
        Operand t1 = newTemp();
        Operand t2 = newTemp();
        translate_Exp(root->firstChild, t1);
        translate_Exp(root->firstChild->nextBrother->nextBrother, t2);
        switch (root->firstChild->nextBrother->name)
        {
        case Node_PLUS:
            addIR(newIR(ADD_IR, place, t2, t1));
            break;
        case Node_MINUS:
            addIR(newIR(SUB_IR, place, t2, t1));
            break;
        case Node_STAR:
            addIR(newIR(MUL_IR, place, t2, t1));
            break;
        case Node_DIV:
            addIR(newIR(DIV_IR, place, t2, t1));
            break;
        default:
            break;
        }
    }
}

void translate_Exp_LPRP(Node root, Operand place){
    translate_Exp(root->firstChild->nextBrother, place);
}

void translate_Exp_MIUNS(Node root, Operand place){
    Operand t1 = newTemp();
    translateExp(root->firstChild->nextBrother, t1);
    Operand t2 = newOperand(CONSTANT, 0);
    genInterCode(SUB_IR, place, t2, t1);
}

void translate_Exp_NOT(Node root, Operand place){
    Operand label1 = newLabel();
    Operand label2 = newLabel();
    Operand const_zero = newOperand(CONSTANT, 0);
    addIR(newIR(ASSIGN_IR, place, const_zero));
    translate_Cond(root, label1, label2);
    addIR(newIR(LABEL_IR, label1));
    Operand const_one = newOperand(CONSTANT, 1);
    addIR(newIR(ASSIGN_IR, place, const_one));
    addIR(newIR(LABEL_IR, label2));
}

void translate_Args(Node root, Arg_list arg_list){
    while(root->childNum != 1){
        Operand t1 = newTemp();
        translate_Exp(root->firstChild, t1);
        Arg_list tmp = (Arg_list)malloc(sizeof(struct Arg_list_));
        tmp->arg = t1;
        tmp->next = arg_list;
        arg_list = tmp;
        root = root->firstChild->nextBrother->nextBrother;
    }

    Operand t1 = newTemp();
    translate_Exp(root->firstChild, t1);
    Arg_list tmp = (Arg_list)malloc(sizeof(struct Arg_list_));
    tmp->arg = t1;
    tmp->next = arg_list;
    arg_list = tmp;
}

void translate_Exp_FUNCTION_CALL(Node root, Operand place){
    char function[32];
    strcpy(function, root->firstChild->val);
    if(root->childNum == 3){        // Exp → ID LP RP
        if(!strcmp(function, "read")){
            addIR(newIR(READ_IR, place));
            return;
        }
        Operand funcOp = newOperand(FUNCTION_OP, function);
        addIR(newIR(CALL_IR, place, funcOp));
        return;
    }
    else if(root->childNum == 4){                           // Exp → ID LP Args RP
        Arg_list arg_list = NULL;
        translate_Args(root->firstChild->nextBrother->nextBrother, arg_list);
        if(!strcmp(function, "write")){
            addIR(newIR(WRITE_IR, arg_list->arg));
            Operand const_zero = newOperand(CONSTANT, 0);
            addIR(newIR(ASSIGN_IR, place, const_zero));
            return;
        }
        while (arg_list != NULL)
        {
            addIR(newIR(ARG_IR, arg_list->arg));
            arg_list = arg_list->next;
        }
        Operand funcOp = newOperand(FUNCTION_OP, function);
        addIR(newIR(CALL_IR, place, funcOp));
        return;
    }
}

void translate_Exp_ARRAY_VISIT(Node root, Operand place){

}

void translate_Exp_STRUCT_VISIT(Node root, Operand place){

}

void translate_Exp_ID(Node root, Operand place){
    //TODO: May have some problem.

    place->kind = VARIABLE;
    strcpy(place->u.value, root->firstChild->val);
}

void translate_Exp_INT(Node root, Operand place){
    place->kind = CONSTANT;
    place->u.var_no = atoi(root->val);
}
