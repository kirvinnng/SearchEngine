#pragma once

#include "main.h"

#define DICTIONARY "document/dictionary.bin"

void readAllFiles(Tree **tree);

void readFile(char *fileName, Tree **tree, int fileID);
void saveInfoIntoTree(Tree **tree, Get info);

int verifyCharAlpha(char caracter);
Get fillStructField(char *word, int position, int fileID);

void addFolder(char *file);

FILE *openFile();
void closeFile(FILE *buff);
void createDictionary(Tree *tree, FILE *buff);
void readDictionary(Tree **tree);
void listToFile(Node *list, char *word, FILE *buff);