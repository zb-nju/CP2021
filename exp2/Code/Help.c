#include"Help.h"
#include"stdio.h"

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