#ifndef _HASH_TABLE_H_
#define _HASH_TABLE_H_
#include"DataStruct.h"
#include"MyEnum.h"

TableNode SymbolTable[HASH_TABLE_SIZE];

void initSymbolTable();

unsigned hash(char* forHash);

// #define true 1
// #define false 0
Boolean insert(TableNode tableNode);
//检查是否存在符号冲突
Boolean checkByTableNode(TableNode tableNode);
//根据名字检查符号是否存在于符号表中
Boolean checkByName(char* name);

#endif