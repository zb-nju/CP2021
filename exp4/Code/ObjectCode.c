#include<stdio.h>
#include"ObjectCode.h"
#include"Help.h"
#include"SymbolTable.h"
#include<assert.h>
#include<stdlib.h>
#include<string.h>

#define DEBUG

extern FILE* fp;
Register regs[32];
Var varList;
int func_offset;

void OCMain(InterCode head){
    #ifdef DEBUG
        perror("OCMain");
    #endif
    varList = NULL;
    initRegs();
    OCHeader();
    while (head!=NULL){
        switch (head->kind)
        {
        case LABEL_IR:{
            fprintf(fp, "%s:\n", head->u.signleop.op->u.value);
            break;
        }
        case FUNCTION_IR:{
            OCFunction(head);
            break;
        }
        case ASSIGN_IR:{
            OCAssign(head);
            break;
        }
        case ADD_IR: case SUB_IR: case MUL_IR: case DIV_IR:{
            OCCal(head);
            break;
        }
        case GOTO_IR:{
            fprintf(fp, "j %s\n", head->u.signleop.op->u.value);
            break;
        }
        case RELOP_GOTO_IR:{
            OCRelopGoto(head);
            break;
        }
        case RETURN_IR:{
            OCReturn(head);
            break;
        }
        case DEC_IR:{
            break;
        }
        case ARG_IR: case CALL_IR:{
            OCCall(head);
            while(head->kind != CALL_IR && head->kind != READ_IR)
                head = head->next;
            break;
        }
        case PARAM_IR:{
            break;
        }
        case WRITE_IR:{
            OCWrite(head);
            break;
        }
        case READ_IR:{
            OCRead(head);
            break;
        }
        default:
            break;
        }
        head = head->next;
    }

}

void OCAssign(InterCode head){
    #ifdef DEBUG
        perror("OCAssign");
    #endif
    int rightReg = loadReg(head->u.assign.right);
    int leftReg = 8;
    if(head->u.assign.left->kind == VALUE_ADDR_OP){
        while(regs[leftReg].free == 1 && leftReg < 16){
            leftReg++;
        }
        if(leftReg == 16){
            perror("No free reg left\n");
            assert(0);
        }
        regs[leftReg].free = 1;
        Var leftVar = getVar(head->u.assign.left);
        fprintf(fp, "lw %s, %d($fp)\n", regs[leftReg].name, leftVar->offset);
        fprintf(fp, "sw %s, 0(%s)\n", regs[rightReg].name, regs[leftReg].name);
    }else{
        leftReg = loadReg(head->u.assign.left);
        fprintf(fp, "move %s, %s\n",  regs[leftReg].name, regs[rightReg].name);
        writeMemory(leftReg);
    }
    freeRegs();
}

void OCCal(InterCode head){
    #ifdef DEBUG
        perror("OCCal");
    #endif
    int resReg = loadReg(head->u.binop.result);
    int op1Reg = loadReg(head->u.binop.op1);
    int op2Reg = loadReg(head->u.binop.op2);
    switch (head->kind)
    {
    case ADD_IR:
        fprintf(fp, "add %s, %s, %s\n", regs[resReg].name, regs[op1Reg].name, regs[op2Reg].name);
        break;
    case SUB_IR:
        fprintf(fp, "sub %s, %s, %s\n", regs[resReg].name, regs[op1Reg].name, regs[op2Reg].name);
        break;
    case DIV_IR:
        fprintf(fp, "div %s, %s, %s\n", regs[resReg].name, regs[op1Reg].name, regs[op2Reg].name);
        break;
    case MUL_IR:
        fprintf(fp, "mul %s, %s, %s\n", regs[resReg].name, regs[op1Reg].name, regs[op2Reg].name);
        break;
    default:
        break;
    }
    writeMemory(resReg);
}

void OCRelopGoto(InterCode head){
    #ifdef DEBUG
        perror("OCRelopGoto");
    #endif
    int xRegNo = loadReg(head->u.if_goto.x);
    int yRegNo = loadReg(head->u.if_goto.y);
    if(strcmp(head->u.if_goto.relop, "==") == 0){
        fprintf(fp, "beq %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    else if(strcmp(head->u.if_goto.relop, "!=") == 0){
        fprintf(fp, "bne %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    else if(strcmp(head->u.if_goto.relop, ">") == 0){
        fprintf(fp, "bgt %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    else if(strcmp(head->u.if_goto.relop, "<") == 0){
        fprintf(fp, "blt %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    else if(strcmp(head->u.if_goto.relop, ">=") == 0){
        fprintf(fp, "bge %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    else if(strcmp(head->u.if_goto.relop, "<=") == 0){
        fprintf(fp, "ble %s, %s, %s\n", regs[xRegNo].name, regs[yRegNo].name, head->u.if_goto.label_z->u.value);
    }
    freeRegs();
}

void OCReturn(InterCode head){
    #ifdef DEBUG
        perror("OCReturn");
    #endif
    // 写入返回地址
    fprintf(fp, "lw $ra, 4($fp)\n");
    // 恢复栈指针
    fprintf(fp, "addi $sp, $fp, 8\n");
    // 恢复帧指针
    fprintf(fp, "lw $fp, 0($fp)\n");

    int regNo = loadReg(head->u.signleop.op);
    fprintf(fp, "move $v0, %s\n", regs[regNo].name);
    fprintf(fp, "jr $ra\n");
    freeRegs();
}
int callnum = 0;

void OCCall(InterCode head){
    #ifdef DEBUG
        perror("OCCall");
    #endif
    callnum++;
    int offset = 0;
    while(head->kind == ARG_IR){
        offset += 4;
        fprintf(fp, "addi $sp, $sp, -4\n");
        int regNo = loadReg(head->u.signleop.op);
        fprintf(fp, "sw %s, 0($sp)\n", regs[regNo].name);
        regs[regNo].free = 0;
        head = head->next;
    }
    fprintf(fp, "jal %s\n", head->u.assign.right->u.value);
    fprintf(fp, "addi $sp, $sp, %d\n", offset);
    perror(intToString(callnum));
    perror(head->u.assign.right->u.value);
    int regNo = loadReg(head->u.assign.left);
    fprintf(fp, "move %s, $v0\n", regs[regNo].name);
    writeMemory(regNo);
}

void OCRead(InterCode head){
    #ifdef DEBUG
        perror("OCRead");
    #endif
    fprintf(fp, "jal read\n");
    int regNo = loadReg(head->u.signleop.op);
    fprintf(fp, "move %s, $v0\n", regs[regNo].name);
    writeMemory(regNo);
}

void OCWrite(InterCode head){
    #ifdef DEBUG
        perror("OCWrite");
    #endif
    int regNo = loadReg(head->u.signleop.op);
    fprintf(fp, "move $a0, %s\n", regs[regNo].name);
    fprintf(fp, "jal write\n");
    freeRegs();
}

void handle_val(Operand op){
    #ifdef DEBUG
        perror("handle_val");
    #endif
    if(op->kind == CONSTANT_OP){
        return;
    }
    if(getVar(op) == NULL){
        func_offset += 4;
        Var tmp=(Var)malloc(sizeof(struct Var_));
        strcpy(tmp->name, op->u.value);
        tmp->offset = (-1)*func_offset;

        tmp->next = varList;
        varList = tmp;
    }
}

void OCFunction(InterCode head){
    #ifdef DEBUG
        perror("OCFunction");
    #endif
    fprintf(fp, "\n%s:\n", head->u.signleop.op->u.value);
    fprintf(fp, "addi $sp, $sp, -8\n");
    fprintf(fp, "sw $fp, 0($sp)\n");
    fprintf(fp, "sw $ra, 4($sp)\n");
    fprintf(fp, "move $fp, $sp\n");
    func_offset = 0;
    int count = 0; //第几个参数
    head = head->next;
    while(head->kind == PARAM_IR){
        Var param=(Var)malloc(sizeof(struct Var_));
        strcpy(param->name, head->u.signleop.op->u.value);
        param->offset = 8 + count*4;

        // 将这个参数加到varlist中
        param->next = varList;
        varList = param;
        
        count++;
        head = head->next;
    }

    // 处理函数中出现的变量
    InterCode tmp = head;
    while(tmp != NULL && tmp->kind != FUNCTION_IR){
        switch (tmp->kind)
        {
        case ASSIGN_IR:{
            handle_val(tmp->u.assign.left);
            handle_val(tmp->u.assign.right);
            break;
        }
        case ADD_IR: case SUB_IR: case MUL_IR: case DIV_IR:{
            handle_val(tmp->u.binop.result);
            handle_val(tmp->u.binop.op1);
            handle_val(tmp->u.binop.op2);
            break;
        }
        case DEC_IR:{
            func_offset += tmp->u.dec.size;
            Var dec_var=(Var)malloc(sizeof(struct Var_));
            strcpy(dec_var->name, tmp->u.dec.op->u.value);
            dec_var->offset = (-1)*func_offset;
            dec_var->next = varList;
            varList = dec_var;
            break;
        }
        case CALL_IR:{
            handle_val(tmp->u.assign.left);
            break;
        }
        case ARG_IR: case WRITE_IR: case READ_IR:{
            handle_val(tmp->u.signleop.op);
            break;
        }
        case RELOP_GOTO_IR:{
            handle_val(tmp->u.if_goto.x);
            handle_val(tmp->u.if_goto.y);
            break;
        }
        default:
            break;
        }
        tmp = tmp->next;
    }
    
    fprintf(fp, "addi $sp, $sp, %d\n", (-1)*func_offset);
    freeRegs();
}

void initRegs(){
    #ifdef DEBUG
        perror("initRegs");
    #endif
    for(int i = 0; i < 32; i++){
        regs[i].free = 0;
        regs[i].var = NULL;
    }
    strcpy(regs[0].name,"$zero");
    strcpy(regs[1].name,"$at");
    strcpy(regs[2].name,"$v0");
    strcpy(regs[3].name,"$v1");
    strcpy(regs[4].name,"$a0");
    strcpy(regs[5].name,"$a1");
    strcpy(regs[6].name,"$a2");
    strcpy(regs[7].name,"$a3");
    strcpy(regs[8].name,"$t0");
    strcpy(regs[9].name,"$t1");
    strcpy(regs[10].name,"$t2");
    strcpy(regs[11].name,"$t3");
    strcpy(regs[12].name,"$t4");
    strcpy(regs[13].name,"$t5");
    strcpy(regs[14].name,"$t6");
    strcpy(regs[15].name,"$t7");
    strcpy(regs[16].name,"$s0");
    strcpy(regs[17].name,"$s1");
    strcpy(regs[18].name,"$s2");
    strcpy(regs[19].name,"$s3");
    strcpy(regs[20].name,"$s4");
    strcpy(regs[21].name,"$s5");
    strcpy(regs[22].name,"$s6");
    strcpy(regs[23].name,"$s7");
    strcpy(regs[24].name,"$t8");
    strcpy(regs[25].name,"$t9");
    strcpy(regs[26].name,"$k0");
    strcpy(regs[27].name,"$k1");
    strcpy(regs[28].name,"$gp");
    strcpy(regs[29].name,"$sp");
    strcpy(regs[30].name,"$fp");
    strcpy(regs[31].name,"$ra");
}

void OCHeader(){
    #ifdef DEBUG
        perror("OCHeader");
    #endif
    fprintf(fp, ".data\n");
    fprintf(fp, "_prompt: .asciiz \"Enter an integer:\"\n");
    fprintf(fp, "_ret: .asciiz \"\\n\"\n");
    fprintf(fp, ".globl main\n");
    fprintf(fp, ".text\n");
    fprintf(fp, "\n");
    fprintf(fp, "read:\n");
    fprintf(fp, "li $v0, 4\n");
    fprintf(fp, "la $a0, _prompt\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "li $v0, 5\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "jr $ra\n");

    fprintf(fp, "\n");
    fprintf(fp, "write:\n");
    fprintf(fp, "li $v0, 1\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "li $v0, 4\n");
    fprintf(fp, "la $a0, _ret\n");
    fprintf(fp, "syscall\n");
    fprintf(fp, "move $v0, $0\n");
    fprintf(fp, "jr $ra\n");
}

int loadReg(Operand op){
    #ifdef DEBUG
        perror("loadReg");
    #endif
    assert(op!=NULL);
    for(int i = 8; i < 16; i++){
        if(regs[i].free == 0){
            regs[i].free = 1;
            switch (op->kind){
                case CONSTANT_OP:{
                    perror("1");
                    regs[i].var = NULL;
                    fprintf(fp, "li %s, %d\n", regs[i].name, op->u.var_no);
                    return i;
                }
                case ADDRESS_OP:{
                    perror("2");
                    Var var = getVar(op);
                    regs[i].var = var;
                    var->regNo = i;
                    fprintf(fp, "addi %s, $fp, %d\n", regs[i].name, var->offset);
                    return i;
                }
                case VALUE_ADDR_OP:{
                    perror("3");
                    Var var = getVar(op);
                    regs[i].var = var;
                    var->regNo = i;
                    fprintf(fp, "lw %s, %d($fp)\n", regs[i].name, var->offset);
                    fprintf(fp, "lw %s, 0(%s)\n", regs[i].name, regs[i].name);
                    return i;
                }
                default:{
                    perror("4");
                    Var var = getVar(op);
                    regs[i].var = var;
                    var->regNo = i;
                    fprintf(fp, "lw %s, %d($fp)\n",regs[i].name, var->offset);
                    return i;
                }
            }
        }
    }
}

Var getVar(Operand op){
    #ifdef DEBUG
        perror("getVar");
    #endif
    Var cur = varList;
    Var ans = NULL;
    while(cur != NULL){
        if(strcmp(cur->name, op->u.value) == 0){
            ans=cur;
            break;
        }
        cur=cur->next;
    }
    // assert(ans != NULL);
    return ans;
}

void writeMemory(int regNo){
    #ifdef DEBUG
        perror("writeMemory");
    #endif
    fprintf(fp, "sw %s, %d($fp)\n", regs[regNo].name, regs[regNo].var->offset);
    freeRegs();
}

void freeRegs(){
    #ifdef DEBUG
        perror("freeRegs");
    #endif
    for(int i = 8; i < 16; i++)
        regs[i].free = 0;
}