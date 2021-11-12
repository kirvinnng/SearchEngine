#include "algorithm.h"
#include "gui.h"
#include "main.h"

Node *createNodeList(int idDOC, int position) {

    Node *create = (Node *)malloc(sizeof(Node));
    verifyError(create, __LINE__);

    create->next = NULL;

    create->idDOC = idDOC;
    create->position = position;

    return create;
}

Tree *createNodeTree(Get info) {

    Tree *create = (Tree *)malloc(sizeof(Tree));
    verifyError(create, __LINE__);
    create->right = NULL;
    create->left = NULL;
    create->list = NULL;
    strcpy(create->word, info.word);

    return create;
}

//* Insert a new tree & list node
int insertTree(Tree **dictionary, Get info) {
    if (*dictionary == NULL) {
        *dictionary = createNodeTree(info);
        insertNodeSorted(&(*dictionary)->list, info.idDOC, info.position);
        (*dictionary)->length = countListNode((*dictionary)->list);

    } else {
        if (strcmpi(info.word, (*dictionary)->word) == 0) {
            insertNodeSorted(&(*dictionary)->list, info.idDOC, info.position);
            (*dictionary)->length = countListNode((*dictionary)->list);
            return -1;
        }

        if (strcmpi(info.word, (*dictionary)->word) > 0) {
            insertTree(&(*dictionary)->right, info);
        } else {
            insertTree(&(*dictionary)->left, info);
        }
    }
}

//* Insert a one node into linked list
void insertNodeSorted(Node **list, int idDoc, int position) {

    Node *newNode = createNodeList(idDoc, position);
    Node *next;
    Node *after;
    if (*list == NULL) {
        *list = newNode;
    } else {
        if (newNode->idDOC < (*list)->idDOC) {
            newNode->next = *list;
            *list = newNode;
        } else {
            next = (*list)->next;
            after = *list;
            while (next != NULL && next->idDOC < newNode->idDOC) {
                after = next;
                next = next->next;
            }
            after->next = newNode;
            newNode->next = next;
        }
    }
}
//* Count the number of nodes in the tree
void countTreeNode(Tree *tree, int *acum) {

    if (tree) {
        countTreeNode(tree->left, acum);
        countTreeNode(tree->right, acum);
        (*acum)++;
    }
}

//* Count the number of nodes in the list
int countListNode(Node *list) {

    int acum = 0;

    while (list) {
        acum++;
        list = list->next;
    }
    return acum;
}