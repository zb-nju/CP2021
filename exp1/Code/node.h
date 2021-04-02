#ifndef _NODE_H_
#define _NODE_H_

#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"assert.h"
#include"stdarg.h"

#define true 1
#define false 0

typedef struct node_{
    char *name;
    char *val;
    int isToken;
    int lineNum;

    struct node_* firstChild;
    struct node_* nextBrother;
}node;

node* createNode(int lineNum, char* name, char* val, int isToken,  int childNum, ...);

void printTree(node* root, int depth);

#endif
