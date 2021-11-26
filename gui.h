#pragma once

#include <conio.h>
#include <stdbool.h>

#include "main.h"

enum Colors {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARKGREY,
    LIGHTBLUE,
    LIGHTGREEN,
    LIGHTCYAN,
    LIGHTRED,
    LIGHTMAGENTA,
    YELLOW,
    WHITE
};

int userChoice(Tree *tree, TreeInfo treeInfo);
int selectMenuOption();
void menu();
void keyMovement(const int _x, const int _y);
void inputSign(int valueColor);
void drawEnter(const int _x, const int _y);

void viewOnlyWords(Tree *tree);
void showTree(Tree *tree, int x, int y);
void showTreeWithoutWord(Tree *tree);
void showNodeList(Node *list);

int didYouMean(Tree *tree, char *word);
int choiceDocument(TreeInfo treeInfo, int _x, int _y, int numDoc);

void verifyError(void *arg, char *fileName, const int line);
void gotoxy(int x, int y);
void setColor(int value);
void setWindow(int width, int height, int widthBuffer, int heightBuffer);

void cleanLineHori(int _x, int _y, int size);
void cleanLineVert(int _x, int _y, int size);
