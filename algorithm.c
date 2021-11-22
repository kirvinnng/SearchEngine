#include "algorithm.h"
#include "gui.h"
#include "main.h"
#include "read_file.h"

Node *createNodeList(int idDOC, int position) {

    Node *create = (Node *)malloc(sizeof(Node));
    verifyError(create, __FILE__, __LINE__);

    create->next = NULL;

    create->idDOC = idDOC;
    create->position = position;

    return create;
}

Tree *createNodeTree(char *word) {

    Tree *create = (Tree *)malloc(sizeof(Tree));
    verifyError(create, __FILE__, __LINE__);
    create->right = NULL;
    create->left = NULL;
    create->list = NULL;
    strcpy(create->word, word);

    return create;
}

//* Insert a new tree & list node
int insertTree(Tree **dictionary, Get info) {
    if (*dictionary == NULL) {
        *dictionary = createNodeTree(info.word);
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

Tree *findWord(Tree *tree, char *word) {
    Tree *aux;
    if (tree) {
        if (!strcmpi(tree->word, word)) {
            aux = createNodeTree(tree->word);
            aux->list = tree->list;
            aux->length = tree->length;
            return aux;

        } else {
            aux = findWord(tree->left, word);
            if (!aux) {
                aux = findWord(tree->right, word);
            }
        }
    } else {
        return NULL;
    }
}

Tree *findWordByDoc(Tree *tree, char *word, int idDoc) {
    Tree *aux = NULL;
    if (tree) {
        if (strcmpi(tree->word, word) == 0) {

            Node *newList = matchIdDoc(tree->list, idDoc);

            if (newList) {

                aux = createNodeTree(tree->word);
                aux->length = countListNode(newList);
                aux->list = newList;
            }

            return aux;

        } else {
            aux = findWordByDoc(tree->left, word, idDoc);
            if (!aux) {
                aux = findWordByDoc(tree->right, word, idDoc);
            }
        }
    } else {
        return NULL;
    }
}

//* Separates the list by different ids
Node *splitList(Node *list, int idDoc) {

    while (list && list->idDOC != idDoc) {
        list = list->next;
    }

    Node *new = NULL;
    insertNodeSorted(&new, list->idDOC, list->position);

    Node *act = list->next;

    //*  insert nodes with the same id
    while (act && act->idDOC == idDoc) {

        insertNodeSorted(&new, act->idDOC, act->position);
        act = act->next;
    }

    return new;
}

Node *matchIdDoc(Node *list, int idDoc) {

    return (list) ? splitList(list, idDoc) : NULL;
}
