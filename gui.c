#include "gui.h"
#include "algorithm.h"
#include "main.h"

void showTree(Tree *tree) {
    if (tree) {
        showNodeList(tree->list, tree->word);
        showTree(tree->left);
        showTree(tree->right);
    }
}

void showNodeList(Node *list, char *word) {
    while (list) {
        printf("Word     : %s\n", word);
        printf("Document : %d\n", list->idDOC);
        printf("Position : %d\n", list->position);
        list = list->next;
    }
}

void verifyError(void *arg, const int line) {

    if (arg == NULL) {
        fprintf(stderr, "ERROR, Status : %d", line);
        free(arg);
        exit(1);
    }
}

void gotoxy(int x, int y) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {x, y};

    SetConsoleCursorPosition(console, pos);
}

void setColor(int value) {
    WORD color;

    HANDLE standarOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;

    if (GetConsoleScreenBufferInfo(standarOutput, &csbi)) {
        color = (csbi.wAttributes & 0xF0) + (value & 0x0F);
        SetConsoleTextAttribute(standarOutput, color);
    }
    return;
}