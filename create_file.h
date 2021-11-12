#pragma once

#include "main.h"

FILE *openFile(char *extensionFile, char *mode);
void closeFile(FILE *buff);

int getFlag(char *extension);

void createJSON(Tree *tree);
void createHTML(Tree *tree);
void createTXT(Tree *tree);
void createBinary(Tree *tree);

void createDictionary(Tree *tree, FILE *buff, char *extension);
void listToFile(Node *list, char *word, FILE *buff, char *extension, Tree *tree);

void printFirstPart(int flag, FILE *buff, char *word);
void printMiddlePart(int flag, FILE *buff, Get info, Node *list);
void printLastPart(int flag, FILE *buff);
