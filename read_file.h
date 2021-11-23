#pragma once

#include "main.h"

#define DICTIONARY "document/dictionary"

void readAllFiles(Tree **tree);
void readFile(char *fileName, Tree **tree, int fileID);

void saveInfoIntoTree(Tree **tree, Get info);

int isValidCharacter(char character);
Get fillStructField(char *word, int position, int fileID);

void addFolder(char *file);
void addExtension(char *dir, char *extension);

TreeInfo readDictionary(Tree **tree);
int documentExists(int documentID[], int newID, int size);