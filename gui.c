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
        printf(" | Nodes    : %d              \n", tree->length);
        showNodeList(tree->list);
        showTree(tree->left);
        showTree(tree->right);
    }
}

void showTreeWithoutWord(Tree *tree) {
    if (tree) {
        showNodeList(tree->list);
        showTree(tree->left);
        showTree(tree->right);
    }
}

void showNodeList(Node *list) {
    while (list) {
        printf(" | \n");
        printf(" | Document :  %d            \n", list->idDOC);
        printf(" | Position :  %d            \n", list->position);
        list = list->next;
    }
    printf(" ===========================================\n\n");
}

void verifyError(void *arg,char *fileName ,const int line) {

    if (arg == NULL) {
        fprintf(stderr, "ERROR (  FILE : %s - LINE : %d ) \n", fileName,line);
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
    gotoxy(0, 0);
}

void toLowerCase(char *str) {

    int valueA = 65;
    int valueZ = 90;

    while (*str != '\0') {

        if (*str >= valueA && *str <= valueZ) {

            *str = *str + 32;
        }
        str++;
    }
}

int didYouMean(Tree *tree, char *word) {
    WordSimilarity ws = _didYouMean(tree, word);
    if (ws.distance != 0 && ws.distance <= 3) {
        char confirmation = 'n';
        printf(" No se encontro el termino '%s', %cquisiste decir '%s'? s/n: ", ws.originalWord,
               168, ws.similarWord);
        fflush(stdin);
        scanf("%c", &confirmation);
        if (confirmation != 's') {
            return -1;
        }
        strcpy(word, ws.similarWord);
        return 1;
    } else if (ws.distance > 3) {
        printf(" No se encontro el termino '%s' ni similes en los documentos.\n", ws.originalWord);
        return -1;
    } else {
        return 0;
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
}

void setWindow(int width, int height, int widthBuffer, int heightBuffer) {
    COORD coord;
    coord.X = widthBuffer;
    coord.Y = heightBuffer;

    SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = height - 1;
    Rect.Right = width - 1;

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleScreenBufferSize(handle, coord);
    SetConsoleWindowInfo(handle, TRUE, &Rect);
}
