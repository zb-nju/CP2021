#include "InterCode.h"
#include "SymbolTable.h"
#include "Help.h"
#include "MyEnum.h"
#include "Semantic.h"
#include<stdlib.h>
#include<stdio.h>
#include<stdarg.h>
#include<string.h>

// #define DEBUG

extern FILE* fp;
extern InterCode head;
extern InterCode tail;
int tempNums = 0;
int variableNums = 0;
int arrayNums = 0;
int structNums = 0;
int labelNums = 0;
FieldList lastField;

void printOp(Operand op){
    switch (op->kind)
    {
    case CONSTANT_OP:
        fprintf(fp, "#%d", op->u.var_no);
        break;
    case ADDRESS_OP:
        fprintf(fp, "&%s", op->u.value);
        break;
    case VALUE_ADDR_OP:
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
    InterCode code = (InterCode)malloc(sizeof(struct InterCode_));
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
        code->u.signleop.op = deepCopyOperand(va_arg(vaList, Operand));
        break;
    }
    case ASSIGN_IR:
    case GET_ADDR_IR:
    case GET_VALUE_IR:
    case ASSIGN_ADDR_IR:
    case CALL_IR:{
        code->u.assign.left = deepCopyOperand(va_arg(vaList, Operand));
        code->u.assign.right = deepCopyOperand(va_arg(vaList, Operand));
        break;
    }
    case ADD_IR:
    case SUB_IR:
    case MUL_IR:
    case DIV_IR:{
        code->u.binop.result = deepCopyOperand(va_arg(vaList, Operand));
        code->u.binop.op1 = deepCopyOperand(va_arg(vaList, Operand));
        code->u.binop.op2 = deepCopyOperand(va_arg(vaList, Operand));
        break;
    }
    case RELOP_GOTO_IR:{
        code->u.if_goto.x = deepCopyOperand(va_arg(vaList, Operand));
        //printf("va_arg(vaList, char*): %s\n",va_arg(vaList, char*));
        strcpy(code->u.if_goto.relop, va_arg(vaList, char*));
        //printf("code->u.if_goto.relop: %s\n",code->u.if_goto.relop);
        code->u.if_goto.y = deepCopyOperand(va_arg(vaList, Operand));
        code->u.if_goto.label_z = deepCopyOperand(va_arg(vaList, Operand));
        break;
    }
    case DEC_IR:{
        code->u.dec.op = deepCopyOperand(va_arg(vaList, Operand));
        code->u.dec.size = va_arg(vaList, int);
        break;
    }
    default:
        break;
    }
    return code;
}

Operand newOperand(int kind, ...){
    Operand op = (Operand)malloc(sizeof(struct Operand_));
    op->kind = kind;
    va_list vaList;
    va_start(vaList, kind);

    switch (kind)
    {
    case CONSTANT_OP:{
        op->u.var_no = va_arg(vaList, int);
        break;
    }
    // case VARIABLE_OP:
    // case ADDRESS_OP:
    // case TEMP_VAR_OP:
    // case ADDR_VALUE:
    // case FUNCTION_OP:
    // case LABEL_OP:
    // case RELOP_OP: {
    //     strcpy(op->u.value, va_arg(vaList, char*));
    //     break;
    // }
    default:
        strcpy(op->u.value, va_arg(vaList, char*));
        break;
    }

    return op;
}

Operand deepCopyOperand(Operand op){
    switch (op->kind)
    {
    case CONSTANT_OP:{
        return newOperand(CONSTANT_OP, op->u.var_no);
        break;
    }
    default:
        return newOperand(op->kind, op->u.value);
        break;
    }
}

Operand newTemp(){
    tempNums++;
    char tempName[10] = {0};
    sprintf(tempName, "t%d", tempNums);
    Operand ret = newOperand(TEMP_VAR_OP, tempName);
    return ret;
}

Operand newVariable(){
    variableNums++;
    char tempName[10] = {0};
    sprintf(tempName, "v%d", variableNums);
    Operand ret = newOperand(VARIABLE_OP, tempName);
    return ret;
}

Operand newArray(){
    arrayNums++;
    char tempName[10] = {0};
    sprintf(tempName, "v%d", arrayNums);
    Operand ret = newOperand(ARRAY_OP, tempName);
    return ret;
}

Operand newStruct(){
    structNums++;
    char tempName[10] = {0};
    sprintf(tempName, "v%d", structNums);
    Operand ret = newOperand(STRUCT_OP, tempName);
    return ret;
}

Operand newLabel(){
    labelNums++;
    char labelName[10] = {0};
    sprintf(labelName, "label%d", labelNums);
    Operand ret = newOperand(LABEL_OP, labelName);
    return ret;
}

//////////////////////////////////////////////////////////////////

void translate_Program(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Program", root->lineNum);
        perror(msg);
    #endif

    translate_ExtDefList(root->firstChild);
    printf("1");
}

void translate_ExtDefList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_ExtDefList", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;

    translate_ExtDef(root->firstChild);
    translate_ExtDefList(root->firstChild->nextBrother);
}
void translate_ExtDef(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_ExtDef", root->lineNum);
        perror(msg);
    #endif
    Node secondChild = root->firstChild->nextBrother;
    if (secondChild->name == Node_FunDec){
        translate_FunDec(secondChild);
        translate_CompSt(secondChild->nextBrother);
    }
}

void translate_Cond(Node root, Operand label_true, Operand label_false){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Cond", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    if(child->nextBrother->name == Node_RELOP){
        Operand t1 = newTemp();
        Operand t2 = newTemp();
        translate_Exp(child, t1);
        translate_Exp(child->nextBrother->nextBrother, t2);
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
        Operand const_zero = newOperand(CONSTANT_OP, 0);
        addIR(newIR(RELOP_GOTO_IR, t1, "!=", const_zero, label_true));
        addIR(newIR(GOTO_IR, label_false));
    }
}

void translate_CompSt(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_CompSt", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;

    if(root->firstChild->nextBrother->name == Node_DefList){
        translate_DefList(root->firstChild->nextBrother);
        translate_StmtList(root->firstChild->nextBrother->nextBrother);
    }else if(root->firstChild->nextBrother->name == Node_StmtList){
        translate_StmtList(root->firstChild->nextBrother);
    }
}

void translate_StmtList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_StmtList", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;
    if(root->firstChild != NULL){
        translate_Stmt(root->firstChild);
        translate_StmtList(root->firstChild->nextBrother);
    }
}

void translate_Stmt(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Stmt", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    if(child->name == Node_Exp){
        Operand t1 = newTemp();
        translate_Exp(child, t1);
    }else if(child->name == Node_CompSt){
        translate_CompSt(child);
    }else if(child->name == Node_RETURN){
        Operand t1 = newTemp();
        translate_Exp(child->nextBrother, t1);
        addIR(newIR(RETURN_IR, t1));
    }else if(child->name == Node_WHILE){
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand label3 = newLabel();
        addIR(newIR(LABEL_IR, label1));
        translate_Cond(child->nextBrother->nextBrother, label2, label3);
        addIR(newIR(LABEL_IR, label2));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(GOTO_IR, label1));
        addIR(newIR(LABEL_IR, label3));
    }else if(root->childNum == 5){      // Stmt → IF LP Exp RP Stmt
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        translate_Cond(child->nextBrother->nextBrother, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(LABEL_IR, label2));
    }else{                              // Stmt → IF LP Exp RP Stmt ELSE Stmt
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand label3 = newLabel();
        translate_Cond(child->nextBrother->nextBrother, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(GOTO_IR, label3));
        addIR(newIR(LABEL_IR, label2));
        translate_Stmt(child->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother->nextBrother);
        addIR(newIR(LABEL_IR, label3));
    }
}

void translate_DefList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_DefList", root->lineNum);
        perror(msg);
    #endif
    if (root->childNum == 0)
        return;

    translate_Def(root->firstChild);
    translate_DefList(root->firstChild->nextBrother);
}
void translate_Def(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Def", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;

    Node secondChild = root->firstChild->nextBrother;
    translate_DecList(secondChild);
}

int getSize(Type type){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "getSize");
        perror(msg);
    #endif
    assert(type!=NULL);
    if(type->kind == BASIC){
        return 4;
    }
    else if(type->kind == ARRAY){
        return type->u.array.size * getSize(type->u.array.elem);
    }
    else if(type->kind == STRUCTURE){
        int ret = 0;
        FieldList tmp = type->u.structure;
        while(tmp != NULL){
            ret += getSize(tmp->type);
            tmp = tmp->next;
        }
        return ret;
    }
}

void translate_DecList(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_DecList", root->lineNum);
        perror(msg);
    #endif
    translate_Dec(root->firstChild);
    if (root->childNum == 3)
        translate_DecList(root->firstChild->nextBrother->nextBrother);
}
void translate_Dec(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Dec", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    Operand v1 = newVariable();
    if (root->childNum == 1){
        translate_VarDec(child, v1);  //TODO
    }
    else if (root->childNum == 3){
        translate_VarDec(child, v1);
        Operand t2 = newTemp();
        translate_Exp(child->nextBrother->nextBrother, t2);
        addIR(newIR(ASSIGN_IR, v1, t2));
    }
}

void translate_VarDec(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_VarDec", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    if(root->childNum == 1){
        getTableNode(child->val)->op = place;
        if(getTableNode(child->val)->type->kind == STRUCTURE){
            int size = getSize(getTableNode(child->val)->type);
            addIR(newIR(DEC_IR, place, size));
            place->kind = STRUCT_OP;
        }
    }
    else{
        getTableNode(child->firstChild->val)->op = place;
        int arrSize = getSize(getTableNode(child->firstChild->val)->type);
        addIR(newIR(DEC_IR, place, arrSize));
        place->kind = ARRAY_OP;
    }
}

void translate_FunDec(Node root){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_FunDec", root->lineNum);
        perror(msg);
    #endif

    //get function's tablenode
    TableNode tNode = getTableNode(root->firstChild->val);
    addIR(newIR(FUNCTION_IR, newOperand(FUNCTION_OP, tNode->name)));

    FieldList fl = tNode->type->u.function.argv;
    while(fl != NULL){
        Operand op = newVariable();
        switch (fl->type->kind)
        {
        case STRUCTURE:
            op->kind = STRUCT_ADDR_OP;
            break;
        case ARRAY:
            op->kind = ARRAY_ADDR_OP;
            break;
        default:
            break;
        }
        getTableNode(fl->name)->op = op;
        addIR(newIR(PARAM_IR, op));
        fl = fl->next;
    }
}

void translate_Exp(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp", root->lineNum);
        perror(msg);
    #endif
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
        lastField = NULL;
    }else if(root->childNum == 3){
        if(child->name == Node_Exp){
            Node secondChild = child->nextBrother;
            if(secondChild->name == Node_ASSIGNOP){
                translate_Exp_ASSIGNOP(root, place);
            }
            else if(secondChild->name == Node_AND || secondChild->name == Node_OR){
                translate_Exp_AND_OR(root, place);
            }
            else if(secondChild->name == Node_DOT)
                translate_Exp_STRUCT_VISIT(root, place);
            else{
                translate_Exp_RELOP_CAL(root, place);
            }
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
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_ASSIGNOP", root->lineNum);
        perror(msg);
    #endif
    Operand t1 = newTemp();
    translate_Exp(root->firstChild->nextBrother->nextBrother, t1);
    Operand t2 = newTemp();
    translate_Exp(root->firstChild, t2);
    addIR(newIR(ASSIGN_IR, t2, t1));
}

void translate_Exp_AND_OR(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_AND_OR", root->lineNum);
        perror(msg);
    #endif
    Operand label1 = newLabel();
    Operand label2 = newLabel();
    Operand const_zero = newOperand(CONSTANT_OP, 0);
    addIR(newIR(ASSIGN_IR, place, const_zero));
    translate_Cond(root, label1, label2);
    addIR(newIR(LABEL_IR, label1));
    Operand const_one = newOperand(CONSTANT_OP, 1);
    addIR(newIR(ASSIGN_IR, place, const_one));
    addIR(newIR(LABEL_IR, label2));
}

void translate_Exp_RELOP_CAL(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_RELOP_CAL", root->lineNum);
        perror(msg);
    #endif
    if(root->firstChild->nextBrother->name == Node_RELOP){
        Operand label1 = newLabel();
        Operand label2 = newLabel();
        Operand const_zero = newOperand(CONSTANT_OP, 0);
        addIR(newIR(ASSIGN_IR, place, const_zero));
        translate_Cond(root, label1, label2);
        addIR(newIR(LABEL_IR, label1));
        Operand const_one = newOperand(CONSTANT_OP, 1);
        addIR(newIR(ASSIGN_IR, place, const_one));
        addIR(newIR(LABEL_IR, label2));
    }else{  // PLUS, MINUS, STAR, DIV
        Operand t1 = newTemp();
        Operand t2 = newTemp();
        translate_Exp(root->firstChild, t1);
        translate_Exp(root->firstChild->nextBrother->nextBrother, t2);
        if(t1->kind == CONSTANT_OP && t2->kind == CONSTANT_OP){
            place->kind = CONSTANT_OP;
            switch (root->firstChild->nextBrother->name)
            {
            case Node_PLUS:
                place->u.var_no = t1->u.var_no + t2->u.var_no;
                break;
            case Node_MINUS:
                place->u.var_no = t1->u.var_no - t2->u.var_no;
                break;
            case Node_STAR:
                place->u.var_no = t1->u.var_no * t2->u.var_no;
                break;
            case Node_DIV:
                place->u.var_no = t1->u.var_no / t2->u.var_no;
                break;
            default:
                break;
            }
        }
        else{
            switch (root->firstChild->nextBrother->name)
            {
            case Node_PLUS:
                addIR(newIR(ADD_IR, place, t1, t2));
                break;
            case Node_MINUS:
                addIR(newIR(SUB_IR, place, t1, t2));
                break;
            case Node_STAR:
                addIR(newIR(MUL_IR, place, t1, t2));
                break;
            case Node_DIV:
                addIR(newIR(DIV_IR, place, t1, t2));
                break;
            default:
                break;
            }
        }
    }
}

void translate_Exp_LPRP(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_LPRP", root->lineNum);
        perror(msg);
    #endif
    translate_Exp(root->firstChild->nextBrother, place);
}

void translate_Exp_MIUNS(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_MIUNS", root->lineNum);
        perror(msg);
    #endif
    Operand t1 = newTemp();
    translate_Exp(root->firstChild->nextBrother, t1);
    Operand t2 = newOperand(CONSTANT_OP, 0);
    addIR(newIR(SUB_IR, place, t2, t1));
}

void translate_Exp_NOT(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_NOT", root->lineNum);
        perror(msg);
    #endif
    Operand label1 = newLabel();
    Operand label2 = newLabel();
    Operand const_zero = newOperand(CONSTANT_OP, 0);
    addIR(newIR(ASSIGN_IR, place, const_zero));
    translate_Cond(root, label1, label2);
    addIR(newIR(LABEL_IR, label1));
    Operand const_one = newOperand(CONSTANT_OP, 1);
    addIR(newIR(ASSIGN_IR, place, const_one));
    addIR(newIR(LABEL_IR, label2));
}

void translate_Args(Node root, Arg_list *arg_list){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Args", root->lineNum);
        perror(msg);
    #endif
    while(root->childNum != 1){
        Operand t1 = newTemp();
        translate_Exp(root->firstChild, t1);
        Arg_list tmp = (Arg_list)malloc(sizeof(struct Arg_list_));
        tmp->arg = t1;
        tmp->next = *arg_list;
        *arg_list = tmp;
        root = root->firstChild->nextBrother->nextBrother;
    }

    Operand t1 = newTemp();
    translate_Exp(root->firstChild, t1);
    Arg_list tmp = (Arg_list)malloc(sizeof(struct Arg_list_));
    tmp->arg = t1;
    tmp->next = *arg_list;
    *arg_list = tmp;
}

void translate_Exp_FUNCTION_CALL(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_FUNCTION_CALL", root->lineNum);
        perror(msg);
    #endif
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
        translate_Args(root->firstChild->nextBrother->nextBrother, &arg_list);
        if(!strcmp(function, "write")){
            addIR(newIR(WRITE_IR, arg_list->arg));
            // Operand const_zero = newOperand(CONSTANT_OP, 0);
            // addIR(newIR(ASSIGN_IR, place, const_zero));
            return;
        }
        while (arg_list != NULL)
        {
            Operand arg = arg_list->arg;
            // 传引用
            if(arg->kind == STRUCT_OP || arg->kind == ARRAY_OP)
                arg->kind = ADDRESS_OP;

            addIR(newIR(ARG_IR, arg));
            arg_list = arg_list->next;
        }
        Operand funcOp = newOperand(FUNCTION_OP, function);
        addIR(newIR(CALL_IR, place, funcOp));
        return;
    }
}

void translate_Exp_ARRAY_VISIT(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_ARRAY_VISIT", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    Operand t1 = newTemp();
    Operand t2 = newTemp();
    translate_Exp(child, t1);

    // 通过指针访问
    if(t1->kind == ARRAY_ADDR_OP){
        // 无需操作
    }
    // 通过名字访问
    else{
        // 先取地址
        t1->kind = ADDRESS_OP;
    }
    // 下标
    translate_Exp(child->nextBrother->nextBrother, t2);
    Type exp = Exp(child);
    int size = getSize(exp->u.array.elem);
    if(t2->kind == CONSTANT_OP){
        t2->u.var_no *= size;
        addIR(newIR(ADD_IR, place, t1, t2));
    }
    else{
        Operand t3 = newTemp();
        addIR(newIR(MUL_IR, t3, newOperand(CONSTANT_OP, size), t2));
        addIR(newIR(ADD_IR, place, t1, t3));
    }
    if(exp->u.array.elem->kind == STRUCTURE){
        place->kind = STRUCT_ADDR_OP;
    }
    else{
        place->kind = VALUE_ADDR_OP;
    }
    perror("finish array");
}

void translate_Exp_STRUCT_VISIT(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_STRUCT_VISIT", root->lineNum);
        perror(msg);
    #endif
    Node child = root->firstChild;
    Operand t1 = newTemp();

    //get struct val and store in t1
    translate_Exp(child, t1);
    // 通过指针访问
    if(t1->kind == STRUCT_ADDR_OP){
        // 无需操作
    }
    // 通过名字访问
    else{
        // 先取地址
        t1->kind = ADDRESS_OP;
    }

    char* structName;
    FieldList field;
    if(child->firstChild->name == Node_ID){
        structName = child->firstChild->val;
        field = getTableNode(structName)->type->u.structure;
    }
    else{
        field = child->firstChild->type->u.array.elem->u.structure;
    }
    char* fieldName = child->nextBrother->nextBrother->val;
    int offset = 0;
    while(field != NULL){
        if(!strcmp(field->name,fieldName)){
            lastField = field;
            break;
        }
        assert(field!=NULL);
        offset += getSize(field->type);
        field = field->next;
    }

    addIR(newIR(ADD_IR, place, t1, newOperand(CONSTANT_OP, offset)));
    if(field->type->kind == ARRAY){
        place->kind = ARRAY_ADDR_OP;
    }
    else if(field->type->kind == STRUCTURE){
        place->kind = STRUCT_ADDR_OP;
    }
    else{
        place->kind = VALUE_ADDR_OP;
    }
    perror("finish struct");
}

void translate_Exp_ID(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_ID", root->lineNum);
        perror(msg);
    #endif
    //TODO: May have some problem.
    Operand op = getTableNode(root->firstChild->val)->op;
    if(op != NULL)
        memcpy(place, op, sizeof(struct Operand_));
    else
        strcpy(place->u.value, root->firstChild->val);
}

void translate_Exp_INT(Node root, Operand place){
    #ifdef DEBUG
        char msg[40];
        sprintf(msg, "line: %d, translate_Exp_INT", root->lineNum);
        perror(msg);
    #endif
    place->kind = CONSTANT_OP;
    place->u.var_no = atoi(root->val);
}
