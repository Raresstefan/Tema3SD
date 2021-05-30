#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""


RopeNode* makeRopeNode(const char* str) {
    // TODO
    RopeNode *new_node = malloc(sizeof(RopeNode));
    DIE(new_node == NULL, "new_node malloc failed");
    new_node->left = NULL;
    new_node->right = NULL;
    // new_node->str = malloc((strlen(str)) * sizeof(char));
    // DIE(new_node->str == NULL, "new_node->str malloc failed");
    // strcpy(new_node->str, str);
    new_node->str = str;
    new_node->weight = strlen(str);
    return new_node;
}

RopeTree* makeRopeTree(RopeNode* root) {
    // TODO
    if(root == NULL)
    return NULL;
    RopeTree *new_tree = malloc(sizeof(RopeTree));
    DIE(new_tree == NULL, "new_tree malloc failed");
    new_tree->root = root;
    return new_tree;
}


void printRopeNode(RopeNode* rn) {
    if (!rn)
        return;

    if (!(rn->left) && !(rn->right)) {
        printf("%s", rn->str);
        return;
    }

    printRopeNode(rn->left);
    printRopeNode(rn->right);
}

void printRopeTree(RopeTree* rt) {
    if (rt && rt->root) {
        printRopeNode(rt->root);
        printf("%s", "\n");
    }
}

void debugRopeNode(RopeNode* rn, int indent) {
    if (!rn)
        return;

    for (int i = 0; i < indent; ++i)
        printf("%s", " ");

    if (!strcmp(rn->str, EMPTY))
        printf("# %d\n", rn->weight);
    else
        printf("%s %d\n", rn->str, rn->weight);

    debugRopeNode(rn->left, indent+2);
    debugRopeNode(rn->right, indent+2);
}



// int getTotalWeight(RopeNode* rt) {
//     if (!rt)
//         return 0;

//     return rt->weight + getTotalWeight(rt->right);
// }

int getNodeWeight(RopeNode *rt) {
    if(!rt)
    return 0;
    if(rt->left == NULL && rt->right == NULL)
    return rt->weight;
    return getNodeWeight(rt->left) + getNodeWeight(rt->right);
}

// char *getStr(RopeNode *rt, char *str) {
//     if(!rt)
//     return NULL;
//     if(rt->left == NULL && rt->right == NULL)
//     strcat(str, rt->str);
    
// }


RopeTree* concat(RopeTree* rt1, RopeTree* rt2) {
    // TODO 1. Concat - 10p
    // const char *new_str = malloc((strlen(rt1->root->str) + strlen(rt1->root->str)) * sizeof(char));
    // strcpy(new_str, rt1->root->str);
    // strcpy(new_str, rt2->root->str);
    RopeNode *new_root = makeRopeNode(strdup(EMPTY));
    // new_root->str = "\0";
    
    new_root->weight = getNodeWeight(rt1->root);
    new_root->left = rt1->root;
    new_root->right = rt2->root;
    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}



char indexRope(RopeTree* rt, int idx) {
    // TODO 2. Index - 10p
}


char* search(RopeTree* rt, int start, int end) {
    // TODO 3. Search - 20p
}

SplitPair split(RopeTree* rt, int idx) {
    // TODO 4. Split - 20p
}

RopeTree* insert(RopeTree* rt, int idx, const char* str) {
    // TODO 5. Insert - 5p
}

RopeTree* delete(RopeTree* rt, int start, int len) {
    // TODO 6. Delete - 5p
}

// FINAL 10p -> complex test involving all operations
