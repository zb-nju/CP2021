#include"Help.h"

int stringToInt(const char* const p){
    int ret = 0;
    for(int i = 0; p[i] != '\0'; i++)
        ret = ret * 10 + p[i] - '0';
    return ret;
}