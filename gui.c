#include "gui.h"
#include "algorithm.h"
#include "main.h"

void viewOnlyWords(Tree *tree) {

    if (tree) {
        printf(" | Word : '%s'   \n", tree->word);

        viewOnlyWords(tree->left);
        viewOnlyWords(tree->right);
    }
}

void showTree(Tree *tree) {
    if (tree) {
        printf(" | Word     : '%s'            \n", tree->word);
        showNodeList(tree->list);
        showTree(tree->left);
        showTree(tree->right);
    }
}

void showNodeList(Node *list) {
    while (list) {
        printf(" .-------------------------\n");
        // printf(" | Word     : '%s'            \n", word);
        printf(" | Document :  %d            \n", list->idDOC);
        printf(" | Position :  %d            \n", list->position);
        printf(" .-------------------------\n\n");

        list = list->next;
    }
    printf(" ===========================================\n\n");
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