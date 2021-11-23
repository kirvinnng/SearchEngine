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
    if (list) {
        insertNodeSorted(&new, list->idDOC, list->position);
        Node *act = list->next;
        //*  insert nodes with the same id

        while (act && act->idDOC == idDoc) {
            insertNodeSorted(&new, act->idDOC, act->position);
            act = act->next;
        }
    }

    return new;
}

Node *matchIdDoc(Node *list, int idDoc) {
    return (list) ? splitList(list, idDoc) : NULL;
}

//* Check if a position exists
int existNodeAtPosition(Node *list, int pos) {
    int found = 0;
    while (list && found == 0) {
        if (list->position == pos) {
            found = 1;
        }
        list = list->next;
    }

    return found;
}

int getListPositionAtIndex(Node *list, int pos) {
    for (int i = 0; i < pos; i++) {
        list = list->next;
    }
    return list->position;
}

//* Separates a sentence word by word and stores it in the bidimensional array
int splitString(char tokens[500][50], char *phrase) {
    char *delim = ". ,-;:'¡!\"#$%%&/()=?¿·~^¨+-ºª{}[]<>\\*";
    char *token;

    int counter = 0;

    token = strtok(phrase, delim);
    while (token != NULL) {
        strcpy(tokens[counter++], token);
        token = strtok(NULL, delim);
    }

    return counter;
}

//* Search a phrase in the tree
SearchResult searchPhraseOnTree(Tree *tree, char *phrase, int id) {
    char phraseAux[500];
    strcpy(phraseAux, phrase);

    char tokens[500][50];

    int counter = splitString(tokens, phraseAux);

    Tree *treeWords[400];
    int found = 1;
    for (int i = 0; found && i < counter; i++) {
        treeWords[i] = findWordByDoc(tree, tokens[i], id);
        if (!treeWords[i]) {
            found = 0;
        }
    }

    if (!found) {
        return (SearchResult){.foundAllWords = found, .allWordsInOrder = false, .wordInitialPosition = -1};
    }

    int exist = 0;
    int initialPos = treeWords[0]->list->position;
    for (int i = 0; !exist && i < treeWords[0]->length; i++) {
        exist = 1;
        initialPos = getListPositionAtIndex(treeWords[0]->list, i);
        for (int j = 1; j < counter; j++) {
            if (!existNodeAtPosition(treeWords[j]->list, initialPos + j)) {
                exist = 0;
            }
        }
    }

    return (SearchResult){.foundAllWords = found, .allWordsInOrder = exist, .wordInitialPosition = initialPos};
}

//* Search for the most frequent word in a document by id
FrequentWord frequentWordByDocumentID(Tree *tree, int idDoc) {
    FrequentWord fwHead;
    FrequentWord fwLeft;
    FrequentWord fwRight;
    if (tree) {
        fwLeft = frequentWordByDocumentID(tree->left, idDoc);
        fwRight = frequentWordByDocumentID(tree->right, idDoc);

        //* separate the list, and count his nodes
        fwHead.frequency = countListNode(splitList(tree->list, idDoc));
        strcpy(fwHead.word, tree->word);

        return fwHead.frequency > fwLeft.frequency ? (fwHead.frequency > fwRight.frequency ? fwHead : fwRight)
                                                   : (fwLeft.frequency > fwRight.frequency ? fwLeft : fwRight);
    } else {

        return (FrequentWord){.frequency = -1};
    }
}

int levenshtein(char *s1, char *s2) {
    int t1, t2, i, j, *m, costo, res, ancho;
    t1 = strlen(s1);
    t2 = strlen(s2);
    if (t1 == 0)
        return (t2);
    if (t2 == 0)
        return (t1);

    ancho = t1 + 1;
    m = (int *)calloc(sizeof(int), (t1 + 1) * (t2 + 1));
    verifyError(m, __FILE__, __LINE__);

    for (i = 0; i <= t1; i++)
        m[i] = i;
    for (j = 0; j <= t2; j++)
        m[j * ancho] = j;

    for (i = 1; i <= t1; i++)
        for (j = 1; j <= t2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                costo = 0;
            } else {
                costo = 1;
                m[j * ancho + i] =
                    min(min(m[j * ancho + i - 1] + 1, m[(j - 1) * ancho + i] + 1), m[(j - 1) * ancho + i - 1] + costo);
            }
        }
    res = m[t2 * ancho + t1];
    free(m);

    return res;
}