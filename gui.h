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

void viewOnlyWords(Tree *tree);
void showTree(Tree *tree);
void showTreeWithoutWord(Tree *tree);
void showNodeList(Node *list);

void menu();
int selectMenuOption();

void verifyError(void *arg,char *fileName, const int line);
void gotoxy(int x, int y);
void setColor(int value);
void setWindow(int width, int height, int widthBuffer, int heightBuffer);