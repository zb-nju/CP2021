#include<stdio.h>
#include"ObjectCode.h"
#include"DataStruct.h"
#include"SymbolTable.h"

extern fp* fp;
Register regs[32];
Var varList;

void OCMain(InterCode head){
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
        case GET_ADDR_IR:{
            break;
        }
        case ASSIGN_ADDR_IR:{
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
        case ARG_IR:{
            break;
        }
        case CALL_IR:{
            break;
        }
        case PARAM_IR:{
            break;
        }
        case READ_IR:{
            OCRead(head);
            break;
        }
        case WRITE_IR:{
            OCWrite(head);
            break;
        }
        default:
            break;
        }
        head = head->next;
    }

}

void OCAssign(InterCode head){

}

void OCCal(InterCode head){
    int resReg = getReg(head->u.binop.result);
    int op1Reg = getReg(head->u.binop.op1);
    int op2Reg = getReg(head->u.binop.op2);
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
    writeMemory();
}

void OCRelopGoto(InterCode head){
    int xRegNo = getReg(head->u.if_goto.x);
    int yRegNo = getReg(head->u.if_goto.y);
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
    // 写入返回地址
    fprintf(fp, "lw $ra, 4($fp)\n");
    // 恢复栈指针
    fprintf(fp, "addi $ra, $fp, 8\n");
    // 恢复帧指针
    fprintf(fp, "lw $fp, 0($fp)\n");

    int regNo = loadReg(head->u.signleop.op);
    fprintf(fp, "move $v0, %s\n", regs[regNo].name);
    fprintf(fp, "jr $ra\n");
    freeRegs();
}

void OCRead(InterCode head){

}

void OCWrite(InterCode head){

}

void OCFunction(InterCode head){

}

void initRegs(){
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

void loadReg(Operand op){
    for(int i = 8; i < 16; i++){
        if(regs[i].free == 0){
            regs[i].free = 1;
            switch (op->kind){
                case CONSTANT_OP:
                    regs[i].node = NULL;
                    fprintf(fp, "li %s, %d", regs[i].name, op->u.var_no);
                    return i;
                case ADDRESS_OP:
                    Var var = getVar(op->u.value);
                    regs[i].var = var;
                    var->regNo = i;
                    fprintf(fp, "addi %s, $fp, %d\n", regs[i].name, var->offset);
                    return i;
                case VALUE_ADDR_OP:
                    Var var = getVar(op->u.value);
                    regs[i].var = var;
                    var->regNo = i;
                    fprintf(fp, "lw %s, %d($fp)\n", regs[i].name, var->offset);
                    fprintf(fp, "lw %s, 0(%s)\n", regs[i].name, regs[i].name);
                    return i;
                default:
                    perror("operand no solve:");
            }
        }
    }
}

Var getVar(Operand op){
    Var cur = varList;
    Var ans = NULL;
    while(cur != NULL){
        if(strcmp(cur->name, op->u.value) == 0){
            ans=cur;
            break;
        }
        cur=cur->next;
    }
    assert(ans != null);
    return ans;
}

void writeMemory(int regNo){
    fprintf(fp, "sw %s, %d($fp)\n", regs[regNo].name, regs[regNo].node->offset);
    freeRegs();
}

void freeRegs(){
    for(int i = 8; i < 16; i++)
        regs[i].free = 0;
}