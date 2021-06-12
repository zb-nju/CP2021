#ifndef _HELP_H_
#define _HELP_H_
#include"DataStruct.h"
#include"MyEnum.h"

int stringToInt(const char* const p);
char* intToString(int a);
int calculateArgc(const FieldList const p);
Boolean judgeType(Type a, Type b);
void printType(Type t);

#endif