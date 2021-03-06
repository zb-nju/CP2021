#ifndef _NODE_H_
#define _NODE_H_

#include"stdio.h"
#include"stdlib.h"
#include"string.h"
#include"assert.h"
#include"stdarg.h"

#include"MyEnum.h"

typedef struct Node_* Node;

struct Node_{
    char *val;
    NodeName name;
    int isToken;
    int lineNum;
    int childNum;

    Node firstChild;
    Node nextBrother;
};

Node createNode(int lineNum, NodeName name, char* val, int isToken,  int childNum, ...);

void printTree(Node root, int depth);

#endif
