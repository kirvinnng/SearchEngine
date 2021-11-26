#include "gui.h"
#include "algorithm.h"
#include "main.h"
#include "operations.h"

const int x = 39;
const int y = 5;

int userChoice(Tree *tree, TreeInfo treeInfo) {

    //* these variables define the position of the menu

    int op = -1;
    const int exit = 6;

    do {

        op = selectMenuOption();

        system("cls");
        setColor(WHITE);

        //* 🤩 User operations 🤩
        switch (op) {
            case 0:
                operation1(tree, treeInfo);
                break;
            case 1:
                operation2(tree, treeInfo);
                break;
            case 2:
                operation3(tree, treeInfo);
                break;
            case 3:
                operation4(tree, treeInfo);
                break;
            case 4:
                operation5(tree, treeInfo);
                break;
            case 5:

                openHTML(tree);
                continue;

            default:
                return 0;
        }
        drawEnter(60, 23);
        gotoxy(0, 0);
        system("pause > nul");
        system("cls");

    } while (op != exit);
}

int selectMenuOption() {

    int i = 0;
    bool enter = false;
    gotoxy(x - 1, y + 1);
    setColor(LIGHTMAGENTA);
    printf(">");

    do {
        enter = false;

        keyMovement(60, 21);
        drawEnter(80, 24);

        menu(x, y);

        getch();
        fflush(stdin);

        if (GetAsyncKeyState(0x26) & 0x8000) { //* ⬆ Up ⬆
            i = i > 0 ? i -= 1 : i;
        } else if (GetAsyncKeyState(0x28) & 0x8000) { //* ⬇ Down ⬇
            i = i < 6 ? i += 1 : i;
        } else if (GetAsyncKeyState(0x0D) & 0x8000) { //* ↩ Enter ↩
            enter = true;
        } else {
            i = i;
        }

        Sleep(80);

        for (int i = 0; i < 14; i++) {
            gotoxy(x - 1, y + i);
            printf(" ");
        }

        gotoxy(x - 1, y + 1 + (i * 2));

        setColor(LIGHTMAGENTA);

        printf(">");

    } while (!enter);
    return i;
}

void menu() {

    setColor(WHITE);
    gotoxy(x, y + 1);
    printf(" Buscar todas las apariciones de un t%crmino en alg%cn documento ", E_ACCENT, U_ACCENT);
    gotoxy(x, y + 3);
    printf(" Buscar todas las apariciones de un t%crmino en un documento y otro ", E_ACCENT);
    gotoxy(x, y + 5);
    printf(" Buscar la aparici%cn de m%cs de un t%crmino en el mismo documento ", O_ACCENT, A_ACCENT, E_ACCENT);
    gotoxy(x, y + 7);
    printf(" Buscar una frase completa");
    gotoxy(x, y + 9);
    printf(" Buscar la palabra de m%cs frecuencia que aparece en alguno de los documentos", A_ACCENT);
    gotoxy(x, y + 11);
    printf(" Ver las palabras en el Navegador ");
    gotoxy(x, y + 13);
    printf(" SALIR ");
    setColor(LIGHTCYAN);
    gotoxy(x, y + 14);
    printf("_______________________________________________________________________________");
}

void viewOnlyWords(Tree *tree) {

    if (tree) {
        printf(" | Palabra : '%s'   \n", tree->word);
        viewOnlyWords(tree->left);
        viewOnlyWords(tree->right);
    }
}

void showTree(Tree *tree, int _x, int _y) {
    if (tree) {
        gotoxy(_x, _y);
        printf("Palabra   : '%s'     ", tree->word);
        gotoxy(_x, _y);
        printf("Nodos     :  %d      ", tree->length);
        showNodeList(tree->list);
        showTree(tree->left, _x, _y);
        showTree(tree->right, _x, _y);
    }
}

void showTreeWithoutWord(Tree *tree) {
    if (tree) {
        showNodeList(tree->list);
        showTreeWithoutWord(tree->left);
        showTreeWithoutWord(tree->right);
    }
}

void showNodeList(Node *list) {
    int _x = 120;
    int _y = 5;
    gotoxy(_x, _y);

    while (list) {

        gotoxy(_x + 1, _y);
        printf(" Document :  %d  ", list->idDOC);

        gotoxy(_x + 1, _y + 1);
        printf(" Position :  %d  ", list->position);

        list = list->next;
        _y += 3;
    }
    setColor(WHITE);
}

int choiceDocument(TreeInfo treeInfo, int _x, int _y, int numDoc) {
    int i = 1;
    int id = 0;
    do {
        gotoxy(_x, _y);
        if (numDoc == 0) {
            printf(" Documento  ");
            inputSign(LIGHTCYAN);
        } else {

            printf(" %d. Documento  ", numDoc);
            inputSign(LIGHTCYAN);
        }
        fflush(stdin);
        scanf("%d", &id);
        if (id < 1 || id > treeInfo.allDocument) {
            gotoxy(_x, _y + 1);
            printf(" ID INVALIDO \n\n");

            cleanLineHori(_x + 14, _y, 28);
        }
    } while (id < 1 || id > treeInfo.allDocument);
    gotoxy(_x, _y + 1);

    cleanLineHori(_x, _y + 1, 16);

    return id;
}

void inputSign(int valueColor) {
    setColor(valueColor);
    printf("> ");
    setColor(WHITE);
}

void cleanLineVert(int _x, int _y, int size) {

    for (int i = 0; i < size; i++) {
        gotoxy(_x, _y + i);
        printf("                   ");
    }
}

void cleanLineHori(int _x, int _y, int size) {

    for (int i = 0; i < size; i++) {

        gotoxy(x + i, _y);
        printf(" ");
    }
}

int didYouMean(Tree *tree, char *word) {

    WordSimilarity ws = _didYouMean(tree, word);

    gotoxy(x - 36, y + 1);

    if (ws.distance != 0 && ws.distance <= 3) {
        char confirmation = 'n';
        printf(" No se encontro  '%s'", ws.originalWord);

        gotoxy(x - 36, y + 3);
        printf("%cQuisiste decir '%s'? ( s / n ) ", QUESTION, ws.similarWord);
        gotoxy(x - 36, y + 4);
        inputSign(LIGHTCYAN);
        fflush(stdin);
        scanf("%c", &confirmation);
        confirmation = tolower(confirmation);
        if (confirmation != 's') {
            return -2;
        }
        strcpy(word, ws.similarWord);
        return 1;
    } else if (ws.distance > 3) {
        printf(" No se encontro  '%s'", ws.originalWord);
        gotoxy(x - 35, y + 2);
        printf(" Ni palabras similes en los documentos");
        return -1;
    } else {

        return 0;
    }
}

void keyMovement(const int _x, const int _y) {

    gotoxy(_x + 7, _y);
    printf("____");
    gotoxy(_x + 6, _y + 1);
    printf("||");
    setColor(LIGHTCYAN);
    gotoxy(_x + 8, _y + 1);
    printf("%c", UP);
    setColor(WHITE);
    gotoxy(_x + 10, _y + 1);
    printf("||");
    gotoxy(_x + 6, _y + 2);
    printf("||__||");
    gotoxy(_x + 2, _y + 3);
    printf("____|/__\\|____");
    gotoxy(_x + 1, _y + 4);
    printf("||");
    setColor(LIGHTCYAN);

    gotoxy(_x + 3, _y + 4);
    printf("%c", 17); //! ----X----
    // printf("<-");
    setColor(WHITE);
    gotoxy(_x + 5, _y + 4);
    printf("|||");
    setColor(LIGHTCYAN);
    gotoxy(_x + 8, _y + 4);
    printf("%c", DOWN);
    setColor(WHITE);
    gotoxy(_x + 10, _y + 4);
    printf("|||");
    setColor(LIGHTCYAN);
    // gotoxy(_x + 14, _y + 4);
    // printf("%c", RIGHT);
    gotoxy(_x + 13, _y + 4);
    printf("%c", 16);
    setColor(WHITE);
    gotoxy(_x + 15, _y + 4);
    printf("||");
    gotoxy(_x + 1, _y + 5);
    printf("||__|||__|||__||");
    gotoxy(_x + 1, _y + 6);
    printf("|/__\\|/__\\|/__\\|");
}

void drawEnter(const int _x, const int _y) {

    gotoxy(_x, _y);
    printf(" ___________");
    gotoxy(_x, _y + 1);
    printf("||  ");
    setColor(LIGHTCYAN);
    printf("Enter  ");
    setColor(WHITE);
    printf("||");
    gotoxy(_x, _y + 2);
    printf("||_________||");
    gotoxy(_x, _y + 3);
    printf("|/_________\\|");
}

void verifyError(void *arg, char *fileName, const int line) {

    if (arg == NULL) {
        gotoxy(0, 0);
        fprintf(stderr, "ERROR (  FILE : %s - LINE : %d ) \n", fileName, line);
        free(arg);
        exit(1);
    }
}

void gotoxy(int _x, int _y) {

    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos = {_x, _y};

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
