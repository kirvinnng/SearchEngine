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

int selectMenuOption() {
    int i = 0;
    bool enter = false;
    gotoxy(6, 3);
    setColor(WHITE);
    printf(">");

    do {
        enter = false;
        menu();
        getch();
        if (GetAsyncKeyState(0x26) & 0x8000) { //  Arriba
            i = i > 0 ? i -= 1 : i;
        } else if (GetAsyncKeyState(0x28) & 0x8000) { // Abajo
            i = i < 2 ? i += 1 : i;
        } else if (GetAsyncKeyState(0x0D) & 0x8000) { // Enter
            enter = true;
        } else {
            i = i;
        }
        // fflush(stdin);

        Sleep(80);
        system("cls");
        gotoxy(6, 3 + (i * 2));
        setColor(WHITE);
        printf(">");
        gotoxy(20, 2);

    } while (!enter);
    return i;
}

void menu() {
    setColor(LIGHTCYAN);
    gotoxy(8, 3);
    printf("Mati \n");
    gotoxy(8, 5);
    printf("Kevin \n");
    gotoxy(8, 7);
    printf("EXIT");
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
}