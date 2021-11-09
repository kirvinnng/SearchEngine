#pragma once

#include "main.h"

void readAllFiles(Tree **tree);

void readFile(Get info, char *fileName, Tree **tree, int fileID);
void saveInfoIntoTree(Tree **tree, Get info);

int verifyCharAlpha(char caracter);
void fillStructField(Get *req, char *word, int position, int fileID);

void addFolder(char *file);