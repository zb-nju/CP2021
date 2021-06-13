#ifndef _OBJECT_CODE_H_
#define _OBJECT_CODE_H_
#include"DataStruct.h"

void OCMain(InterCode head);
void OCAssign(InterCode head);
void OCCal(InterCode head);
void OCRelopGoto(InterCode head);
void OCReturn(InterCode head);
void OCCall(InterCode head);
void OCRead(InterCode head);
void OCWrite(InterCode head);
void handle_val(Operand op);
void OCFunction(InterCode head);
void initRegs();
void OCHeader();
int loadReg(Operand op);
Var getVar(Operand op);
void writeMemory(int regNo);
void freeRegs();

#endif