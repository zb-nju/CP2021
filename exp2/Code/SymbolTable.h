#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include"DataStruct.h"

TableNode SymbolTable[HASH_TABLE_SIZE];

int hash(Type type);

// #define true 1
// #define false 0
int insert(TableNode tableNode);
//检查是否存在符号冲突
int checkConflict(TableNode tableNode);
//根据名字检查符号是否存在于符号表中
int find(char* name);

#endif