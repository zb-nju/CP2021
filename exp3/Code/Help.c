#include"Help.h"
#include"MyEnum.h"
#include"stdio.h"
#include<string.h>
#include<stdlib.h>

int stringToInt(const char* const p){
    int ret = 0;
    for(int i = 0; p[i] != '\0'; i++)
        ret = ret * 10 + p[i] - '0';
    return ret;
}

char* intToString(int a){
    char *b = (char*)malloc(4);
    sprintf(b, "int: %d", a);
    return b;
}

int calculateArgc(const FieldList const p){
    FieldList temp = p;
    int ret = 0;
    while(temp != NULL){
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

void printType(Type t){
    printf("kind : ");
    switch (t->kind)
    {
    case BASIC:
        printf("basic ");
        switch (t->u.basic)
        {
        case Type_INT:
            printf("int/n");
            break;
        case Type_FLOAT:
            printf("float/n");
            break;
        default:
            break;
        }
        break;
    case ARRAY:
        printf("array, size: %d, elem type:\n", t->u.array.size);
        printType(t->u.array.elem);
        break;
    case STRUCTURE:
        printf("structure/n");
        break;
    case FUNCTION:
        printf("function/n");
        break;
    default:
        break;
    }
}