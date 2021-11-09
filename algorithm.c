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

Tree *createTreeNode(Get info) {

    Tree *create = (Tree *)malloc(sizeof(Tree));
    verifyError(create, __LINE__);
    create->right = NULL;
    create->left = NULL;
    create->list = NULL;

    strcpy(create->word, info.word);

    return create;
}

int insertTree(Tree **dictionary, Get info) {
    if (*dictionary == NULL) {
        *dictionary = createTreeNode(info);
    } else if (strcmpi(info.word, (*dictionary)->word) > 0) {
        insertTree(&(*dictionary)->right, info);
    } else if (strcmpi(info.word, (*dictionary)->word) < 0) {
        insertTree(&(*dictionary)->left, info);
    } else {
        insertNodeSorted(&(*dictionary)->list, info.idDOC, info.position);
        return -1;
    }
}

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