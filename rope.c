#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""
char* strdup(const char*);

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

static char __indexRope(RopeNode *rn, int *idx)
 {
 	if (rn->left) {
 		__indexRope(rn->left, idx);
 	} else if (rn->right) {
 		__indexRope(rn->right, idx);
 	} else {
 		int lenght = strlen(rn->str);

 		if (*idx < lenght)
 			return (rn->str)[*idx];
 		else
 			*idx = *idx - lenght;
 	}
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

int isCharInStr(char *str, char c)
{
    unsigned int i;
    for(i = 0; i < strlen(str); i++) {
        if(str[i] == c) {
            return 1;
        }
    }
    return 0;
}

char indexRope(RopeTree* rt, int idx) {
     // TODO 2. Index - 10p
    //  if (rt)
    //  	__indexRope(rt->root, &idx);
    //  else
    //  	return 'x';
    if(!rt)
    return 'x';
    int length = getNodeWeight(rt->root->left) + getNodeWeight(rt->root->right);
    char *str = calloc(length + 1, sizeof(char));
    form_str(rt->root, str);
    char c = str[idx];
    free(str);
    return c;
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
    int i;
    for(i = start; i < end; i++) {
        strncat(new_str, &(str[i]), 1);
    }
    free(str);
    return new_str;
}

RopeNode* copyRopeNode(RopeNode* rn) {
    if (!rn)
        return NULL;

    RopeNode* new_rn = makeRopeNode(strdup(rn->str));
    new_rn->left = copyRopeNode(rn->left);
    new_rn->right = copyRopeNode(rn->right);
    return new_rn;
}

int whichSideIsChar(char c, RopeNode* rn)
{
    if(!rn)
    return 0;
    if(rn->left == NULL && rn->right == NULL) {
        if(isCharInStr(rn->str, c) == 1) 
        return 1;
    }
    
    return whichSideIsChar(c, rn->left);
    return whichSideIsChar(c, rn->right);
}

RopeTree* copyRopeTree(RopeTree* rt) {
    if (!rt)
        return NULL;

    RopeTree* new_rt = makeRopeTree(copyRopeNode(rt->root));
    return new_rt;
}


SplitPair split(RopeTree* rt, int idx) {
    // TODO 4. Split - 20p
    char the_char = indexRope(rt, idx);
    if(whichSideIsChar(the_char, rt->root->left) == 1) {
        RopeTree *first_rt = makeRopeTree(copyRopeNode(rt->root->right));
    }
    else {
        RopeTree *first_rt = makeRopeTree(copyRopeNode(rt->root->left));
    }

}

RopeTree* insert(RopeTree* rt, int idx, const char* str) {
    // TODO 5. Insert - 5p

}

RopeTree* delete(RopeTree* rt, int start, int len) {
    // TODO 6. Delete - 5p
    //split(start)

}

// FINAL 10p -> complex test involving all operations


