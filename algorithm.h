#pragma once

#include "main.h"

#include <stdbool.h>

typedef struct SearchResult {
    bool foundAllWords;
    bool allWordsInOrder;
    int wordInitialPosition;
} SearchResult;

typedef struct FrequentWord {
    char word[50];
    int frequency;
} FrequentWord;

typedef struct WordSimilarity {
    char originalWord[50];
    char similarWord[50];
    int distance;
} WordSimilarity;

Tree *createNodeTree(char *word);
Node *createNodeList(int idDOC, int position);

void insertNodeSorted(Node **list, int idDoc, int position);
int insertTree(Tree **dictionary, Get info);

void countTreeNode(Tree *tree, int *acum);
int countListNode(Node *list);
int existNodeAtPosition(Node *list, int pos);
int getListPositionAtIndex(Node *list, int pos);

int splitString(char tokens[500][50], char *phrase);

Tree *findWord(Tree *tree, char *word);
Tree *findWordByDoc(Tree *tree, char *word, int idDoc);
Node *matchIdDoc(Node *list, int idDoc);
Node *splitList(Node *list, int idDoc);
SearchResult searchPhraseOnTree(Tree *tree, char *phrase, int id);

FrequentWord frequentWordByDocumentID(Tree *tree, int idDOC);

int levenshtein(char *s1, char *s2);
WordSimilarity _didYouMean(Tree *tree, char *word);