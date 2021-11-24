#include "operations.h"
#include "algorithm.h"
#include "gui.h"
#include "main.h"
#include "read_file.h"

//* 1) Search for all occurrences of a term in a document (operation or).
void operation1(Tree *tree) {
    char word[500];
    int id;
    Tree *auxID = NULL;

    printf(" Termino a buscar: ");
    fflush(stdin);
    scanf("%s", word);
    toLowerCase(word);
    printf(" ID Documento: ");
    fflush(stdin);
    scanf("%d", &id);

    if(didYouMean(tree, word) == -1){
        return;
    }

    auxID = findWordByDoc(tree, word, id);
    if (auxID) {
        printf("\nSe encontro el termino '%s' en el documento Nro. %d.\n", word, id);
        showTreeWithoutWord(auxID);
    } else if (!auxID) {
        printf("No se encontro el termino '%s' en el documento Nro. %d.\n", word, id);
    }
}

//* 2) Search for all occurrences of a term in one document and another (and operation).
void operation2(Tree *tree) {
    char word[500];
    int id1, id2;
    Tree *auxID1 = NULL, *auxID2 = NULL;

    printf(" Termino a buscar: ");
    fflush(stdin);
    scanf("%s", word);
    toLowerCase(word);
    printf(" ID Documento Nro. 1: ");
    fflush(stdin);
    scanf("%d", &id1);
    printf(" ID Documento Nro. 2: ");
    fflush(stdin);
    scanf("%d", &id2);

    if (didYouMean(tree, word) == -1) {
        return;
    }

    auxID1 = findWordByDoc(tree, word, id1);
    auxID2 = findWordByDoc(tree, word, id2);

    if (auxID1 && auxID2) {
        printf("\nSe encontro el termino '%s' tanto en el documento Nro. %d como en el Nro. %d.\n", word, id1, id2);
        showTreeWithoutWord(auxID1);
        showTreeWithoutWord(auxID2);

    } else {
        printf("No se encontro el termino '%s' en ambos documentos (Nro. %d y Nro. %d).\n", word, id1, id2);
    }
}

//* 3) Search for the occurrence of more than one term in the same document.
void operation3(Tree *tree) {

    const int ESC = 27;
    char word[500];
    int id = 0;
    Tree *auxID1 = NULL;
    char choice;

    printf(" ID Documento : ");
    scanf("%d", &id);

    do {
        printf(" Termino a buscar: ");
        fflush(stdin);
        scanf("%s", word);
        toLowerCase(word);

        if (didYouMean(tree, word) == -1) {
            return;
        }

        auxID1 = findWordByDoc(tree, word, id);

        if (auxID1) {
            showTree(auxID1);
        } else {
            printf(" No se encontro el termino '%s' en el documento (Nro. %d).\n", word, id);
        }
        printf(" Pulse una tecla para realizar otra busqueda o ESC para salir\n");
        fflush(stdin);
        choice = getch();

    } while (choice != ESC);
}

//* 4) Search for a complete sentence (words must be contiguous in one of the documents).
void operation4(Tree *tree) {
    char phrase[500];
    int id;
    Tree *auxID = NULL;

    printf(" Ingrese una frase a buscar: ");
    fflush(stdin);
    gets(phrase);
    toLowerCase(phrase);

    printf(" ID Documento: ");
    scanf("%d", &id);

    SearchResult result = searchPhraseOnTree(tree, phrase, id);

    if (!result.foundAllWords) {
        printf(" No se encontraron todas las palabras de la frase '%s', ", phrase);
    } else {
        printf(" Se encontraron todas las palabras de la frase '%s'\n ", phrase);
        if (result.allWordsInOrder) {
            printf(" y se encontraron en orden en el documento %d a partir de la posicion %d.\n", id,
                   result.wordInitialPosition);
        } else {
            printf(" pero no se encontraron en orden.\n");
        }
    }
}

//* 5) Search for the most frequent word that appears in one of the documents.
void operation5(Tree *tree, TreeInfo treeInfo) {

    char phrase[500];
    int id;
    Tree *auxID = NULL;
    printf(" BUSCADOR DE LA PALABRA CON MAS FRECUENCIA \n\n");

    do {

        printf(" Ingrese el ID del documento : ");
        fflush(stdin);
        scanf("%d", &id);

        if (id < 1 || id > treeInfo.allDocument) {
            printf(" ID invalido \n\n");
        }
    } while (id < 1 || id > treeInfo.allDocument);

    FrequentWord fw = frequentWordByDocumentID(tree, id);

    printf(" ID %d : La palabra %s tiene la frecuencia mas alta con %d %s \n", id, fw.word, fw.frequency,
           (fw.frequency == 1) ? "aparicion" : "apariciones");
}