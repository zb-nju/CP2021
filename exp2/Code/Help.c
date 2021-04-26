#include"Help.h"
#include"MyEnum.h"
#include"stdio.h"
#include<string.h>

int stringToInt(const char* const p){
    int ret = 0;
    for(int i = 0; p[i] != '\0'; i++)
        ret = ret * 10 + p[i] - '0';
    return ret;
}

int calculateArgc(const FieldList const p){
    FieldList temp = p;
    int ret = 0;
    while(p != NULL){
        ret++;
        temp = temp->next;
    }
    return ret;
}

Boolean judgeType(Type a, Type b){
    if(a->kind != b->kind){
        return false;
    }

    if(a->kind == BASIC){
        if(a->u.basic == b->u.basic){
            return true;
        }else{
            return false;
        }
    }else if(a->kind == ARRAY){
        if(judgeType(a->u.array.elem,b->u.array.elem)==1)
        {
            return true;
        }
        else return false;
    }else if(a->kind == STRUCTURE){
        if(strcmp(a->u.structure->name, b->u.structure->name) == 0){  // Name Equivalence
            return true;
        }
        else return false;
    }else if(a->kind == FUNCTION){
        // TODO: maybe is not right
        return strcmp(a->u.function.name, b->u.function.name) == 0 && judgeType(a->u.function.returnType, b->u.function.returnType);
    }
}