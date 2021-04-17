#include"SymbolTable.h"
#include"stdio.h"

void initSymbolTable(){
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        SymbolTable[i] = NULL;
    }
}

unsigned hash(char* forHash){
    unsigned hash = 1315423911;
    for(;*forHash; forHash++){
        hash ^= ((hash << 5) + *forHash + (hash >> 2));
        hash %= HASH_TABLE_SIZE;
    }
    return hash;
}

Boolean insert(TableNode tableNode){
    char* name = tableNode->name;
    int hashVal = hash(name);
    TableNode tNode = SymbolTable[hashVal], pre = NULL;
    while(tNode != NULL){
        if(strcmp(name, tNode->name) == 0)
            return false;
        pre = NULL;
        tNode = tNode->next;
    }
    if(pre == NULL)
        SymbolTable[hashVal] = tableNode;
    else
        pre->next = tableNode;
    return true;
}

Boolean checkByTableNode(TableNode tableNode){
    return checkByName(tableNode->name);
}

Boolean checkByName(char* name){
    int hashVal = hash(name);
    TableNode tNode = SymbolTable[hashVal];
    while(tNode != NULL){
        if(strcmp(name, tNode->name) == 0)
            return true;
        tNode = tNode->next;
    }
    return false;
}