#include"SymbolTable.h"
#include <stdio.h>
#include <string.h>

void initSymbolTable(){
    for(int i = 0; i < HASH_TABLE_SIZE; i++){
        SymbolTable[i] = NULL;
    }
}

unsigned hash(const char* const forHash){
    unsigned hash = 1315423911;
    for(int i = 0; forHash[i] != '\0'; i++){
        hash ^= ((hash << 5) + forHash[i] + (hash >> 2));
        hash %= HASH_TABLE_SIZE;
    }
    return hash;
}

Boolean insertIntoSymbolTable(TableNode tableNode){
    char* name = tableNode->name;
    int hashVal = hash(name);
    TableNode tNode = SymbolTable[hashVal], pre = NULL;
    while(tNode != NULL){
        if(strcmp(name, tNode->name) == 0)
            return false;
        pre = tNode;
        tNode = tNode->next;
    }
    if(pre == NULL)
        SymbolTable[hashVal] = tableNode;
    else
        pre->next = tableNode;
    return true;
}

Boolean checkSymbolByTableNode(TableNode tableNode){
    return checkSymbolByName(tableNode->name);
}

Boolean checkSymbolByName(const char* const name){
    int hashVal = hash(name);
    TableNode tNode = SymbolTable[hashVal];
    while(tNode != NULL){
        if(strcmp(name, tNode->name) == 0)
            return true;
        tNode = tNode->next;
    }
    return false;
}

TableNode getTableNode(const char* const name){
    if(name == NULL)
        return NULL;
    int hashVal = hash(name);
    TableNode tNode = SymbolTable[hashVal];
    while(tNode != NULL){
        if(strcmp(name, tNode->name) == 0)
            return tNode;
        tNode = tNode->next;
    }
    return NULL;
}

int lookUpStructField(const char* const structName, const char* const fieldName){
    TableNode tNode = getTableNode(structName);
    if(tNode == NULL || tNode->type->kind != STRUCTURE)
        return -1;
    int ret = 0;
    FieldList fl = tNode->type->u.structure;
    while(fl != NULL){
        if(!strcmp(fl->name, fieldName)){
            break;
        }
        else{
            // only int in struct
            ret += 4;
        }
        fl = fl->next;
    }
    return ret;
}