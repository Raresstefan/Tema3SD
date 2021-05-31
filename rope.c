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

int getNodeWeight(RopeNode *rt) {
    if(!rt)
    return 0;
    if(rt->left == NULL && rt->right == NULL)
    return rt->weight;
    return getNodeWeight(rt->left) + getNodeWeight(rt->right);
}


RopeTree* concat(RopeTree* rt1, RopeTree* rt2) {
    RopeNode *new_root = makeRopeNode(strdup(EMPTY));    
    new_root->weight = getNodeWeight(rt1->root);
    new_root->left = rt1->root;
    new_root->right = rt2->root;
    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}



char indexRope(RopeTree* rt, int idx) {
    // TODO 2. Index - 10p
}

void form_str(RopeNode *rn, char *str) {
    if(!rn)
    return;
        if(rn->left == NULL && rn->right == NULL) {
            strcat(str, rn->str);
            return;
        }
        form_str(rn->left, str);
        form_str(rn->right, str);
}

char* search(RopeTree* rt, int start, int end) {
    // TODO 3. Search - 20p
    if(!rt)
    return NULL;
    int length = getNodeWeight(rt->root->left) + getNodeWeight(rt->root->right);
    char *str = calloc(length + 1, sizeof(char));
    int nr = 0;
    int the_length = end - start;
    char *new_str = calloc((the_length + 1), sizeof(char));
    form_str(rt->root, str);
    unsigned int i;
    for(i = start; i < end; i++) {
        strncat(new_str, &(str[i]), 1);
    }
    free(str);
    return new_str;
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
