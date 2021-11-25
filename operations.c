#include "operations.h"
#include "algorithm.h"
#include "create_file.h"
#include "gui.h"
#include "main.h"
#include "read_file.h"

extern const int x;
extern const int y;

//* 1) Search for all occurrences of a term in a document (operation or).
void operation1(Tree *tree, TreeInfo treeInfo) {
    char word[500];
    int id;
    Tree *auxID = NULL;
    gotoxy(x, y - 4);

    printf(" Buscar todas las apariciones de un t%crmino en alg%cn documento ", E_ACCENT, U_ACCENT);
    gotoxy(x, y + 1);
    printf(" Palabra  ", COM);
    inputSign(LIGHTCYAN);
    fflush(stdin);
    scanf("%s", word);

    toLowerCase(word);

    id = choiceDocument(treeInfo, x, y + 3, 0);

    if (didYouMean(tree, word) == -1) {
        return;
    }

    auxID = findWordByDoc(tree, word, id);

    if (auxID) {
        gotoxy(x, y + 5);
        printf(" Se encontro el termino '%s' en el documento Nro. %d.\n", word, id);
        gotoxy(x, y + 8);
        setColor(WHITE);
        printf(" ___________________________________________");
        showTreeWithoutWord(auxID);
    } else if (!auxID) {
        gotoxy(x, y + 5);
        printf(" No se encontro el termino '%s' en el documento Nro. %d.\n", word, id);
    }
}

//* 2) Search for all occurrences of a term in one document and another (and operation).
void operation2(Tree *tree, TreeInfo treeInfo) {
    char word[500];
    int id1, id2;
    Tree *auxID1 = NULL, *auxID2 = NULL;

    gotoxy(x, y - 4);
    printf(" Buscar todas las apariciones de un t%crmino en un documento y otro ", E_ACCENT);

    gotoxy(x, y + 1);
    printf(" Palabra  ", COM);
    inputSign(LIGHTCYAN);
    inputSign(LIGHTCYAN);
    fflush(stdin);
    scanf("%s", word);
    toLowerCase(word);

    id1 = choiceDocument(treeInfo, x, y + 3, 1);
    id2 = choiceDocument(treeInfo, x, y + 4, 2);

    if (didYouMean(tree, word) == -1) {
        return;
    }

    auxID1 = findWordByDoc(tree, word, id1);
    auxID2 = findWordByDoc(tree, word, id2);

    if (auxID1 && auxID2) {
        gotoxy(x, y + 6);
        printf(" Se encontro el termino '%s' tanto en el documento Nro. %d como en el Nro. %d", word, id1, id2);
        showTreeWithoutWord(auxID1);
        showTreeWithoutWord(auxID2);

    } else {
        gotoxy(x, y + 6);
        printf(" No se encontro el termino '%s' en ambos documentos (Nro. %d y Nro. %d)", word, id1, id2);
    }
}

//* 3) Search for the occurrence of more than one term in the same document.
void operation3(Tree *tree, TreeInfo treeInfo) {

    char word[500];
    int id = 0;
    Tree *auxID1 = NULL;
    char choice;
    gotoxy(x, y - 4);
    printf(" Buscar la aparici%cn de m%cs de un t%crmino en el mismo documento ", O_ACCENT, A_ACCENT, E_ACCENT);

    id = choiceDocument(treeInfo, x, y + 1, 0);

    gotoxy(x, y + 3);
    printf(" Palabra  ", COM);
    inputSign(LIGHTCYAN);
    fflush(stdin);
    scanf("%s", word);
    toLowerCase(word);

    if (didYouMean(tree, word) == -1) {
        return;
    }

    auxID1 = findWordByDoc(tree, word, id);

    if (auxID1) {
        gotoxy(x, y + 5);
        setColor(WHITE);
        printf(" ___________________________________________");
        gotoxy(x + 1, y + 7);
        printf(" Palabra  : %s ", word);
        gotoxy(x + 1, y + 8);
        printf(" Nodos    : %d ", auxID1->length);
        showTreeWithoutWord(auxID1);
    } else {
        gotoxy(x, y + 5);
        printf(" No se encontro '%s' en el documento '%d' ", word, id);
    }
}

//* 4) Search for a complete sentence (words must be contiguous in one of the documents).
void operation4(Tree *tree, TreeInfo treeInfo) {
    char phrase[500];
    int id;
    Tree *auxID = NULL;

    gotoxy(x, y - 4);
    printf(" Buscar una frase completa");

    gotoxy(x, y + 1);
    printf(" Frase  ", COM);
    inputSign(LIGHTCYAN);
    fflush(stdin);
    gets(phrase);
    toLowerCase(phrase);

    id = choiceDocument(treeInfo, x, y + 3, 0);

    SearchResult result = searchPhraseOnTree(tree, phrase, id);

    if (!result.foundAllWords) {
        gotoxy(x, y + 5);
        printf(" No se encontraron todas las palabras de la frase '%s'. ", phrase);
    } else {
        gotoxy(x, y + 5);
        printf(" Se encontraron todas las palabras de la frase '%s' ", phrase);
        if (result.allWordsInOrder) {
            gotoxy(x, y + 6);
            printf(" y se encontraron en orden en el documento %d a partir de la posicion %d.\n", id,
                   result.wordInitialPosition);
        } else {
            gotoxy(x, y + 6);
            printf(" pero no se encontraron en orden.\n");
        }
    }
}

//* 5) Search for the most frequent word that appears in one of the documents.
void operation5(Tree *tree, TreeInfo treeInfo) {

    char phrase[500];
    int id;
    Tree *auxID = NULL;

    gotoxy(x, y - 4);
    printf(" Buscar la palabra de m%cs frecuencia que aparece en alguno de los documentos ", A_ACCENT);

    id = choiceDocument(treeInfo, x, y + 1, 0);

    FrequentWord fw = frequentWordByDocumentID(tree, id);

    gotoxy(x, y + 3);

    printf(" La palabra '%s' tiene la frecuencia mas alta con %d %s \n", fw.word, fw.frequency,
           (fw.frequency == 1) ? "aparicion" : "apariciones");
}

void openHTML(Tree *tree) {

    createHTML(tree);
    system("cd document && dictionary.html");
}
