#ifndef _NODE_H_
#define _NODE_H_

#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"assert.h"
#include"stdarg.h"

#define true 1
#define false 0

typedef struct Node_* Node;

typedef struct Node_{
    char *name;
    char *val;
    int isToken;
    int lineNum;

    Node firstChild;
    Node nextBrother;
};

Node createNode(int lineNum, char* name, char* val, int isToken,  int childNum, ...);

void printTree(Node root, int depth);

#endif
