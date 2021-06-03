#include "./rope.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "utils.h"

#define EMPTY ""

char *strdup(const char *s);

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
 	// if (rn->left != NULL) {
 	// 	__indexRope(rn->left, idx);
 	// } else if (rn->right != NULL) {
 	// 	__indexRope(rn->right, idx);
 	// } else {
 	// 	int lenght = strlen(rn->str);

 	// 	if (*idx < lenght)
 	// 		return (rn->str)[*idx];
 	// 	else
 	// 		*idx = *idx - lenght;
 	// }

 // 	if (!rn->left && !rn->right) {
 		
	//  	int lenght = strlen(rn->str);

	//  	if (*idx < lenght) {
	//  		*result = (rn->str)[*idx];
	//  		return;
	//  	} else {
	//  		*idx = *idx - lenght;
	//  	}
	// }

	// if (rn->left != NULL)
 // 		__indexRope(rn->left, idx, c);
 	
 // 	if (rn->right != NULL)
 // 		__indexRope(rn->right, idx, c);

	if (!rn->left && !rn->right)
		return (rn->str)[*idx];

	int weight = getNodeWeight(rn->left);

	if (*idx < weight) {
		return __indexRope(rn->left, idx);
	} else {
		*idx -= weight;
		return __indexRope(rn->right, idx);
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

char indexRope(RopeTree* rt, int idx) {
     // TODO 2. Index - 10p
    if (rt)
    	return __indexRope(rt->root, &idx);
     	
    return 'x';
    // if(!rt)
    // return 'x';
    // int length = getNodeWeight(rt->root->left) + getNodeWeight(rt->root->right);
    // char *str = calloc(length + 1, sizeof(char));
    // form_str(rt->root, str);
    // char c = str[idx];
    // free(str);
    // return c;
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

static void first_split(RopeNode* rn, int *idx) {

	if (!rn->left && !rn->right) {
		if (*idx) {
			char *str1 = malloc(*idx + 1);
			char *str2 = malloc(rn->weight - *idx + 1);
			
			int i;
			
			for (i = 0; i < *idx; i++)
   				str1[i] = (rn->str)[i];

   			str1[i] = '\0';

   			for (i = *idx; i < rn->weight; i++)
   				str2[i - *idx] = (rn->str)[i];

   			str2[i - *idx] = '\0';

			free((void *)(rn->str));
			rn->str = strdup(EMPTY);

			RopeNode *rn1 = makeRopeNode(str1);
			RopeNode *rn2 = makeRopeNode(str2);

			rn->left = rn1;
			rn->right = rn2;
			rn->weight = getNodeWeight(rn->left);
		}

		return;
	}

	int weight = getNodeWeight(rn->left);

	if (*idx < weight) {
		first_split(rn->left, idx);
	} else {
		*idx -= weight;
		first_split(rn->right, idx);
	}
}

RopeNode* concat_nodes(RopeNode* rn1, RopeNode* rn2) {
    RopeNode *new_root = makeRopeNode(strdup(EMPTY));    
    new_root->weight = rn1->weight;
    new_root->left = rn1;
    new_root->right = rn2;
    //printf("%s\n", new_root->right->str);
    // RopeTree *new_tree = makeRopeTree(new_root);
    return new_root;
}

static RopeNode* second_split(RopeNode* rn, int *idx, char c) {

	if ((rn->left->str)[0] == c) {
		RopeNode* rn_right_copy = rn->right;
		RopeNode* rn_left_copy = rn->left;
		rn->right = NULL;
		rn->left = NULL;
		return concat_nodes(rn_left_copy, rn_right_copy);
	} else if ((rn->right->str)[0] == c) {
		RopeNode* rn_right_copy = rn->right;
		rn->right = NULL;
		return rn_right_copy;
	}

	int weight = getNodeWeight(rn->left);

	if (*idx < weight) {
		//printf("weight: %d, string: %s \n", rn->weight, rn->str);
		RopeNode *second_node_right = rn->right;
		rn->right = NULL;
		return concat_nodes(second_split(rn->left, idx, c), second_node_right);
	} else {
		//printf("weight: %d, string: %s \n", rn->weight, rn->str);
		*idx -= weight;
		return second_split(rn->right, idx, c);
	}
}

RopeNode *tree_copy(RopeNode *rn) {
	if(rn == NULL)
    	return NULL;
    
    RopeNode* runner = makeRopeNode(strdup(rn->str));
    runner->weight = rn->weight;
    
    runner->left = tree_copy(rn->left);
    runner->right = tree_copy(rn->right);
    
    return runner;
}

SplitPair split(RopeTree* rt, int idx) {
    // TODO 4. Split - 20p

    SplitPair pair;

    int copy_idx = idx;

    // copie la tree ul initial
    RopeNode* new_root = tree_copy(rt->root);

    if (idx >= getNodeWeight(new_root)) {
    	pair.left = new_root;
    	pair.right = NULL;
    	return pair;
    }

    char key = indexRope(rt, copy_idx);

    // 1st split (daca nu e primul caracter din frunza)
	copy_idx = idx;
	first_split(new_root, &copy_idx);

	copy_idx = idx;

	//2nd split;
	//second_split(new_root, &copy_idx, key);
    pair.right = second_split(new_root, &copy_idx, key);
    pair.left = new_root;
    //pair.right = new_root;
    if(pair.left == NULL || pair.right == NULL)
    printf("\n");
    return pair;
}

RopeTree* insert(RopeTree* rt, int idx, const char* str) {
    // TODO 5. Insert - 5p
    if(!rt)
    return NULL;
    SplitPair pair = split(rt, idx);
    RopeNode *new_node = makeRopeNode(str);
    RopeNode *new_root = concat_nodes(pair.left, new_node);
    RopeNode *final_node = concat_nodes(new_root, pair.right);
    RopeTree *new_tree = makeRopeTree(final_node);
    return new_tree;
}

RopeTree* delete(RopeTree* rt, int start, int len) {
    // TODO 6. Delete - 5p
    if(!rt)
    return NULL;
    SplitPair first_pair = split(rt, start);
    SplitPair second_pair = split(rt, start + len);
    RopeNode *new_root = concat_nodes(first_pair.left, second_pair.right);
    RopeTree *new_tree = makeRopeTree(new_root);
    return new_tree;
}

// FINAL 10p -> complex test involving all operations