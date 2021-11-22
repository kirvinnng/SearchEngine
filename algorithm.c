#include "algorithm.h"
#include "gui.h"
#include "main.h"

Node *createNodeList(int idDOC, int position) {

    Node *create = (Node *)malloc(sizeof(Node));
    verifyError(create,__FILE__, __LINE__);

    create->next = NULL;

    create->idDOC = idDOC;
    create->position = position;

    return create;
}

Tree *createNodeTree(Get info) {

    Tree *create = (Tree *)malloc(sizeof(Tree));
    verifyError(create, __FILE__, __LINE__);
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

Tree *findWord(Tree *tree, char *word) {
    Tree *aux;
    if (tree) {
        if (!strcmpi(tree->word, word)) {
            tree->right = NULL;
            tree->left = NULL;
            return tree;
        } else {
            aux = findWord(tree->left, word);
            if (!aux) {
                aux = findWord(tree->right, word);
            }
        }
    } else {
        return NULL;
    }
    return aux;
}

Tree *findWordByDoc(Tree *tree, char *word, int idDoc) {
    Tree *aux = NULL;
    if (tree) {
        if (!strcmpi(tree->word, word)) {
            Node * list = matchIdDoc(tree->list, idDoc);
            if(list){
                // ! TODO: FIX TREE COPY
                return aux;
            }
        } else {
            aux = findWordByDoc(tree->left, word, idDoc);
            if (!aux) {
                aux = findWordByDoc(tree->right, word, idDoc);
            }
        }
    } else {
        return NULL;
    }
    return aux;
}

Node * matchIdDoc(Node *list, int idDoc){
    while(list && list->idDOC != idDoc){
        list = list->next;
    }
    if(list){
        Node *aux = list;
        while(aux->next && aux->next->idDOC == idDoc){
            aux = aux->next;
        }
        if(aux){
            aux->next = NULL;
            return list;
        }
    }
    return NULL;
}

