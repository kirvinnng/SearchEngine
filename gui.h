#pragma once

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

void showTree(Tree *tree);
void showNodeList(Node *list, char *word);

void verifyError(void *arg, const int line);
void gotoxy(int x, int y);
void setColor(int value);
