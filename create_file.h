#pragma once

#include "main.h"

FILE *openFile(char *extensionFile, char *mode);
void closeFile(FILE *buff);

int getFlag(char *extensionFile);

void createJSON(Tree *tree);
void createHTML(Tree *tree);
void createTXT(Tree *tree);
void createBinary(Tree *tree);
void createFiles(Tree *tree);

void createDictionary(Tree *tree, FILE *buff, char *extensionFile);
void listToFile(Node *list, char *word, FILE *buff, char *extensionFile, Tree *tree);

void printFirstPart(int extensionID, FILE *buff, char *word);
void printMiddlePart(int extensionID, FILE *buff, Get info, Node *list);
void printLastPart(int extensionID, FILE *buff);
