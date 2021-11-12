#pragma once

#include "main.h"

void insertNodeSorted(Node **list, int idDoc, int position);
int insertTree(Tree **dictionary, Get info);
Tree *createNodeTree(Get info);
Node *createNodeList(int idDOC, int position);

void countTreeNode(Tree *tree, int *acum);
int countListNode(Node *list);